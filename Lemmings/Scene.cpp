#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "Game.h"
#include "Scene.h"
#include "ShaderManager.h"
#include "Scroller.h"
#include "JobFactory.h"
#include "DoorFactory.h"
#include "TrapdoorFactory.h"
#include "SceneMouseManager.h"
#include "SceneKeyboardManager.h"
#include "Cursor.h"
#include "ParticleSystemManager.h"
#include "StateManager.h"
#include "Utils.h"

Scene::Scene()
{
	map = NULL;
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
}

void Scene::init()
{	
	keyboardManager = &SceneKeyboardManager::getInstance();
	mouseManager = &SceneMouseManager::getInstance();
	initSounds();
	Cursor::getInstance().init();
	initMap();
	initUI();
	doomed = false;
}

void Scene::update(int deltaTime)
{
	((SceneMouseManager*)mouseManager)->update();

	if (Scroller::getInstance().isScrolled()) {
		delete map;
		initMap();
		Scroller::getInstance().iScroll();
	}


	if (paused) {
		return;
	}

	if (speedUp) {
		deltaTime = 4 * deltaTime;
	}

	currentTime += deltaTime;

	ParticleSystemManager::getInstance().update(deltaTime);

	updateUI();

	if (!Level::currentLevel().getLevelAttributes()->trapdoor->isOpened()) {
		Level::currentLevel().getLevelAttributes()->trapdoor->update(deltaTime);
		if (Level::currentLevel().getLevelAttributes()->trapdoor->isOpened()) {
			currentTime = 0;
		}
		return;
	}

	if (!doomed) {
		spawnLemmings();
	}
	updateLemmings(deltaTime);
	updateCurrentLevel(deltaTime);
}

void Scene::render()
{
	ShaderManager::getInstance().useMaskedShaderProgram();
	map->render(ShaderManager::getInstance().getMaskedShaderProgram(), Level::currentLevel().getLevelAttributes()->levelTexture, Level::currentLevel().getLevelAttributes()->maskedMap);


	ShaderManager::getInstance().useShaderProgram();
	Level::currentLevel().getLevelAttributes()->trapdoor->render();
	Level::currentLevel().getLevelAttributes()->door->render();

	for (int i = 0; i < Level::currentLevel().getLevelAttributes()->numLemmings; ++i) {
		if (alive[i]) {
			lemmings[i].render();
		}
	}
	ParticleSystemManager::getInstance().render();

	UI::getInstance().render();

	Cursor::getInstance().render();
}

void Scene::startLevel(string levelMode, int levelNum)
{
	string levelName = levelMode + "-" + to_string(levelNum);
	actualLevel = levelNum;
	if (levelMode == "fun") actualMode = FUN_MODE;
	if (levelMode == "tricky") actualMode = TRICKY_MODE;
	if (levelMode == "taxing") actualMode = TAXING_MODE;

	Level::currentLevel().createFromFile("levels/" + levelName + ".txt");
	Level::currentLevel().init();
	currentTime = 0.0f;

	lemmings = vector<Lemming>(Level::currentLevel().getLevelAttributes()->numLemmings, Lemming());
	alive = vector<bool>(Level::currentLevel().getLevelAttributes()->numLemmings, false);

	lemmingsSaved = 0;
	lemmingsDied = 0;

	paused = false;
	speedUp = false;

	//FMOD::Channel* channel = soundManager->playSound(dooropen);
	//channel->setVolume(0.5f);

	//channel = soundManager->playSound(music);
	//channel->setVolume(0.3f);
}

VariableTexture& Scene::getMaskedMap()
{
	return Level::currentLevel().getLevelAttributes()->maskedMap;
}

void Scene::changePauseStatus()
{
	paused = !paused;
}

void Scene::changeSpeedUpStatus()
{
	speedUp = !speedUp;
}

bool Scene::isPaused()
{
	return paused;
}

bool Scene::isSpeedUp()
{
	return speedUp;
}

void Scene::initSounds()
{
	soundManager = Game::instance().getSoundManager();
	music = soundManager->loadSound("sounds/Lemmings1.mp3", FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);
	dooropen = soundManager->loadSound("sounds/Lemmings_effects/Letsgo.ogg", FMOD_DEFAULT | FMOD_UNIQUE);
}

void Scene::initMap()
{
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(LEVEL_WIDTH), float(LEVEL_HEIGHT)) };

	int levelWidth = Level::currentLevel().getLevelAttributes()->levelTexture.width();
	int levelHeight = Level::currentLevel().getLevelAttributes()->levelTexture.height();
	glm::vec2 normalizedTexCoordStart = glm::vec2(
		Level::currentLevel().getLevelAttributes()->cameraPos.x / levelWidth,
		Level::currentLevel().getLevelAttributes()->cameraPos.y / levelHeight
	);
	glm::vec2 normalizedTexCoordEnd = glm::vec2(
		(Level::currentLevel().getLevelAttributes()->cameraPos.x + LEVEL_WIDTH) / levelWidth,
		(Level::currentLevel().getLevelAttributes()->cameraPos.y + LEVEL_HEIGHT) / levelHeight
	);

	glm::vec2 texCoords[2] = { normalizedTexCoordStart , normalizedTexCoordEnd };
	map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords, ShaderManager::getInstance().getMaskedShaderProgram());
}

