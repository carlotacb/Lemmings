#ifndef _KEYBOARDMANAGER_INCLUDE
#define _KEYBOARDMANAGER_INCLUDE



class KeyboardManager
{

public:
	virtual void keyPressed(int key) = 0;
	virtual void keyReleased(int key) = 0;
	virtual void specialKeyPressed(int key) = 0;
	virtual void specialKeyReleased(int key) = 0;
	
};
#endif // _KEYBOARDMANAGER_INCLUDE