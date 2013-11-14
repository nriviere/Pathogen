#pragma once
#ifndef PROGRAM_H
#define PROGRAM_H
#include "Shader.h"
#include <list>

class Program
{
private:
	unsigned int ID;
	unsigned int shader_count;
	Shader *shaders[2];
	bool in_use;
public:

	static list<unsigned int> current_program;

	Program();
	~Program();
	unsigned int getID();
	Shader **getShaders(unsigned int *shader_count);
	void setShader(Shader *shader, unsigned int position);
	void removeShader(unsigned int position);
	void linkProgram();
	void start();
	void stop();
};
#endif
