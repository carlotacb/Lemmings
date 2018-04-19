#ifndef _UTILS_INCLUDE
#define _UTILS_INCLUDE

#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

class Utils
{

public:
	static bool insideRectangle(glm::vec2 point, glm::vec2 rectangleOrigin, glm::vec2 rectangleSize);
	static void changeTexelColor(GLuint id, GLint x, GLint y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
};


#endif // _UTILS_INCLUDE

