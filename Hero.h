#pragma once
#include "GameObject.h"

class GameEngine;

class Hero :
	public GameObject
{
public:
	Hero(GameEngine *engine = NULL);
	Hero(const Hero &hero);
	Hero &operator=(const Hero &hero);
	Hero(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent);
	~Hero();

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	void shoot();
	Vect4 getHeading();

	void stopMoveUp();
	void stopMoveDown();
	void stopMoveRight();
	void stopMoveLeft();

	void selfAdd();
	void selfRemove();

};

