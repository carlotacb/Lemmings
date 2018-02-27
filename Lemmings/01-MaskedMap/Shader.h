#ifndef _SHADER_INCLUDE
#define _SHADER_INCLUDE


#include <string>
#include <GL/glew.h>
#include <GL/gl.h>


using namespace std;


enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER };


// This class is able to load to OpenGL a vertex or fragment shader and compile it.
// It can do so from a file or from a string so that shader code can be
// procedurally modified if needed.


class Shader
{

public:
	Shader();

	// These methods should be called with an active OpenGL context
	void initFromSource(const ShaderType type, const string &source);
	bool initFromFile(const ShaderType type, const string &filename);
	void free();

	GLuint getId() const;
	bool isCompiled() const;
	const string &log() const;

private:
	bool loadShaderSource(const string &filename, string &shaderSource);

private:
	GLuint shaderId;
	bool compiled;
	string errorLog;

};


#endif // _SHADER_INCLUDE
