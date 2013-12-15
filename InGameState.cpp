#include "InGameState.h"
#include "GameEngine.h"
#include "MyEngine.h"
#include "Renderer.h"
#include "Light.h"
#include <WinUser.h>

InGameState::InGameState(GameEngine *engine) : GameState(engine)
{
	isZdown = isQdown = isSdown = isDdown = false;
	prevMousePos.x = 0;
	prevMousePos.y = 0;
	parentEngine = engine->getParentEngine();
}

InGameState::~InGameState(void)
{
}

void InGameState::mouseMove(POINT pos)
{
	Vect4 cursorMove(pos.x,-pos.y, 0, 1);
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
	default:
		break;

	}
}

void InGameState::setup()
{
	ShowCursor(false);

	Renderer *renderer = parentEngine->getRenderer();
	renderer->init();

	const char *names[7];
	names[0] = "3DS/models/hero.obj";
	names[1] = "3DS/models/cell.obj";
	names[2] = "3DS/models/neutrophil.obj";
	names[3] = "3DS/models/bacteria.obj";
	names[4] = "3DS/models/virus.obj";
	names[5] = "3DS/models/cancer.obj";
	names[6] = "3DS/models/monocyte.obj";
	engine->load(names, 7);

	Light * light = new Light(Matrx44(Vect4(0.1,0.1,0.1, 1.),
		Vect4(0.5, 0.5,0.5, 1.),
		Vect4(1, 1, 1, 1),
		Vect4(0, 0, -100, 1)),
		0,0);

	int lightId = renderer->addLight(light);

	
}

void InGameState::update(float fDT)
{
	
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

	engine->getCurrentLevel()->update();
	engine->remove();
	engine->addParticleSystems();
}

void InGameState::display(unsigned int u32Width, unsigned int u32Height)
{
	parentEngine->getRenderer()->render(engine->getGameObjects(), engine->getGameObjectCount(), u32Width, u32Height, engine->getCurrentLevel());
}

