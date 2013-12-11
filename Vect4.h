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
		return values[i];
	}

	float &operator[](int i)
	{
		/*if (i > 3 || i < 0)
		{
			exit(-1);
		}*/
		return values[i];
	}

	Vect4 operator+(const Vect4 & v) const
	{
		float w = 0;
		if (v[3] == 1 || values[3] == 1) w = 1;
		Vect4 add(values[0] + v[0], values[1] + v[1], values[2] + v[2], 1);
		return add;
	}

	Vect4 operator-(const Vect4 & v) const
	{
		float w = 0;
		//if (v[3] == 1|| values[3] == 1) w = 1;
		return Vect4(values[0] - v[0], values[1] - v[1], values[2] - v[2], v[3] * values[3]);
	}

	Vect4 operator-() const
	{
		Vect4 add(-values[0] , -values[1] , -values[2], values[3]);
		return add;
	}

	Vect4 operator^(const Vect4 & v) const
	{
		Vect4 vec(values[1]*v.values[2]-values[2]*v.values[1],values[2]*v.values[0]-values[0]*v.values[2],values[0]*v.values[1]-values[1]*v.values[0],1);
		return vec;
	}

	float operator*(const Vect4 & v) const
	{
		return values[0]*v.values[0]+values[1]*v.values[1]+values[2]*v.values[2]+values[3]*v.values[3];
	}


	Vect4 operator*(float f) const
	{
		return Vect4(values[0] * f , values[1] * f , values[2] * f,values[3]);
	}

	float dot(const Vect4 & v) const
	{
		float nu = norme();
		float nv = v.norme();
		return 0.5 * (pow(((*this) + v).norme(), 2) - pow(nu, 2) - pow(nv, 2));
	}

	float norme() const{
		return sqrt(pow(values[0],2)+pow(values[1],2)+pow(values[2],2));
	}

	float normesqr(){
		return pow(values[0], 2) + pow(values[1], 2) + pow(values[2], 2);
	}

	void normalize(){
		float n = norme();
		values[0] /= n; values[1] /= n; values[2] /= n;
	}

	Vect4 reflect(const Vect4 &n){
		float length = norme();
		Vect4 v = (*this);
		v.normalize();
		v = n *(v*n)* -2 + v;
		v = v * length;
		return v;
	}

	void toFloatv(float *v)
	{
		v[0] = values[0];
		v[1] = values[1];
		v[2] = values[2];
		v[3] = values[3];
	}

	~Vect4(void){};
};

