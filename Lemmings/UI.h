#ifndef _UI_INCLUDE
#define _UI_INCLUDE

#include "Button.h"
#include "Texture.h"
#include "Sprite.h"
#include "Job.h"
#include "NumDisplayGreen.h"
#include "PercentageDisplay.h"
#include "TimeDisplay.h"


class UI
{

public:
	static UI &getInstance()
	{
		static UI instance; // Guaranteed to be destroyed.
							   // Instantiated on first use.
		return instance;
	};

	void init();
	void update();
	void render();
	void setPosition(glm::vec2 position);

	int getButtonIndexInPos(int posX, int posY);
	void changeSelectedButton(int selectedButton);
	int getSelectedButtonJobCount();

	void changeDisplayedJob(string lemmingJobName);

private:
	static const int NUM_BUTTONS = 13;

	glm::vec2 position;

	Button buttons[NUM_BUTTONS];

	Texture backgroundTexture;
	Sprite *background;
	
	Sprite *jobName;

	Sprite *outWord;
	NumDisplayGreen numberOutLemmings;

	Sprite *inWord;
	PercentageDisplay numberInLemmings;
	
	Sprite *timeWord;
	TimeDisplay time;
	


	int selectedButton = -1;
	Texture selectFrameTexture;
	Sprite *selectFrame;
};

#endif // _UI_INCLUDE


