#ifndef _LEVELMANAGER_INCLUDE
#define _LEVELMANAGER_INCLUDE

#include "InfoLevel.h"

class LevelManager
{

public:
	static LevelManager &instance()
	{
		static LevelManager instance;
		return instance;
	};

	void infoLevel(int level, int mode);
	void initLevel(int level, int mode, int lemmingsToSave, int totalLemmings, int time);
	int getActualMode();
	int getActualLevel();
	void changeLevel(int levelNum, int levelMode);
	void lemmingSaved();
	void lemmingDied();
	void lemmingAppear();

private:
	int actualLevel;
	int actualMode; // FUN = 1; TRICKY = 2; TAXING = 3;
	int lemmingsInLevel;
	int lemmingsDied;
	int lemmingsSaved;
	int lemmingsToBeSaved;
	int levelLemmings;
	int totalTime;

};

#endif // _LEVELMANAGER_INCLUDE