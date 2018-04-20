#ifndef _STATEMANAGER_INCLUDE
#define _STATEMANAGER_INCLUDE

#include "GameState.h"

class StateManager
{

public:

	static StateManager &instance()
	{
		static StateManager instance;
		return instance;
	};

	void changeMenu();
	void changeInfo(int levelMode, int levelNum);
	void changeScene(int levelMode, int levelNum);
	void changeResults(int goalPercentage, int currentPercentage);
	void changeCredits();
	void changeInstructions();

private:
	GameState *gameState;
};


#endif // _GAMESTATE_INCLUDE