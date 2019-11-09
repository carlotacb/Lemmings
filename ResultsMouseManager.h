#ifndef _RESULTSMOUSEMANAGER_INCLUDE
#define _RESULTSMOUSEMANAGER_INCLUDE

#include "MouseManager.h"

class ResultsMouseManager : public MouseManager
{

public:
	static ResultsMouseManager &getInstance()
	{
		static ResultsMouseManager instance; // Guaranteed to be destroyed.
							// Instantiated on first use.
		return instance;
	};

	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {};

};
#endif // _RESULTSMOUSEMANAGER_INCLUDE

