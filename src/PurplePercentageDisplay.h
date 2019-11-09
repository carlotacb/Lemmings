#ifndef _PURPLEPERCENTAGEDISPLAY_INCLUDE
#define _PURPLEPERCENTAGEDISPLAY_INCLUDE

#include "Sprite.h"

class PurplePercentageDisplay
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

#endif // _PURPLEPERCENTAGEDISPLAY_INCLUDE


