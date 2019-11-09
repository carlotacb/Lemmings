#ifndef _TIMEDISPLAY_INCLUDE
#define _TIMEDISPLAY_INCLUDE

#include "Sprite.h"

class TimeDisplay
{
public:
	void init();
	void displayTime(int time);
	void render();
	void setPosition(glm::vec2 position);

private:
	glm::vec2 position;
	Sprite *minutes;
	Sprite *firstDigitSeconds;
	Sprite *secondDigitSeconds;
	Sprite *hyphen;

};

#endif // _TIMEDISPLAY_INCLUDE