void Scene::initUI()
{
	UI::getInstance().init();
	UI::getInstance().setPosition(glm::vec2(0, LEVEL_HEIGHT - 1));
}

void Scene::spawnLemmings()
{
	float delay = 3500 * (100 - Level::currentLevel().getLevelAttributes()->releaseRate) / 50;
	if (((int)currentTime / delay) > currentAlive) {
		if (currentAlive < Level::currentLevel().getLevelAttributes()->numLemmings) {
			++currentAlive;
			Job *fallerJob = JobFactory::instance().createFallerJob();
			lemmings[currentAlive - 1].init(fallerJob, Level::currentLevel().getLevelAttributes()->trapdoor->getEnterPosition());
			fallerJob->setWalkingRight(true);

		}
	}
}

void Scene::updateLemmings(int deltaTime)
{
	for (int i = 0; i < Level::currentLevel().getLevelAttributes()->numLemmings; ++i) {
		alive[i] = lemmings[i].isAlive();
		if (alive[i]) {
			lemmings[i].update(deltaTime);
		}
	}

	if (lemmingsSaved + lemmingsDied == Level::currentLevel().getLevelAttributes()->numLemmings)
	{
		int goalPercentage = (Level::currentLevel().getLevelAttributes()->goalLemmings / Level::currentLevel().getLevelAttributes()->numLemmings) * 100;
		int currentPercentage = (lemmingsSaved / Level::currentLevel().getLevelAttributes()->numLemmings) * 100;

		StateManager::instance().changeResults(goalPercentage, currentPercentage);
	}
}

void Scene::updateCurrentLevel(int deltaTime)
{
	Level::currentLevel().getLevelAttributes()->door->update(deltaTime);
	Level::currentLevel().getLevelAttributes()->trapdoor->update(deltaTime);
}

void Scene::updateUI()
{
	UI::getInstance().update();
}

int Scene::getNumLemmingAlive()
{
	return currentAlive;
}

int Scene::getLemmingIndexInPos(int posX, int posY) {

	for (int i = 0; i < Level::currentLevel().getLevelAttributes()->numLemmings; ++i) {
		if (alive[i]) {
			glm::vec2 lemmingPosition = lemmings[i].getPosition();
			glm::vec2 lemmingSize = glm::vec2(16);
			if (Utils::insideRectangle(glm::vec2(posX, posY) + Level::currentLevel().getLevelAttributes()->cameraPos, lemmingPosition, lemmingSize)) {
				return i;
			}
		}

	}

	return -1;
}

/*
*****************************************************
*/
//SEGURAMENTE HAYA QUE CAMBIAR ESTA FUNCION
Lemming Scene::getLemming(int index)
{
	return lemmings[index];
}

bool Scene::assignJob(int lemmingIndex, Job *jobToAssign)
{
	if (jobToAssign->getName() == lemmings[lemmingIndex].getJob()->getName()) {
		return false;
	}
	else {
		if (jobToAssign->getName() == "BOMBER") {
			lemmings[lemmingIndex].writeDestiny();
		}
		else {
			lemmings[lemmingIndex].changeJob(jobToAssign);
		}
		return true;
	}
}

void Scene::eraseMask(int x, int y) {
	if (getPixel(x,y) != 200) {
		Level::currentLevel().getLevelAttributes()->maskedMap.setPixel(x, y, 0);
	}
}

void Scene::eraseSpecialMask(int x, int y) {
	Level::currentLevel().getLevelAttributes()->maskedMap.setPixel(x, y, 0);
}

char Scene::getPixel(int x, int y) {
	return Level::currentLevel().getLevelAttributes()->maskedMap.pixel(x, y);
}

void Scene::applyMask(int x, int y) {
	Level::currentLevel().getLevelAttributes()->maskedMap.setPixel(x, y, 255);
}

void Scene::applySpecialMask(int x, int y) {
	Level::currentLevel().getLevelAttributes()->maskedMap.setPixel(x, y, 200);
}

void Scene::buildStep(glm::vec2 position)
{
	for (int i = 0; i < 4; ++i) {
		Utils::changeTexelColor(Level::currentLevel().getLevelAttributes()->levelTexture.getId(), position.x + i, position.y, 120, 77, 0, 255);
		applyMask(position.x + i, position.y);
	}
}

void Scene::explodeAll()
{
	doomed = true;
	for (int i = 0; i < Level::currentLevel().getLevelAttributes()->numLemmings; ++i) {
		if (alive[i]) {
			lemmings[i].writeDestiny();
		}
	}

	int goalPercentage = (Level::currentLevel().getLevelAttributes()->goalLemmings / Level::currentLevel().getLevelAttributes()->numLemmings) * 100;
	int currentPercentage = (lemmingsSaved / Level::currentLevel().getLevelAttributes()->numLemmings) * 100;

	StateManager::instance().changeResults(goalPercentage, currentPercentage);

}

void Scene::lemmingSaved()
{
	++lemmingsSaved;
}

void Scene::lemmingDied()
{
	++lemmingsDied;
}

int Scene::getActualLevel()
{
	return actualLevel;
}

int Scene::getActualMode()
{
	return actualMode;
}