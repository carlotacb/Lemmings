#include <iostream>
#include <cmath>
#include <algorithm>
#include "Game.h"
#include "Scene.h"
#include "ShaderManager.h"
#include "Scroller.h"
#include "JobFactory.h"
#include "DoorFactory.h"
#include "TrapdoorFactory.h"
#include "MouseManager.h"
#include "Cursor.h"

Scene::Scene()
{
	map = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
}


void Scene::init(string levelFilePath)
{
	//initSounds();
	initCurrentLevel(levelFilePath);
	Cursor::getInstance().init();
	initMap();
	initUI();
}


void Scene::update(int deltaTime)
{
	MouseManager::getInstance().update();

	if (Scroller::getInstance().isScrolled()) {
		initMap();
		Scroller::getInstance().iScroll();
	}


	if (paused) {
		return;
	}

	if (speedUp) {
		deltaTime = 4*deltaTime;
	}

	currentTime += deltaTime;
	
	updateUI();

	if (!Level::currentLevel().getLevelAttributes()->trapdoor->isOpened()) {
		Level::currentLevel().getLevelAttributes()->trapdoor->update(deltaTime);
		if (Level::currentLevel().getLevelAttributes()->trapdoor->isOpened()) {
			currentTime = 0;
		}
		return;
	}

	

	spawnLemmings();
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

	UI::getInstance().render();

	Cursor::getInstance().render();


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

void Scene::initCurrentLevel(string levelFilePath) 
{
	Level::currentLevel() = Level();
	Level::currentLevel().createFromFile(levelFilePath);
	Level::currentLevel().init();
	currentTime = 0.0f;

	lemmings = vector<Lemming>(Level::currentLevel().getLevelAttributes()->numLemmings, Lemming());
	alive = vector<bool>(Level::currentLevel().getLevelAttributes()->numLemmings, false);

	//FMOD::Channel* channel = soundManager->playSound(dooropen);
	//channel->setVolume(0.5f);

	//channel = soundManager->playSound(music);
	//channel->setVolume(0.3f);
	
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
			lemmings[currentAlive-1].init(fallerJob, Level::currentLevel().getLevelAttributes()->trapdoor->getEnterPosition());
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
			if (insideRectangle(glm::vec2(posX, posY) + Level::currentLevel().getLevelAttributes()->cameraPos, lemmingPosition, lemmingSize)) {
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


void Scene::assignJob(int lemmingIndex, Job *jobToAssign)
{
	lemmings[lemmingIndex].changeJob(jobToAssign);

}

void Scene::eraseMask(int x, int y) {
	Level::currentLevel().getLevelAttributes()->maskedMap.setPixel(x, y, 0);
}

void Scene::applyMask(int x, int y) {
	Level::currentLevel().getLevelAttributes()->maskedMap.setPixel(x, y, 255);
}

bool Scene::insideRectangle(glm::vec2 point, glm::vec2 rectangleOrigin, glm::vec2 rectangleSize)
{
	return (
		rectangleOrigin.x <= point.x
		&& point.x < rectangleOrigin.x + rectangleSize.x
		&& rectangleOrigin.y <= point.y
		&& point.y < rectangleOrigin.y + rectangleSize.y
	);
}
