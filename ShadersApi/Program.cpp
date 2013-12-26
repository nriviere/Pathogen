#include "Program.h"
#include "MyEngine.h"
list<unsigned int> Program::current_program = list<unsigned int>();

Program::Program()
{
	ID = glCreateProgramObjectARB();
	shaders[0] = shaders[1] = NULL;
	shader_count = 0;
	in_use = false;
}


Program::~Program()
{
	if (ID != 0)
	{
		glDeleteProgramsARB(1,&ID);
	}
}

unsigned int Program::getID()
{
	return ID;
}

Shader **Program::getShaders(unsigned int *shader_count)
{
	*shader_count = this->shader_count;
	return shaders;
}

void Program::setShader(Shader *shader, unsigned int position)
{
	if (shaders[position] != NULL)
	{
		glDetachShader(ID,shaders[position]->getID());
	}
	shaders[position] = shader;
	glAttachShader(ID, shader->getID());
}

void Program::removeShader(unsigned int position)
{
	glDetachShader(ID, shaders[position]->getID());
	shaders[position] = NULL;
}

void Program::linkProgram()
{
	glLinkProgramARB(ID);
	GLint result;
	glGetProgramiv(ID, GL_LINK_STATUS, &result);
	if (result != GL_TRUE)
	{
		GLint logsize = 0, length = 0;
		glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &logsize);
		char * log = new char[logsize];
		glGetProgramInfoLog(ID, logsize, &length, log);
		//MyEngine::errlog << "Linking failed" << endl;
		ShaderException *e = new ShaderException(log);
		delete[] log;
		throw e;
	}
}

void Program::start()
{
	glUseProgramObjectARB(ID);
	Program::current_program.push_back(ID);
	in_use = true;
}

void Program::stop()
{
	if (in_use == true)
	{
		Program::current_program.pop_back();
	}
	if (Program::current_program.empty())
	{
		glUseProgramObjectARB(0);
	}
	else
	{
		glUseProgramObjectARB(Program::current_program.back());
	}
}