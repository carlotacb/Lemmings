#include <fstream>
#include "Shader.h"


using namespace std;


Shader::Shader()
{
	shaderId = 0;
	compiled = false;
}


void Shader::initFromSource(const ShaderType type, const string &source)
{
	const char *sourcePtr = source.c_str();
	GLint status;
	char buffer[512];

	switch(type)
	{
	case VERTEX_SHADER:
		shaderId = glCreateShader(GL_VERTEX_SHADER);
		break;
	case FRAGMENT_SHADER:
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}
	if(shaderId == 0)
		return;
	glShaderSource(shaderId, 1, &sourcePtr, NULL);
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	compiled = (status == GL_TRUE);
	glGetShaderInfoLog(shaderId, 512, NULL, buffer);
	errorLog.assign(buffer);
}

bool Shader::initFromFile(const ShaderType type, const string &filename)
{
	string shaderSource;

	if(!loadShaderSource(filename, shaderSource))
		return false;
	initFromSource(type, shaderSource);

	return true;
}

void Shader::free()
{
	glDeleteShader(shaderId);
	shaderId = 0;
	compiled = false;
}

GLuint Shader::getId() const
{
	return shaderId;
}

bool Shader::isCompiled() const
{
	return compiled;
}

const string &Shader::log() const
{
	return errorLog;
}

bool Shader::loadShaderSource(const string &filename, string &shaderSource)
{
	ifstream fin;

	fin.open(filename.c_str());
	if(!fin.is_open())
		return false;
	shaderSource.assign(istreambuf_iterator<char>(fin), istreambuf_iterator<char>());

	return true;
}

