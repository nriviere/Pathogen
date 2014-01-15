#include "InGameState.h"
#include "GameEngine.h"
#include "MyEngine.h"
#include "Renderer.h"
#include "Light.h"
#include <WinUser.h>
#include "HeroPhysicalComponent.h"

InGameState::InGameState(GameEngine *engine) : GameState(engine)
{
	isZdown = isQdown = isSdown = isDdown = false;
	prevMousePos.x = 0;
	prevMousePos.y = 0;
	remainingLife = 3;
	parentEngine = engine->getParentEngine();
}

InGameState::~InGameState(void)
{
}

void InGameState::mouseWheel(float fIncrement)
{
	bool up = fIncrement > 0;
	engine->getHero()->changeMunitionType(up);
}

void InGameState::mouseMove(POINT pos)
{
	float cursorMoveX = pos.x;
	float cursorMoveY = -pos.y;
	Vect4 cursorMove(0,0,0,1);
	Cursor *cursor = engine->getCursor();
	float *limitsX = engine->getCurrentLevel()->getLimitsX();
	float *limitsY = engine->getCurrentLevel()->getLimitsY();
	Vect4 cursorPostion = cursor->getPhysicalComponent()->getPosition();
	if (limitsX[0] <= cursorMoveX + cursorPostion[0] && limitsX[1] >= cursorMoveX + cursorPostion[0])
	{
	
		cursorMove[0] = cursorMoveX;
	}

	if (limitsY[0] <= cursorMoveY + cursorPostion[1] && limitsY[1] >= cursorMoveY + cursorPostion[1])
	{
		cursorMove[1] = cursorMoveY;
	}
	engine->getCursor()->translate(cursorMove*1.5);
	prevMousePos = pos;
}

void InGameState::lButtonDown(POINT Pt)
{
	engine->getHero()->shoot();
}

void InGameState::lButtonUp(POINT Pt)
{
}

void InGameState::keyUp(int s32VirtualKey)
{
	switch (s32VirtualKey) {
	case 90: //z 
		engine->getHero()->stopMoveUp();
		isZdown = false;
		break;

	case 83: //s 
		engine->getHero()->stopMoveDown();
		isSdown = false;
		break;

	case 81: //q 
		engine->getHero()->stopMoveLeft();
		isQdown = false;
		break;
	case 68: //d 
		engine->getHero()->stopMoveRight();
		isDdown = false;
		break;
	default:
		break;

	}
}
void InGameState::keyDown(int s32VirtualKey)
{
	switch (s32VirtualKey) {
	case 90: //z 
		if (!isZdown)
		{
			engine->getHero()->moveUp();
			isZdown = true;
		}
		break;

	case 83: //s 
		if (!isSdown)
		{
			engine->getHero()->moveDown();
			isSdown = true;
		}
		break;

	case 81: //q 
		if (!isQdown)
		{
			engine->getHero()->moveLeft();
			isQdown = true;
		}
		break;
	case 68: //d 
		if (!isDdown)
		{
			engine->getHero()->moveRight();
			isDdown = true;
		}
		break;
	case 49:
		engine->getHero()->changeMunitionType(0);
		break;
	case 50:
		engine->getHero()->changeMunitionType(1);
		break;
	case 51:
		engine->getHero()->changeMunitionType(2);
		break;
	default:
		break;
	}
}

void InGameState::setup()
{
	bool cursorVisible;
	do{
		cursorVisible = ShowCursor(false) >= 0;
	} while (cursorVisible);

	score = 0;

	PhysicalEngine *physicalEngine = engine->getParentEngine()->getPhysicalEngine();
	Renderer *renderer = engine->getParentEngine()->getRenderer();

	PhysicalComponent *physicalComponent = new HeroPhysicalComponent(engine->getCursor());
	physicalComponent->setPosition(Vect4(0, 0, 0, 1));
	Hero *hero = new Hero(engine, &renderer->getModels()[0], physicalComponent);
	engine->setHero(hero);
	engine->addObject(hero);
	Light * light = new Light(Matrx44(Vect4(0.1, 0.1, 0.1, 1.),
		Vect4(0.5, 0.5, 0.5, 1.),
		Vect4(1, 1, 1, 1),
		Vect4(0, 0, -100, 1)),
		0, 0);

	int lightId = renderer->addLight(light);
	engine->getCurrentLevel()->load();
	engine->getCurrentLevel()->init();
}

void InGameState::update(float fDT)
{
	unsigned int nb_life = remainingLife;
	engine->getHero()->regenerateMunition(fDT);
	parentEngine->getRenderer()->updateTime(fDT);

	parentEngine->getPhysicalEngine()->update(fDT);
	unsigned int gameObjectCount = engine->getGameObjectCount();
	unsigned int particleSystemCount = engine->getParticleSystemCount();
	GameObject **gameObjects = engine->getGameObjects();
	ParticleSystem **particleSystems = engine->getParticleSystems();
	int count = 0;
	for (int i = 0; i < GameEngine::MAX_GAME_OBJECT_COUNT && count < gameObjectCount; i++)
	{
		if (gameObjects[i] != NULL)
		{
			count++;
			gameObjects[i]->update();
		}
	}
	count = 0;
	for (int i = 0; i < GameEngine::MAX_PARTICLE_SYSTEM_COUNT && count < particleSystemCount; i++)
	{
		if (particleSystems[i] != NULL)
		{
			count++;
			particleSystems[i]->update(fDT);
		}
	}

	
	engine->remove();
	engine->addParticleSystems();

	engine->getCurrentLevel()->update();

	if (nb_life > remainingLife)
	{
		engine->clear();
		engine->getParentEngine()->getRenderer()->clear();
		engine->nextState(2);
	}

	if (remainingLife == 0)
	{
		engine->clear();
		engine->getParentEngine()->getRenderer()->clear();
		engine->gameOver();
	}
		
	if (engine->getCurrentLevel()->isFinished()&&engine->getEnemyCount() == 0)
	{
		engine->clear();
		engine->getParentEngine()->getRenderer()->clear();
		engine->setNextLevel();

		if (engine->isGameFinished())
		{
			//END GAME STATE;
			engine->nextState(0);
			engine->setFinished(false);
		}
		else{
			engine->nextState(4);
		}
	}
}

void InGameState::display(unsigned int u32Width, unsigned int u32Height)
{
	parentEngine->getRenderer()->render(engine->getGameObjects(), engine->getGameObjectCount(), u32Width, u32Height, engine->getCurrentLevel());
}

void InGameState::decreaseLife()
{
	if (remainingLife > 0)
	{
		remainingLife--;
	}
}

unsigned int InGameState::getRemainingLife()
{
	return remainingLife;
}

void InGameState::setRemainingLife(unsigned int life)
{
	remainingLife = life;
}

unsigned int InGameState::getScore()
{
	return score;
}

void InGameState::setScore(unsigned int scr)
{
	score = scr;
}