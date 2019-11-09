#ifndef _SCENEKEYBOARDMANAGER_INCLUDE
#define _SCENEKEYBOARDMANAGER_INCLUDE

#include "KeyboardManager.h"

class SceneKeyboardManager : public KeyboardManager
{

public:
	static SceneKeyboardManager &getInstance()
	{
		static SceneKeyboardManager instance; // Guaranteed to be destroyed.
									  // Instantiated on first use.
		return instance;
	};

	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);


private:
	
};
#endif // _SCENEKEYBOARDMANAGER_INCLUDE