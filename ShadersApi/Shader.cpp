#include "Shader.h"
#include <fstream>
#include <sstream>


using namespace std;


Shader::Shader()
{
	shaderStr = NULL;
	ID = UINT_MAX;
	type = -1;
}

Shader::Shader(const char *filename, GLenum type)
{
	this->filename = string(filename) ;
	this->type = type;
}


Shader::~Shader()
{
	if (ID != 0)
	{
		glDeleteShader(ID);
	}
}

void Shader::init() throw (ShaderException)
{
	if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER)
	{
		throw new ShaderException("Failed to create shader identifier : missing type");
	}
	ID = glCreateShader(type);
	if (ID == 0)
	{
		throw new ShaderException("Failed to create shader identifier");
	}
}

void Shader::loadSource(const char *filename) throw (ShaderException)
{
	const char *f = filename;
	if (f == NULL)
	{
		if (this->filename.length() == 0)
		{
			throw new ShaderException("Failed to load shader source : missing filename");
		}
		else{
			f = this->filename.c_str();
		}
	}
	ifstream file;
	file.open(f);
	if (!file.is_open())
	{
		throw new ShaderException("Failed to load shader source : unable to open selected file");
	}
	std::stringstream ss;
	ss << file.rdbuf();
	int length = ss.str().length();

	if (length == 0 || length < 0){
		ShaderException *e = new ShaderException("Failed to load shader source : empty source file");
		throw e;
	}
	
	shaderStr = new char[length];
	
	strcpy(shaderStr, ss.str().c_str());
	file.close();
}

void Shader::loadShader() throw (ShaderException)
{
	glShaderSource(ID, 1, &shaderStr, NULL);
	glCompileShader(ID);
	GLint result;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &result);

	if (result != GL_TRUE)
	{
		GLint logsize=0,length=0;
		glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logsize);
		char * log = new char[logsize];
		glGetShaderInfoLog(ID, logsize, &length, log);
		ShaderException *e = new ShaderException(log);
		throw e;
	}

	shaderStr = NULL;
}

unsigned int Shader::getID()
{
	return ID;
}