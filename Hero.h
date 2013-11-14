#pragma once
#include "GameObject.h"
class Hero :
	public GameObject
{
public:
	Hero();
	Hero(const Hero &hero);
	Hero &operator=(const Hero &hero);
	Hero(RenderableComponent *model, PhysicalComponent *physicalComponent);
	~Hero();

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	void stopMoveUp();
	void stopMoveDown();
	void stopMoveRight();
	void stopMoveLeft();

};

