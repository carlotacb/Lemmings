#include "Utils.h"

bool Utils::insideRectangle(glm::vec2 point, glm::vec2 rectangleOrigin, glm::vec2 rectangleSize)
{
	return (
		rectangleOrigin.x <= point.x
		&& point.x < rectangleOrigin.x + rectangleSize.x
		&& rectangleOrigin.y <= point.y
		&& point.y < rectangleOrigin.y + rectangleSize.y
		);
}

void Utils::changeTexelColor(GLuint id, GLint x, GLint y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	uint8_t data[4];
	data[0] = r;
	data[1] = g;
	data[2] = b;
	data[3] = a;
	glBindTexture(GL_TEXTURE_2D, id);
	glTexSubImage2D(GL_TEXTURE_2D,
		0,
		x,
		y,
		1,
		1,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data);
}