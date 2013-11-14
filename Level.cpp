#include "Level.h"


Level::Level()
{
	limitsX[0] = -200;
	limitsY[0] = -150;
	limitsX[1] = 200;
	limitsY[1] = 150;
}


Level::~Level()
{
}

float *Level::getLimitsX()
{
	return limitsX;
}
float *Level::getLimitsY()
{
	return limitsY;
}