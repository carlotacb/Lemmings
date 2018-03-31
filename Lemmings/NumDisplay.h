#ifndef _NUMDISPLAY_INCLUDE
#define _NUMDISPLAY_INCLUDE

#include "Texture.h"
#include "Sprite.h"

// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class NumDisplay
{

public:
	void init();
	void displayNum(int num);
	void render();
	void setPosition(glm::vec2 position);

private:
	glm::vec2 position;

	Texture backgroundTexture;

	Sprite *background;
	Sprite *leftNum;
	Sprite *rightNum;

};

#endif // _NUMDISPLAY_INCLUDE


