#ifndef _INFOLEVELKEYBOARDMANAGER_INCLUDE
#define _INFOLEVELKEYBOARDMANAGER_INCLUDE

#include "KeyboardManager.h"

class InfoLevelKeyboardManager : public KeyboardManager
{

public:
	static InfoLevelKeyboardManager &getInstance()
	{
		static InfoLevelKeyboardManager instance; // Guaranteed to be destroyed.
									  // Instantiated on first use.
		return instance;
	};

	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);


private:
	
};
#endif // _INFOLEVELKEYBOARDMANAGER_INCLUDE