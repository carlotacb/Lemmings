#ifndef _INSTRUCTIONSMOUSEMANAGER_INCLUDE
#define _INSTRUCTIONSMOUSEMANAGER_INCLUDE

#include "MouseManager.h"

class InstructionsMouseManager : public MouseManager
{

public:
	static InstructionsMouseManager &getInstance()
	{
		static InstructionsMouseManager instance; // Guaranteed to be destroyed.
							// Instantiated on first use.
		return instance;
	};

	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) {};

};
#endif // _INSTRUCTIONSMOUSEMANAGER_INCLUDE

