#ifndef _DOOR_INCLUDE
#define _DOOR_INCLUDE

#include "Sprite.h"


class Door
{

public:
	virtual void init() = 0;
	void update(int deltaTime);
	void render();
	
	void setPosition(glm::vec2 position);
	glm::vec2 getPosition();
	glm::vec2 getEscapePosition();

protected:
	Sprite *doorSprite;
	glm::vec2 escapeOffset;
};


#endif // _DOORSTANDARD_INCLUDE

