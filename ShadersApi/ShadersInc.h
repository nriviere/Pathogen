#ifndef SHADERSINC_H
#define SHADERSINC_H

#include "stdafx.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\GLExt.h>
#include <gl\wglext.h>
#include "ShaderException.h"

extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLDELETEPROGRAMPROC  glDeleteProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLUSEPROGRAMPROC glUseProgram;

extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORM1FVPROC  glUniform1fv;
extern PFNGLUNIFORM4FVPROC  glUniform4fv;
extern PFNGLUNIFORM1UIPROC  glUniform1ui;

void initApi() throw (ShaderException);

#endif