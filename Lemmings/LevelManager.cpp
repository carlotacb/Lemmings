#include "LevelManager.h"
#include "Scene.h"
#include "StateManager.h"
#include "Lemming.h"
#include "JobFactory.h"
#include <GL/glew.h>
#include <GL/glut.h>

void LevelManager::initLevel(Level::LevelAttributes *levelAttributes, float newCurrentTime)
{
	cTime = newCurrentTime;

	lemmings = vector<Lemming>(levelAttributes->numLemmings, Lemming());
	alive = vector<bool>(levelAttributes->numLemmings, false);
	
	levelLemmings = levelAttributes->numLemmings;
	totalTime = levelAttributes->time;
	lemmingsToBeSaved = levelAttributes->goalLemmings;
	lemmingsDied = 0;
	lemmingsInLevel = 0;
	lemmingsSaved = 0;
}

void LevelManager::updateLemmings(int deltaTime)
{
	for (int i = 0; i < levelLemmings; ++i) {
		alive[i] = lemmings[i].isAlive();
		if (alive[i]) {
			lemmings[i].update(deltaTime);
		}
	}
}

void LevelManager::changeLevel(int levelNum, int levelMode)
{
	int goalPercentage = (lemmingsToBeSaved / levelLemmings) * 100;
	int currentPercentage = (lemmingsSaved / levelLemmings) * 100;

	StateManager::instance().changeResults(goalPercentage, currentPercentage);
}

void LevelManager::lemmingSaved()
{
	++lemmingsSaved;
	--lemmingsInLevel;
}

void LevelManager::lemmingDied()
{
	--lemmingsInLevel;
	++lemmingsDied;
}

void LevelManager::lemmingAppear()
{
	++lemmingsInLevel;
}

