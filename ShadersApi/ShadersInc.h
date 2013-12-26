#ifndef SHADERSINC_H
#define SHADERSINC_H

#include "stdafx.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\GLExt.h>
#include <gl\wglext.h>
#include "ShaderException.h"

extern PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
extern PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

extern PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB;
extern PFNGLDELETEPROGRAMSARBPROC  glDeleteProgramsARB;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLLINKPROGRAMARBPROC glLinkProgramARB;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB;

extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORM1FVPROC  glUniform1fv;
extern PFNGLUNIFORM4FVPROC  glUniform4fv;
extern PFNGLUNIFORM1UIVPROC glUniform1uiv;
extern PFNGLUNIFORM4FPROC  glUniform4f;
extern PFNGLUNIFORM1UIPROC  glUniform1ui;
extern PFNGLUNIFORM1FPROC  glUniform1f;
extern PFNGLUNIFORM1IPROC  glUniform1i;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
extern PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
extern PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
extern PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
extern PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
extern PFNGLDRAWBUFFERSPROC glDrawBuffers;
extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
extern PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;

extern PFNGLACTIVETEXTUREPROC glActiveTexture;



void initApi() throw (ShaderException);

#endif