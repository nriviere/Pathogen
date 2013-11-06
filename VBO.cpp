#include "VBO.h"
#include <exception>

 PFNGLGENVERTEXARRAYSPROC glGenVertexArrays= NULL;
 PFNGLBINDVERTEXARRAYPROC glBindVertexArray= NULL;
 PFNGLGENBUFFERSPROC  glGenBuffers= NULL;
 PFNGLBINDBUFFERPROC glBindBuffer= NULL;
 PFNGLBUFFERDATAPROC glBufferData= NULL;
 PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer= NULL;
 PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray= NULL;
 PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray= NULL;
 PFNGLDELETEBUFFERSPROC glDeleteBuffers= NULL;
 PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays= NULL;
 PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = NULL;
 PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;

void init_vbo()
{
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	if (glGenVertexArrays == NULL)
	{
		throw new std::exception("failed to retrieve glGenVertexArrays function pointer.");
	}

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	if (glBindVertexArray == NULL)
	{
		throw new std::exception("failed to retrieve glCreateShader function pointer.");
	}

	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	if (glGenBuffers == NULL)
	{
		throw new std::exception("failed to retrieve glGenBuffers function pointer.");
	}

	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	if (glBindBuffer == NULL)
	{
		throw new std::exception("failed to retrieve glBindBuffer function pointer.");
	}

	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	if (glBufferData == NULL)
	{
		throw new std::exception("failed to retrieve glBufferData function pointer.");
	}

	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	if (glVertexAttribPointer == NULL)
	{
		throw new std::exception("failed to retrieve glVertexAttribPointer function pointer.");
	}

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	if (glEnableVertexAttribArray == NULL)
	{
		throw new std::exception("failed to retrieve glEnableVertexAttribArray function pointer.");
	}

	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	if (glDisableVertexAttribArray == NULL)
	{
		throw new std::exception("failed to retrieve glDisableVertexAttribArray function pointer.");
	}

	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	if (glDeleteBuffers == NULL)
	{
		throw new std::exception("failed to retrieve glDeleteBuffers function pointer.");
	}

	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	if (glDeleteVertexArrays == NULL)
	{
		throw new std::exception("failed to retrieve glDeleteVertexArrays function pointer.");
	}

	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	if (glBindAttribLocation == NULL)
	{
		throw new std::exception("failed to retrieve glBindAttribLocation function pointer.");
	}

	glBufferSubData = (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubData");
	if (glBufferSubData == NULL)
	{
		throw new std::exception("failed to retrieve glBufferSubData function pointer.");
	}
}
