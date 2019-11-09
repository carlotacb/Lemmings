#ifndef _CREDITSKEYBOARDMANAGER_INCLUDE
#define _CREDITSKEYBOARDMANAGER_INCLUDE

#include "KeyboardManager.h"

class CreditsKeyboardManager : public KeyboardManager
{

public:
	static CreditsKeyboardManager &getInstance()
	{
		static CreditsKeyboardManager instance; // Guaranteed to be destroyed.
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