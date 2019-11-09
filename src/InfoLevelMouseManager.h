#ifndef _INFOLEVELMOUSEMANAGER_INCLUDE
#define _INFOLEVELMOUSEMANAGER_INCLUDE

#include "MouseManager.h"

class InfoLevelMouseManager : public MouseManager
{

public:
	static InfoLevelMouseManager &getInstance()
	{
		static InfoLevelMouseManager instance; // Guaranteed to be destroyed.
							// Instantiated on first use.
		return instance;
	};

	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {};

};
#endif // _INFOLEVELMOUSEMANAGER_INCLUDE

