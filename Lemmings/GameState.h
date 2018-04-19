#ifndef _GAMESTATE_INCLUDE
#define _GAMESTATE_INCLUDE

#include "Game.h"

class GameState
{

public:

	static GameState &instance()
	{
		static GameState instance;
		return instance;
	};

	int getCurrentState();
	void setCurrentState(int newState);

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
	

private:
	int currentState; // 0 = Menu, 1 = Playing, 2 = Instructions, 3 = About
	bool keys[256], specialKeys[256]; // Store key states so that 
									  // we can have access at any time
	int mouseX, mouseY;               // Mouse position
	bool bLeftMouse, bRightMouse;     // Mouse button states
};


#endif // _GAMESTATE_INCLUDE

