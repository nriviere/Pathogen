#include "Shader.h"
#include <fstream>
#include <sstream>
#include "MyEngine.h"

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
		MyEngine::errlog << "Failed to create shader identifier : missing type" << endl;
	}
	ID = glCreateShaderObjectARB(type);
	if (ID == 0)
	{
		throw new ShaderException("Failed to create shader identifier");
		//MyEngine::errlog << "Failed to create shader identifier" << endl;
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
			//MyEngine::errlog << "Failed to load shader source : missing filename" << endl;
		}
		else{
			f = this->filename.c_str();
		}
	}
	ifstream file;
	file.open(f);
	MyEngine::errlog << "File Opened Done ..." << endl;
	if (!file.is_open())
	{
		throw new ShaderException("Failed to load shader source : unable to open selected file");
		//MyEngine::errlog << "Failed to load shader source : unable to open selected file" << endl;
	}
	std::stringstream ss;
	ss << file.rdbuf();
	MyEngine::errlog << "File :  " << ss.str() << endl;
	int length = ss.str().length();

	if (length == 0 || length < 0){
		ShaderException *e = new ShaderException("Failed to load shader source : empty source file");
		throw e;
		//MyEngine::errlog << "Failed to load shader source : empty source file" << endl;
	}
	
	shaderStr = new GLcharARB[length+1];
	
	strcpy(shaderStr, ss.str().c_str());
	file.close();
}

void Shader::loadShader() throw (ShaderException)
{
	//MyEngine::errlog << "Compilation" << endl;
	glShaderSourceARB(ID, 1, const_cast<const GLcharARB **>(&shaderStr), NULL);
	glCompileShaderARB(ID);
	//MyEngine::errlog << "Done" << endl;
	GLint result;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &result);

	if (result != GL_TRUE)
	{
		GLint logsize=0,length=0;
		glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logsize);
		char * log = new char[logsize];
		glGetShaderInfoLog(ID, logsize, &length, log);
		//MyEngine::errlog << "compilation failed" << endl;
		ShaderException *e = new ShaderException(log);
		throw e;
	}
	delete shaderStr;
	shaderStr = NULL;
}

unsigned int Shader::getID()
{
	return ID;
}