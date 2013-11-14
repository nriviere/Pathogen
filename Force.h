#pragma once

#include "stdafx.h"
#include "Vect4.h"

class Force : public Vect4
{
private:
	float acceleration;
public:
	Force(float acceleration = 1) : Vect4()
	{
		this->acceleration = 1;
	}

	Force(float v[4],float acceleration = 1) : Vect4(v)
	{
		this->acceleration = acceleration;
	}

	Force(const Force &v) : Vect4(v)
	{
		acceleration = v.acceleration;
	}

	Force &operator=(const Force &v)
	{
		Vect4::operator=(v);
		acceleration = v.acceleration;
		return *this;
	}

	Force(float X, float Y, float Z, float W,float acceleration = 1)  : Vect4(X,Y,Z,W) {
		this->acceleration = acceleration;
	}

	void update(){
		values[0] *= acceleration;
		values[1] *= acceleration;
		values[2] *= acceleration;
	}


};