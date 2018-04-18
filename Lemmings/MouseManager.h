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

	enum ScreenClickedArea {
		MAP,
		UI
	};

	enum ScreenMovedArea {
		SCROLL_AREA,
		LEVEL
	};


	enum MouseStates {
		NONE,
		LEFT_MOUSE_PRESSED,
		RIGHT_MOUSE_PRESSED
	};

	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton);
	void update();

private:
	ScreenClickedArea getClickedScreenArea(int mouseX, int mouseY);
	ScreenMovedArea getMovedScreenArea(int mouseX, int mouseY);

	void leftClickOnUI(int posX, int posY);
	void leftClickOnMap(int posX, int posY);

private:
	int posX, posY;

	MouseStates mouseState = NONE;
	ScreenMovedArea screenMovedArea;
};
#endif // _MOUSEMANAGER_INCLUDE

