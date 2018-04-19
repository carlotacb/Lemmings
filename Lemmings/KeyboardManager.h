#ifndef _KEYBOARDMANAGER_INCLUDE
#define _KEYBOARDMANAGER_INCLUDE

#include <GL/glew.h>
#include <GL/glut.h>
#include "LevelManager.h"
#include "GameState.h"

class KeyboardManager
{

public:
	static KeyboardManager &getInstance()
	{
		static KeyboardManager instance; // Guaranteed to be destroyed.
									  // Instantiated on first use.
		return instance;
	};

	
public:
	void menuControlSpecialKey(int key, int mode);

private:
	
};
#endif // _KEYBOARDMANAGER_INCLUDE