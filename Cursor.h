#pragma once
#include "stdafx.h"
#include "GameObject.h"

class Cursor : public GameObject
{
public:
	Cursor();
	~Cursor();
	void translate(Vect4 translation);
};

