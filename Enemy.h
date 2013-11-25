#pragma once
#include "ReplicableGameObject.h"

class Cell;
class Hero;

class Enemy :
	public ReplicableGameObject
{
public:
	Enemy();
	~Enemy();

	void hit(Cell *cell);
	void hit(Hero *hero);
};

