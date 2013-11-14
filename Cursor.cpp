#include "Cursor.h"


Cursor::Cursor()
{
	physicalComponent = new PhysicalComponent();
}


Cursor::~Cursor()
{
	delete physicalComponent;
}

void Cursor::translate(Vect4 translation)
{
	this->physicalComponent->setSpeed(translation);
	this->physicalComponent->setAcceleration(0);
}