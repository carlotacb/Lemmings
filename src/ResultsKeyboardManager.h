#ifndef _RESULTSKEYBOARDMANAGER_INCLUDE
#define _RESULTSKEYBOARDMANAGER_INCLUDE

#include "KeyboardManager.h"

class ResultsKeyboardManager : public KeyboardManager
{

public:
	static ResultsKeyboardManager &getInstance()
	{
		static ResultsKeyboardManager instance; // Guaranteed to be destroyed.
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