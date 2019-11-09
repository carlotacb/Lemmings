#ifndef _PERCENTAGEDISPLAY_INCLUDE
#define _PERCENTAGEDISPLAY_INCLUDE

#include "Sprite.h"

class PercentageDisplay
{
public:
	void init();
	void displayPercentage(int num);
	void render();
	void setPosition(glm::vec2 position);

private:
	glm::vec2 position;
	Sprite *firstNum;
	Sprite *secondNum;
	Sprite *thirdNum;
	Sprite *percentage;

};

#endif // _PERCENTAGEDISPLAY_INCLUDE


