#ifndef _COUNTDOWN_INCLUDE
#define _COUNTDOWN_INCLUDE

#include <glm\glm.hpp>
#include "Sprite.h"

class Countdown
{

public:

	Countdown();
	void render();
	void setPosition(glm::vec2 position);
	void update(int deltaTime);
	bool isOver();

private:
	Sprite *countNum;
	int goalTime;
	bool over;

};

#endif // _COUNTDOWN_INCLUDE


