#ifndef SHADEREXCEPTION_H
#define SHADEREXCEPTION_H
#include <exception>
#include <string>
using namespace std;

class ShaderException : public exception
{
private:
	char *error_message;
	exception *parent;
public:
	ShaderException(const char* error_message = "", exception *parent = NULL) :exception(){
		this->error_message = new char[strlen(error_message)];
		strcpy(this->error_message, error_message);
		this->parent = parent;
	}
	~ShaderException() throw() 
	{ 
		delete parent; 
	}
	const char* what() throw()
	{
		
		if (parent != NULL)
		{
			char *full_message = new char[strlen(error_message) + 1 + strlen(parent->what())];
			strcpy(full_message, error_message);
			full_message[strlen(error_message)] = '\n';
			strcpy(&full_message[strlen(error_message) + 1], parent->what());
			delete [] error_message;
			error_message = full_message;
		}
		return error_message;
	}
};
#endif