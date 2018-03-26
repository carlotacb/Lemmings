#ifndef _VARIABLE_TEXTURE_INCLUDE
#define _VARIABLE_TEXTURE_INCLUDE


#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "common_defs.h"


using namespace std;


// The texture class loads images an passes them to OpenGL
// storing the returned id so that it may be applied to any drawn primitives


class VariableTexture
{

public:
	VariableTexture();
	~VariableTexture();

	bool loadFromFile(const string &filename, PixelFormat imageFormat);
	void loadFromGlyphBuffer(unsigned char *buffer, int width, int height);

	void createEmptyTexture(int width, int height);
	void loadSubtextureFromGlyphBuffer(unsigned char *buffer, int x, int y, int width, int height);
	void generateMipmap();
	
	void setWrapS(GLint value);
	void setWrapT(GLint value);
	void setMinFilter(GLint value);
	void setMagFilter(GLint value);
	
	void use() const;
	
	int width() const { return widthTex; }
	int height() const { return heightTex; }
	
	unsigned char pixel(unsigned int x, unsigned int y) const;
	void setPixel(unsigned int x, unsigned int y, unsigned char value);
	void setPixel(unsigned int x, unsigned int y, const glm::ivec3 & value);
	void setPixel(unsigned int x, unsigned int y, const glm::ivec4 & value);
	void saveBMP(const string &filename);

private:
	PixelFormat format;
	int widthTex, heightTex;
	unsigned char *image;
	GLuint texId;
	GLint wrapS, wrapT, minFilter, magFilter;

};


#endif // _VARIABLE_TEXTURE_INCLUDE

