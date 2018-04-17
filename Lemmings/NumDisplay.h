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
	virtual void setPosition(glm::vec2 position) = 0;

protected:
	virtual void displayNumAux(int firstDigit, int secondDigit) = 0;

protected:
	glm::vec2 position;
	Sprite *leftNum;
	Sprite *rightNum;

};

#endif // _NUMDISPLAY_INCLUDE


