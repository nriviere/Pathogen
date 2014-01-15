#pragma once
#include "GameObject.h"
#include "Monocyte.h"

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

	static const int MUN_MAX = 50;

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	void shoot();
	Monocyte *shootMonocyte();
	Vect4 getHeading();

	void stopMoveUp();
	void stopMoveDown();
	void stopMoveRight();
	void stopMoveLeft();

	void selfAdd();
	void selfRemove();

	float getMunitionType1();
	float getMunitionType2();
	float getMunitionType3();
	int getCurrentMunition();

	void setGenerator(int generator);

	void regenerateMunition(float deltaTime);
	void changeMunitionType(bool up);
	void changeMunitionType(int type);
	
	void setLymphocyteTag(ObjectType type);
	ObjectType getLymphocyteTag();

private:
	float munitions[3];
	int currentMunition;

	int regenerator[3];
	float regenerationTime;
	
	ObjectType lymphocyteTag;
};

