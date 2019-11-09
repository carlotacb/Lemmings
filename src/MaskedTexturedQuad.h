#ifndef _MASKED_TEXTURED_QUAD_INCLUDE
#define _MASKED_TEXTURED_QUAD_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "VariableTexture.h"
#include "ShaderProgram.h"


class MaskedTexturedQuad
{

public:
	// Textured quads can only be created inside an OpenGL context
	static MaskedTexturedQuad *createTexturedQuad(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program);

	MaskedTexturedQuad(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program);

	void render(ShaderProgram &program, const Texture &tex, const VariableTexture &mask) const;
	void free();

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;

};


#endif // _MASKED_TEXTURED_QUAD_INCLUDE

