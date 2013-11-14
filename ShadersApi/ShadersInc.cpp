#include "ShadersInc.h"
#include "ShaderException.h"
#include <iostream>

PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;

PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLDELETEPROGRAMPROC  glDeleteProgram = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLDETACHSHADERPROC glDetachShader = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;

PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLUNIFORM1FVPROC  glUniform1fv = NULL;
PFNGLUNIFORM4FVPROC  glUniform4fv = NULL;
PFNGLUNIFORM1UIPROC  glUniform1ui = NULL;
PFNGLUNIFORM1FPROC  glUniform1f = NULL;

void initApi() throw (ShaderException){
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	if (glCreateShader == NULL)
	{
		throw new ShaderException("failed to retrieve glCreateShader function pointer.");
		return;
	}

	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	if (glShaderSource == NULL)
	{
		throw new ShaderException("failed to retrieve glShaderSource function pointer.");
	}
	
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	if (glDeleteShader == NULL)
	{
		throw new ShaderException("failed to retrieve glDeleteShader function pointer.");
	}

	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	if (glCompileShader == NULL)
	{
		throw new ShaderException("failed to retrieve glCompileShader function pointer.");
	}

	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	if (glGetShaderiv == NULL)
	{
		throw new ShaderException("failed to retrieve glGetShaderiv function pointer.");
	}

	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	if (glGetShaderInfoLog == NULL)
	{
		throw new ShaderException("failed to retrieve glGetShaderInfoLog function pointer.");
	}


	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	if (glCreateProgram == NULL)
	{
		throw new ShaderException("failed to retrieve glCreateProgram function pointer.");
	}

	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	if (glDeleteProgram == NULL)
	{
		throw new ShaderException("failed to retrieve glDeleteProgram function pointer.");
	}

	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	if (glAttachShader == NULL)
	{
		throw new ShaderException("failed to retrieve glAttachShader function pointer.");
	}

	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	if (glDetachShader == NULL)
	{
		throw new ShaderException("failed to retrieve glDetachShader function pointer.");
	}

	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	if (glLinkProgram == NULL)
	{
		throw new ShaderException("failed to retrieve glLinkProgram function pointer.");
	}

	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	if (glGetProgramiv == NULL)
	{
		throw new ShaderException("failed to retrieve glGetProgramiv function pointer.");
	}

	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	if (glGetProgramInfoLog == NULL)
	{
		throw new ShaderException("failed to retrieve glGetProgramInfoLog function pointer.");
	}

	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	if (glUseProgram == NULL)
	{
		throw new ShaderException("failed to retrieve glUseProgram function pointer.");
	}

	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	if (glGetUniformLocation == NULL)
	{
		throw new ShaderException("failed to retrieve glGetUniformLocation function pointer.");
	}

	glUniform1fv = (PFNGLUNIFORM1FVPROC)wglGetProcAddress("glUniform1fv");
	if (glUniform1fv == NULL)
	{
		throw new ShaderException("failed to retrieve glUniform1fv function pointer.");
	}

	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	if (glUniform4fv == NULL)
	{
		throw new ShaderException("failed to retrieve glUniform4fv function pointer.");
	}

	glUniform1ui = (PFNGLUNIFORM1UIPROC)wglGetProcAddress("glUniform1ui");
	if (glUniform1ui == NULL)
	{
		throw new ShaderException("failed to retrieve glUniform1ui function pointer.");
	}

	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	if (glUniform1f == NULL)
	{
		throw new ShaderException("failed to retrieve glUniform1f function pointer.");
	}
}

