#pragma once
#include "vect4.h"
class Matrx44
{
public:
	Vect4 Ox,Oy,Oz,Pos;

	Matrx44()
	{
		this->Ox = Vect4(1, 0, 0, 0);
		this->Oy = Vect4(0, 1, 0, 0);
		this->Oz = Vect4(0, 0, 1, 0);
		this->Pos = Vect4(0, 0, 0, 1);
	}

	Matrx44(const Vect4 Ox, const Vect4 Oy,const Vect4 Oz, const Vect4 pos): Ox(Ox),Oy(Oy),Oz(Oz),Pos(pos){};

	Matrx44(const Matrx44& m)
	{
		Ox = m.Ox; Oy = m.Oy; Oz = m.Oz; Pos = m.Pos;
	}

	Matrx44 operator=(const Matrx44 &m)
	{
		Ox = m.Ox; Oy = m.Oy; Oz = m.Oz; Pos = m.Pos;
		return *this;
	}

	void loadIdentity()
	{
		this->Ox  = Vect4(1,0,0,0);
		this->Oy  = Vect4(0,1,0,0);
		this->Oz  = Vect4(0,0,1,0);
		this->Pos = Vect4(0,0,0,1);
	}

	Matrx44 operator*(const Matrx44 &m) const
	{
		return Matrx44(	Vect4(m.Ox*getX(),m.Ox*getY(),m.Ox*getZ(),m.Ox*getW()),
						Vect4(m.Oy*getX(),m.Oy*getY(),m.Oy*getZ(),m.Oy*getW()),
						Vect4(m.Oz*getX(),m.Oz*getY(),m.Oz*getZ(),m.Oz*getW()),
						Vect4(m.Pos*getX(), m.Pos*getY(), m.Pos*getZ(), m.Pos*getW()));
	}

	Vect4 operator*(const Vect4 &v)
	{
		return Vect4(getX()*v,getY()*v,getZ()*v,getW()*v);
	}

	Matrx44 rotation(float angle, Vect4 u)
	{
		float c = cos(angle),s = sin(angle);
		Ox = Vect4(u[0] * u[0] + (1 - u[0] * u[0])*c, u[0] * u[1]*(1 - c) + u[2]*s, u[0]*u[2]*(1 - c) - u[1]*s,0);
		Oy = Vect4(u[0] * u[1]*(1 - c) - u[2]*s, u[1]*u[1] + (1 - u[1]*u[1])*c, u[1]*u[2]*(1 - c) + u[0]*s,0);
		Oz = Vect4(u[0] * u[2]*(1 - c) + u[1]*s, u[1]*u[2]*(1 - c) - u[0]*s, u[2]*u[2] + (1 - u[2]*u[2])*c,0);
		Pos = Vect4(0,0,0,1);
		return *this;
	}

	Matrx44 orthonormalisation()
	{
		Ox = Oy^Oz;
		Oy = Oz^Ox;
		return *this;
	}

	Vect4 getX() const{return Vect4(Ox[0],Oy[0],Oz[0],Pos[0]);}
	Vect4 getY() const{return Vect4(Ox[1],Oy[1],Oz[1],Pos[1]);}
	Vect4 getZ() const{return Vect4(Ox[2],Oy[2],Oz[2],Pos[2]);}
	Vect4 getW() const{return Vect4(Ox[3],Oy[3],Oz[3],Pos[3]);}

	~Matrx44(void){};
};

