#pragma once
#ifndef GLSHADER_H
#define GLSHADER_H
#include <iostream>
#include "stdafx.h"
#include "ShadersInc.h"
using namespace std;

class GLShader
{
private:
	string filename;
	char *shaderStr;
	unsigned int ID;
	GLenum type;
public:
	GLShader();
	GLShader(const char *filename, GLenum type);
	~GLShader();
	void init()  throw (ShaderException);
	void loadSource(const char *filename = NULL) throw (ShaderException);
	void loadShader() throw (ShaderException);
	unsigned int getID();
};
#endif
