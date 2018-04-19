#ifndef _CREDITSMOUSEMANAGER_INCLUDE
#define _CREDITSMOUSEMANAGER_INCLUDE

#include "MouseManager.h"

class CreditsMouseManager : public MouseManager
{

public:
	static CreditsMouseManager &getInstance()
	{
		static CreditsMouseManager instance; // Guaranteed to be destroyed.
							// Instantiated on first use.
		return instance;
	};

	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {};

};
#endif // _CREDITSMOUSEMANAGER_INCLUDE

