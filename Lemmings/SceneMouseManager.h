#ifndef _SCENEMOUSEMANAGER_INCLUDE
#define _SCENEMOUSEMANAGER_INCLUDE

#include "MouseManager.h"
#include "Job.h"


class SceneMouseManager : public MouseManager
{

public:
	static SceneMouseManager &getInstance()
	{
		static SceneMouseManager instance; // Guaranteed to be destroyed.
							// Instantiated on first use.
		return instance;
	};

	enum ScreenClickedArea {
		MAP,
		UI,
		INFO
	};

	enum ScreenMovedArea {
		SCROLL_AREA_LEFT,
		SCROLL_AREA_RIGHT,
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

	void updateCursorPosition();

private:
	int posX, posY;

	MouseStates mouseState = NONE;
	ScreenMovedArea screenMovedArea;
};
#endif // _SCENEMOUSEMANAGER_INCLUDE

