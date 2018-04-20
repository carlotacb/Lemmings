#include "LevelManager.h"
#include "StateManager.h"
#include "ParticleSystemManager.h"
#include "Utils.h"

void LevelManager::init(string levelMode, int levelNum)
{
	currentTime = 0.0f;

	string levelName = levelMode + "-" + to_string(levelNum);
	actualLevel = levelNum;
	if (levelMode == "fun") actualMode = FUN_MODE;
	if (levelMode == "tricky") actualMode = TRICKY_MODE;
	if (levelMode == "taxing") actualMode = TAXING_MODE;
	Level::currentLevel().createFromFile("levels/" + levelName + ".txt");
	Level::currentLevel().init();
	
	jobCount = Level::currentLevel().getLevelAttributes()->jobCount;
	
	lemmings.clear();
	lemmings = set<Lemming*>();

	goalLemmingNum = Level::currentLevel().getLevelAttributes()->goalLemmings;
	releaseRate = Level::currentLevel().getLevelAttributes()->releaseRate;
	minReleaseRate = Level::currentLevel().getLevelAttributes()->minReleaseRate;

	goalTime = Level::currentLevel().getLevelAttributes()->time;
	currentTime = 0.0f;
	lastTimeSpawnedLemming = -3500;

	availableLemmings = Level::currentLevel().getLevelAttributes()->numLemmings;
	spawningLemmings = true;
	
	door = Level::currentLevel().getLevelAttributes()->door;
	trapdoor = Level::currentLevel().getLevelAttributes()->trapdoor;

	deadLemmings = 0;
	savedLemmings = 0;

	finishedLevel = false;

	//FMOD::Channel* channel = soundManager->playSound(dooropen);
	//channel->setVolume(0.5f);

	//channel = soundManager->playSound(music);
	//channel->setVolume(0.3f);
}

void LevelManager::update(int deltaTime)
{
	currentTime += deltaTime;

	if (currentTime / 1000 >= goalTime) {
		finishLevel();
	}

	if (!trapdoor->isOpened()) {
		trapdoor->update(deltaTime);
		if (trapdoor->isOpened()) {
			currentTime = 0;
		}
		return;
	}

	if (spawningLemmings) {
		spawnLemmings();
	}
	updateLemmings(deltaTime);

	door->update(deltaTime);
	trapdoor->update(deltaTime);

	if (savedLemmings + deadLemmings == Level::currentLevel().getLevelAttributes()->numLemmings) {
		finishLevel();
	}
}

void LevelManager::render()
{
	Level::currentLevel().getLevelAttributes()->trapdoor->render();
	Level::currentLevel().getLevelAttributes()->door->render();
	renderLemmings();
}

bool LevelManager::finished()
{
	return finishedLevel;
}

void LevelManager::spawnLemmings()
{
	int elapsedTimeSinceLastLemming = currentTime - lastTimeSpawnedLemming;
	int timeToNextLemming = 3500 * (100 - releaseRate) / 50;

	if (elapsedTimeSinceLastLemming >= timeToNextLemming) {
		--availableLemmings;
		lastTimeSpawnedLemming = currentTime;
		Lemming *newLemming = new Lemming(Level::currentLevel().getLevelAttributes()->trapdoor->getEnterPosition());
		newLemming->setWalkingRight(true);
		lemmings.insert(newLemming);
	}

	spawningLemmings = availableLemmings != 0;
}

int LevelManager::getNumLemmingsAlive()
{
	return lemmings.size();
}

int LevelManager::getPercentageSavedLemmings()
{
	return float(savedLemmings) / Level::currentLevel().getLevelAttributes()->numLemmings * 100;
}

int LevelManager::getPercentageTotalLemmings()
{
	return goalLemmingNum;
}

void LevelManager::stopSpawningLemmings()
{
	spawningLemmings = false;
}

int LevelManager::getCurrentTime()
{
	return currentTime/1000;
}

int LevelManager::getRemainingTime()
{
	return goalTime - getCurrentTime();
}


int LevelManager::getActualLevel()
{
	return actualLevel;
}

int LevelManager::getActualMode()
{
	return actualMode;
}

void LevelManager::apocalypsis()
{
	spawningLemmings = false;
	deadLemmings += availableLemmings;

	std::set<Lemming*>::iterator it;
	for (it = lemmings.begin(); it != lemmings.end(); ++it)
	{
		Lemming* currentLemming = *it; 
		currentLemming->writeDestiny();
	}
}


int LevelManager::getReleaseRate() {
	return releaseRate;
}

int LevelManager::getMinReleaseRate() {
	return minReleaseRate;
}


void LevelManager::decreaseReleaseRate()
{
	releaseRate = Utils::max(minReleaseRate, releaseRate - 5);
}

void LevelManager::increaseReleaseRate()
{
	releaseRate = Utils::min(99, releaseRate + 5);
}

int LevelManager::getLemmingIndexInPos(int posX, int posY) 
{
	int i = -1;
	std::set<Lemming*>::iterator it;
	for (it = lemmings.begin(); it != lemmings.end(); ++it)
	{
		++i;
		Lemming* currentLemming = *it;
		glm::vec2 lemmingPosition = currentLemming->getPosition();
		glm::vec2 lemmingSize = glm::vec2(16);
		if (Utils::insideRectangle(glm::vec2(posX, posY) + Level::currentLevel().getLevelAttributes()->cameraPos, lemmingPosition, lemmingSize)) {
			return i;
		}
	}

	return -1;
}

string LevelManager::getLemmingJobNameIndex(int index)
{
	std::set<Lemming*>::iterator it = lemmings.begin();
	std::advance(it, index);
	Lemming* currentLemming = *it;
	return currentLemming->getJob()->getName();
}

bool LevelManager::assignJob(int lemmingIndex, Job *jobToAssign)
{
	std::set<Lemming*>::iterator it = lemmings.begin();
	std::advance(it, lemmingIndex);
	Lemming* currentLemming = *it;

	string lemmingActualJob = currentLemming->getJob()->getName();
	string jobToAssignName = jobToAssign->getName();
	if (jobToAssignName == lemmingActualJob) {
		return false;
	}
	else {
		if (lemmingActualJob == "FALLER" && jobToAssignName != "FLOATER") {
			return false;
		}
		if (jobToAssignName == "BOMBER") {
			currentLemming->writeDestiny();
		}
		else {
			currentLemming->changeJob(jobToAssign);
		}
		return true;
	}
}


void LevelManager::finishLevel()
{
	finishedLevel = true;
}

void LevelManager::updateLemmings(int deltaTime)
{
	std::set<Lemming*>::iterator it = lemmings.begin();
	while(it != lemmings.end())
	{
		std::set<Lemming*>::iterator current = it++;
		Lemming* currentLemming = *current;
		currentLemming->update(deltaTime);

		bool saved = currentLemming->saved();
		bool dead = currentLemming->dead();

		if (saved) {
			lemmings.erase(current);
			++savedLemmings;
		}
		else if (dead) {
			lemmings.erase(current);
			++deadLemmings;
		}
	}
}

void LevelManager::renderLemmings()
{
	std::set<Lemming*>::iterator it;
	for (it = lemmings.begin(); it != lemmings.end(); ++it)
	{
		Lemming* currentLemming = *it;
		currentLemming->render();
	}
}


int LevelManager::getJobCount(int index)
{
	return jobCount[index];
}

void LevelManager::decreaseJobCount(int index)
{
	--jobCount[index];
}