#ifndef _TRAPDOOR_INCLUDE
#define _TRAPDOOR_INCLUDE

#include "Sprite.h"


class Trapdoor
{

public:
	virtual void init() = 0;
	void update(int deltaTime);
	void render();

	void setPosition(glm::vec2 position);
	glm::vec2 getPosition();
	glm::vec2 getEnterPosition();

	bool isOpened();

protected:
	Sprite *trapdoorSprite;
	glm::vec2 enterOffset;

	bool opened = false;
};


#endif // _TRAPDOOR_INCLUDE

