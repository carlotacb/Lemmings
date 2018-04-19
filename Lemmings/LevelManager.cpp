#include "LevelManager.h"
#include "Scene.h"
#include <GL/glew.h>
#include <GL/glut.h>

int LevelManager::getActualMode()
{
	return actualMode;
}

int LevelManager::getActualLevel()
{
	return actualLevel;
}

void LevelManager::infoLevel(int level, int mode)
{
	InfoLevel::instance().init(mode, level);
}

void LevelManager::initLevel(int level, int mode, int lemmingsToSave, int totalLemmings, int time)
{
	actualLevel = level;
	actualMode = mode;
	levelLemmings = totalLemmings;
	totalTime = time;
	lemmingsToBeSaved = lemmingsToSave;
	lemmingsDied = 0;
	lemmingsInLevel = 0;
	lemmingsSaved = 0;
}

void LevelManager::changeLevel(int levelNum, int levelMode)
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);

	if (currentTime >= totalTime) // pasa a la pantalla de perdida
	{

	}

	else if (lemmingsToBeSaved > lemmingsSaved) // pasa a la pantalla de perdida
	{

	}

	else // pantalla de victoria
	{

	}
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

