#ifndef _INFOLEVEL_INCLUDE
#define _INFOLEVEL_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"

class InfoLevel {

public:
	static InfoLevel &instance()
	{
		static InfoLevel instance;
		return instance;
	};

	InfoLevel();
	~InfoLevel();
	void init(int mode, int numlevel);
	void update(int deltaTime);
	void render();

private:

	// Functions
	void initShaders();
	void initTextures(int mode, int numlevel);

	// Parametres
	Texture InfoLevelTexture;

	Sprite* InfoLevelSprite;

	ShaderProgram simpleTexProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif