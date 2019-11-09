#include <SOIL.h>
#include "VariableTexture.h"


using namespace std;


VariableTexture::VariableTexture()
{
	wrapS = GL_REPEAT;
	wrapT = GL_REPEAT;
	minFilter = GL_LINEAR_MIPMAP_LINEAR;
	magFilter = GL_LINEAR_MIPMAP_LINEAR;
	image = NULL;
}

VariableTexture::~VariableTexture()
{
	if(image != NULL)
		delete [] image;
}


bool VariableTexture::loadFromFile(const string &filename, PixelFormat imageFormat)
{
	format = imageFormat;
	switch(format)
	{
	case TEXTURE_PIXEL_FORMAT_RGB:
		image = SOIL_load_image(filename.c_str(), &widthTex, &heightTex, 0, SOIL_LOAD_RGB);
		break;
	case TEXTURE_PIXEL_FORMAT_RGBA:
		image = SOIL_load_image(filename.c_str(), &widthTex, &heightTex, 0, SOIL_LOAD_RGBA);
		break;
	case TEXTURE_PIXEL_FORMAT_L:
		image = SOIL_load_image(filename.c_str(), &widthTex, &heightTex, 0, SOIL_LOAD_L);
		break;
	}
	if(image == NULL)
		return false;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	switch(format)
	{
	case TEXTURE_PIXEL_FORMAT_RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthTex, heightTex, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		break;
	case TEXTURE_PIXEL_FORMAT_RGBA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthTex, heightTex, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		break;
	case TEXTURE_PIXEL_FORMAT_L:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, widthTex, heightTex, 0, GL_RED, GL_UNSIGNED_BYTE, image);
		break;
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	
	return true;
}

void VariableTexture::loadFromGlyphBuffer(unsigned char *buffer, int width, int height)
{
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void VariableTexture::createEmptyTexture(int width, int height)
{
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void VariableTexture::loadSubtextureFromGlyphBuffer(unsigned char *buffer, int x, int y, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, texId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RED, GL_UNSIGNED_BYTE, buffer);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void VariableTexture::generateMipmap()
{
	glBindTexture(GL_TEXTURE_2D, texId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenerateMipmap(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void VariableTexture::setWrapS(GLint value)
{
	wrapS = value;
}

void VariableTexture::setWrapT(GLint value)
{
	wrapT = value;
}

void VariableTexture::setMinFilter(GLint value)
{
	minFilter = value;
}

void VariableTexture::setMagFilter(GLint value)
{
	magFilter = value;
}

void VariableTexture::use() const
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId);
	switch(format)
	{
	case TEXTURE_PIXEL_FORMAT_RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthTex, heightTex, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		break;
	case TEXTURE_PIXEL_FORMAT_RGBA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthTex, heightTex, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		break;
	case TEXTURE_PIXEL_FORMAT_L:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, widthTex, heightTex, 0, GL_RED, GL_UNSIGNED_BYTE, image);
		break;
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

unsigned char VariableTexture::pixel(unsigned int x, unsigned int y) const
{
	if(format == TEXTURE_PIXEL_FORMAT_RGB)
		return image[3 * (y * widthTex + x)];
	else if(format == TEXTURE_PIXEL_FORMAT_RGBA)
		return image[4 * (y * widthTex + x)];
	else
		return image[y * widthTex + x];
}

void VariableTexture::setPixel(unsigned int x, unsigned int y, unsigned char value)
{
	if(format == TEXTURE_PIXEL_FORMAT_L)
	{
		image[y * widthTex + x] = value;
	}
}

void VariableTexture::setPixel(unsigned int x, unsigned int y, const glm::ivec3 & value)
{
	if(format == TEXTURE_PIXEL_FORMAT_RGB)
	{
		image[3*(y * widthTex + x)] = value.r;
		image[3*(y * widthTex + x) + 1] = value.g;
		image[3*(y * widthTex + x) + 2] = value.b;
	}
}

void VariableTexture::setPixel(unsigned int x, unsigned int y, const glm::ivec4 & value)
{
	if(format == TEXTURE_PIXEL_FORMAT_RGBA)
	{
		image[4*(y * widthTex + x)] = value.r;
		image[4*(y * widthTex + x) + 1] = value.g;
		image[4*(y * widthTex + x) + 2] = value.b;
		image[4*(y * widthTex + x) + 3] = value.a;
	}
}

void VariableTexture::saveBMP(const string &filename)
{
	if(format == TEXTURE_PIXEL_FORMAT_RGB)
		SOIL_save_image(filename.c_str(), SOIL_SAVE_TYPE_BMP, widthTex, heightTex, 3, image);
	else
		SOIL_save_image(filename.c_str(), SOIL_SAVE_TYPE_BMP, widthTex, heightTex, 4, image);
}







