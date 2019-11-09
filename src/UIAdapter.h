#ifndef _UIADAPTER_INCLUDE
#define _UIADAPTER_INCLUDE
#include "Sprite.h"

class UIAdapter
{

public:

	static UIAdapter &getInstance()
	{
		static UIAdapter instance; // Guaranteed to be destroyed.
							   // Instantiated on first use.
		return instance;
	};

	void changeFocusedLemming(int lemmingIndex);
	void changeSelectedButton(int buttonIndex);
	void changeJobName(Sprite *jobNameSprite, string jobName);

private:
	void activateButton(int buttonIndex);
};

#endif // _UIADAPTER_INCLUDE


