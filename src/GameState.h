#ifndef _GAMESTATE_INCLUDE
#define _GAMESTATE_INCLUDE

#include "MouseManager.h"
#include "KeyboardManager.h"

class GameState
{

public:

	virtual void init() = 0;
	virtual void update(int deltaTime) = 0;
	virtual void render() = 0;

	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	

protected:
	MouseManager *mouseManager;
	KeyboardManager *keyboardManager;
	float currentTime;

private:

	bool keys[256], specialKeys[256]; // Store key states so that 
									  // we can have access at any time
	int mouseX, mouseY;               // Mouse position
	bool bLeftMouse, bRightMouse;     // Mouse button states
	
	

};


#endif // _GAMESTATE_INCLUDE

