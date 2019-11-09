#ifndef _MENUMOUSEMANAGER_INCLUDE
#define _MENUMOUSEMANAGER_INCLUDE

#include "MouseManager.h"

class MenuMouseManager : public MouseManager
{

public:
	static MenuMouseManager &getInstance()
	{
		static MenuMouseManager instance; // Guaranteed to be destroyed.
							// Instantiated on first use.
		return instance;
	};

	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {};

};
#endif // _MOUSEMANAGER_INCLUDE

