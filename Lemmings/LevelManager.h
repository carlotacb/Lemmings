#ifndef _LEVELMANAGER_INCLUDE
#define _LEVELMANAGER_INCLUDE

#include "InfoLevel.h"
#include "Lemming.h"
#include "Level.h"

class LevelManager
{

public:
	static LevelManager &instance()
	{
		static LevelManager instance;
		return instance;
	};

	void infoLevel(int level, int mode);
	void initLevel(Level::LevelAttributes *levelAttributes, float newCurrentTime);
	int getActualMode();
	int getActualLevel();
	void changeLevel(int levelNum, int levelMode);
	void lemmingSaved();
	void lemmingDied();
	void lemmingAppear();
	void updateLemmings(int deltaTime);
	void spawnLemmings();

private:
	int actualLevel;
	int actualMode; // FUN = 1; TRICKY = 2; TAXING = 3;
	int lemmingsInLevel;
	int lemmingsDied;
	int lemmingsSaved;
	int lemmingsToBeSaved;
	int levelLemmings;
	int totalTime;
	float cTime;
	float startedTime;
	vector<Lemming> lemmings;
	vector<bool> alive;

};

#endif // _LEVELMANAGER_INCLUDE