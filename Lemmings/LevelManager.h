#ifndef _LEVELMANAGER_INCLUDE
#define _LEVELMANAGER_INCLUDE

#include <set>
#include "Lemming.h"
#include "Level.h"
#include "Door.h"
#include "Trapdoor.h"

class LevelManager
{

public:
	static LevelManager &getInstance()
	{
		static LevelManager instance;
		return instance;
	};

	enum JobPosition {
		CLIMBER,
		FLOATER,
		BOMBER,
		BLOCKER,
		BUILDER,
		BASHER,
		MINNER,
		DIGGER
	};

	void init(string levelMode, int levelNum);
	void update(int deltaTime);
	void render();

	bool finished();

	void spawnLemmings();
	int getNumLemmingsAlive();
	int getPercentageSavedLemmings();
	int getPercentageTotalLemmings();

	void stopSpawningLemmings();

	bool assignJob(int lemmingIndex, Job *jobToAssign);
	int getLemmingIndexInPos(int posX, int posY);
	string getLemmingJobNameIndex(int index);

	int getCurrentTime();
	int getRemainingTime();

	void apocalypsis();

	int getReleaseRate();
	int getMinReleaseRate();
	void decreaseReleaseRate();
	void increaseReleaseRate();

	int getActualLevel();
	int getActualMode();

	int getJobCount(int index);
	void decreaseJobCount(int index);

private:
	int *jobCount;
	set<Lemming*> lemmings;

	int deadLemmings;
	int savedLemmings;
	int goalLemmingNum;
	int releaseRate;
	int minReleaseRate;
	int availableLemmings;

	int actualLevel;
	int actualMode;

	int goalTime;
	float currentTime;
	int lastTimeSpawnedLemming;

	bool spawningLemmings;
	bool finishedLevel;

	Door* door;
	Trapdoor* trapdoor;

	void finishLevel();
	void updateLemmings(int deltaTime);
	void renderLemmings();


};

#endif // _LEVELMANAGER_INCLUDE