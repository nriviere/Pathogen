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
PFNGLUNIFORM1UIVPROC glUniform1uiv = NULL;
PFNGLUNIFORMMATRIX4FVPROC  glUniformMatrix4fv = NULL;
PFNGLUNIFORM4FPROC  glUniform4f = NULL;
PFNGLUNIFORM1UIPROC  glUniform1ui = NULL;
PFNGLUNIFORM1FPROC  glUniform1f = NULL;
PFNGLUNIFORM1IPROC  glUniform1i = NULL;

PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = NULL;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = NULL;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = NULL;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer = NULL;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage = NULL;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = NULL;
PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture = NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = NULL;
PFNGLDRAWBUFFERSPROC glDrawBuffers = NULL;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = NULL;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers = NULL;

PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;

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

	glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
	if (glUniform4f == NULL)
	{
		throw new ShaderException("failed to retrieve glUniform4f function pointer.");
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

	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	if (glUniform1i == NULL)
	{
		throw new ShaderException("failed to retrieve glUniform1i function pointer.");
	}

	glUniform1uiv = (PFNGLUNIFORM1UIVPROC)wglGetProcAddress("glUniform1uiv");
	if (glUniform1uiv == NULL)
	{
		throw new ShaderException("failed to retrieve glUniform1uiv function pointer.");
	}

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	if (glUniformMatrix4fv == NULL)
	{
		throw new ShaderException("failed to retrieve glUniformMatrix4fv function pointer.");
	}

	glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
	if (glGenFramebuffers == NULL)
	{
		throw new ShaderException("failed to retrieve glGenFramebuffers function pointer.");
	}

	glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
	if (glBindFramebuffer == NULL)
	{
		throw new ShaderException("failed to retrieve glBindFramebuffer function pointer.");
	}

	glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
	if (glGenRenderbuffers == NULL)
	{
		throw new ShaderException("failed to retrieve glGenRenderbuffers function pointer.");
	}

	glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
	if (glBindRenderbuffer == NULL)
	{
		throw new ShaderException("failed to retrieve glBindRenderbuffer function pointer.");
	}

	glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
	if (glRenderbufferStorage == NULL)
	{
		throw new ShaderException("failed to retrieve glRenderbufferStorage function pointer.");
	}

	glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
	if (glFramebufferRenderbuffer == NULL)
	{
		throw new ShaderException("failed to retrieve glFramebufferRenderbuffer function pointer.");
	}

	glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)wglGetProcAddress("glFramebufferTexture");
	if (glFramebufferTexture == NULL)
	{
		throw new ShaderException("failed to retrieve glFramebufferTexture function pointer.");
	}

	glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
	if (glFramebufferTexture2D == NULL)
	{
		throw new ShaderException("failed to retrieve glFramebufferTexture2D function pointer.");
	}

	glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");
	if (glCheckFramebufferStatus == NULL)
	{
		throw new ShaderException("failed to retrieve glCheckFramebufferStatus function pointer.");
	}

	glDrawBuffers = (PFNGLDRAWBUFFERSPROC)wglGetProcAddress("glDrawBuffers");
	if (glDrawBuffers == NULL)
	{
		throw new ShaderException("failed to retrieve glDrawBuffers function pointer.");
	}

	glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers");
	if (glDeleteFramebuffers == NULL)
	{
		throw new ShaderException("failed to retrieve glDeleteFramebuffers function pointer.");
	}

	glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffers");
	if (glDeleteRenderbuffers == NULL)
	{
		throw new ShaderException("failed to retrieve glDeleteRenderbuffers function pointer.");
	}

	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	if (glActiveTexture == NULL)
	{
		throw new ShaderException("failed to retrieve glActiveTexture function pointer.");
	}


}

