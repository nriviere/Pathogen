#pragma once
#include <cmath>
#include <iostream>

class Vect4
{
public:
	float values[4];

	Vect4()
	{
		values[0] = 0;
		values[1] = 0;
		values[2] = 0;
		values[3] = 0;
	}

	Vect4(float v[4])
	{
		values[0] = v[0];
		values[1] = v[1];
		values[2] = v[2];
		values[3] = v[3];
	}

	Vect4(const Vect4 &v)
	{
		values[0] = v[0];
		values[1] = v[1];
		values[2] = v[2];
		values[3] = v[3];
	}

	Vect4 &operator=(const Vect4 &v)
	{
		values[0] = v[0];
		values[1] = v[1];
		values[2] = v[2];
		values[3] = v[3];
		return *this;
	}
	
	Vect4(float X,float Y,float Z,float W)   {
		values[0] = X;
		values[1] = Y;
		values[2] = Z;
		values[3] = W;
	};

	float operator[](int i) const
	{
		if (i > 3 || i < 0)
		{
			exit(-1);
		}
		return values[i];
	}

	Vect4 operator+(const Vect4 & v) const
	{
		Vect4 add(values[0] + v[0], values[1] + v[1], values[2] + v[2], values[3]);
		return add;
	}

	Vect4 operator^(const Vect4 & v) const
	{
		Vect4 vec(values[1]*v.values[2]-values[2]*v.values[1],values[2]*v.values[0]-values[0]*v.values[2],values[0]*v.values[1]-values[1]*v.values[0],1);
		return vec;
	}

	float operator*(const Vect4 & v) const
	{
		return values[0]*v.values[0]+values[1]*v.values[1]+values[2]*v.values[2];
	}
	
	float norme(){
		return sqrt(pow(values[0],2)+pow(values[1],2)+pow(values[2],2));
	}

	void normalize(){
		float n = norme();
		values[0] /= n; values[1] /= n; values[2] /= n;
	}

	~Vect4(void){};
};

