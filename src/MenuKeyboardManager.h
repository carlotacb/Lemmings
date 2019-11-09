#ifndef _MENUKEYBOARDMANAGER_INCLUDE
#define _MENUKEYBOARDMANAGER_INCLUDE

#include "KeyboardManager.h"

class MenuKeyboardManager : public KeyboardManager
{

public:
	static MenuKeyboardManager &getInstance()
	{
		static MenuKeyboardManager instance; // Guaranteed to be destroyed.
									  // Instantiated on first use.
		return instance;
	};

	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);


private:
	
};
#endif // _KEYBOARDMANAGER_INCLUDE