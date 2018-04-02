#ifndef _MOUSEMANAGER_INCLUDE
#define _MOUSEMANAGER_INCLUDE

#include "Job.h"


class MouseManager
{

public:
	static MouseManager &getInstance()
	{
		static MouseManager instance; // Guaranteed to be destroyed.
							// Instantiated on first use.
		return instance;
	};

	enum ScreenArea {
		MAP,
		UI
	};


	enum MouseStates {
		NONE,
		LEFT_MOUSE_PRESSED,
		RIGHT_MOUSE_PRESSED
	};

	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton);

private:
	ScreenArea getScreenArea(int mouseX, int mouseY);

	void leftClickOnUI(int posX, int posY);
	void activateButton(int buttonIndex);

	void leftClickOnMap(int posX, int posY);

private:
	MouseStates mouseState = NONE;
	Job *jobToAssign = NULL;
};
#endif // _MOUSEMANAGER_INCLUDE

