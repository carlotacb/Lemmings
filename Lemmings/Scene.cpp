#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "Game.h"
#include "Scene.h"
#include "ShaderManager.h"
#include "Scroller.h"
#include "SceneMouseManager.h"
#include "SceneKeyboardManager.h"
#include "Cursor.h"
#include "ParticleSystemManager.h"
#include "StateManager.h"
#include "Utils.h"
#include "HardMaskManager.h"
#include "EasyMaskManager.h"
#include "LevelManager.h"

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
	Cursor::getInstance().init();

	ParticleSystemManager::getInstance().init();

	if (Game::instance().isHardMode()) {
		setMaskManager(&HardMaskManager::getInstance());
	}
	else {
		setMaskManager(&EasyMaskManager::getInstance());
	}

	initSounds();
	initMap();
	initUI();

	paused = false;
	speedUp = false;

	
}

void Scene::update(int deltaTime)
{
	((SceneMouseManager*)mouseManager)->update();
	maskManager->update();

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

	LevelManager::getInstance().update(deltaTime);
	ParticleSystemManager::getInstance().update(deltaTime);
	updateUI();

	if (LevelManager::getInstance().finished()) {
		int goalPercentage = LevelManager::getInstance().getPercentageSavedLemmings();
		int currentPercentage = LevelManager::getInstance().getPercentageTotalLemmings();

		StateManager::instance().changeResults(goalPercentage, currentPercentage);
	}

}

void Scene::render()
{
	ShaderManager::getInstance().useMaskedShaderProgram();
	map->render(ShaderManager::getInstance().getMaskedShaderProgram(), Level::currentLevel().getLevelAttributes()->levelTexture, Level::currentLevel().getLevelAttributes()->maskedMap);


	ShaderManager::getInstance().useShaderProgram();
	LevelManager::getInstance().render();
	ParticleSystemManager::getInstance().render();
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

void Scene::initUI()
{
	UI::getInstance().init();
	UI::getInstance().setPosition(glm::vec2(0, LEVEL_HEIGHT - 1));
}

void Scene::updateUI()
{
	UI::getInstance().update();
}


void Scene::setMaskManager(MaskManager* maskM)
{
	maskManager = maskM;

	maskManager->init();
}

void Scene::eraseMask(int x, int y) {
	maskManager->eraseMask(x, y);
}

void Scene::eraseSpecialMask(int x, int y) {
	maskManager->eraseSpecialMask(x, y);

}

char Scene::getPixel(int x, int y) {
	return maskManager->getPixel(x, y);
}

void Scene::applyMask(int x, int y) {
	maskManager->applyMask(x, y);
}

void Scene::applySpecialMask(int x, int y) {
	maskManager->applySpecialMask(x, y);
}

void Scene::buildStep(glm::vec2 position)
{
	for (int i = 0; i < 4; ++i) {
		Utils::changeTexelColor(Level::currentLevel().getLevelAttributes()->levelTexture.getId(), position.x + i, position.y, 120, 77, 0, 255);
		applyMask(position.x + i, position.y);
	}
}

