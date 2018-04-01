#ifndef _UI_INCLUDE
#define _UI_INCLUDE

#include "Button.h"
#include "Texture.h"
#include "Sprite.h"


class UI
{

public:
	void init();
	void render();
	void setPosition(glm::vec2 position);

private:
	void changeSelectedButton(int selectedButton);

private:
	static const int NUM_BUTTONS = 12;

	glm::vec2 position;

	Button buttons[NUM_BUTTONS];

	Texture backgroundTexture;
	Sprite *background;

	int selectedButton = -1;
	Texture selectFrameTexture;
	Sprite *selectFrame;
};

#endif // _UI_INCLUDE


