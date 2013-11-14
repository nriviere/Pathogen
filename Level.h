#pragma once
#include "stdafx.h"
class Level
{
private:
	float limitsX[2],limitsY[2];
public:

	Level();
	~Level();
	float *getLimitsX();
	float *getLimitsY();
};

