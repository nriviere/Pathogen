#include "InGameState.h"
#include "MyEngine.h"
#include <WinUser.h>

InGameState::InGameState(MyEngine *engine) : GameState(engine)
{
	isZdown = isQdown = isSdown = isDdown = false;
	prevMousePos.x = 0;
	prevMousePos.y = 0;
	ShowCursor(false);

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
	engine->getRenderer()->init();

	const char *test[2];
	test[0] = "3DS/models/hero.obj";
	test[1] = "3DS/models/cell.obj";
	engine->load(test, 2);

	Light * light = new Light(Matrx44(Vect4(0.3, 0.1, 0.1, 1),
		Vect4(0.5, 0.3, 0.3, 1),
		Vect4(0.8, 0.5, 0.5, 1),
		Vect4(0, 0, 0, 1)));

	int lightId = engine->getRenderer()->addLight(light);

	engine->getErrLog()->open("log.txt", std::ios::trunc);


}

void InGameState::update(float fDT)
{
	engine->getPhysicalEngine()->update(fDT);
}

void InGameState::render(unsigned int u32Width, unsigned int u32Height)
{

	engine->getRenderer()->render(engine->getGameObjects(), engine->getGameObjectCount(), u32Width, u32Height, engine->getCurrentLevel());
}