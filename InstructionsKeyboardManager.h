#ifndef _INSTRUCTIONSKEYBOARDMANAGER_INCLUDE
#define _INSTRUCTIONSKEYBOARDMANAGER_INCLUDE

#include "KeyboardManager.h"

class InstructionsKeyboardManager : public KeyboardManager
{

public:
	static InstructionsKeyboardManager &getInstance()
	{
		static InstructionsKeyboardManager instance; // Guaranteed to be destroyed.
									  // Instantiated on first use.
		return instance;
	};

	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);


private:
	
};
#endif // _INSTRUCTIONSKEYBOARDMANAGER_INCLUDE