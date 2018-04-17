#include <iostream>
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "Scene.h"
#include "JobFactory.h"
#include "DoorFactory.h"
#include "TrapdoorFactory.h"

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
	initShaders();
	//initSounds();
	initCurrentLevel(levelFilePath);
	initMap();
	initUI();
}


void Scene::update(int deltaTime)
{
	if (paused) {
		return;
	}

	currentTime += deltaTime;
	if (!Level::currentLevel().getLevelAttributes()->trapdoor->isOpened()) {
		Level::currentLevel().getLevelAttributes()->trapdoor->update(deltaTime);
		if (Level::currentLevel().getLevelAttributes()->trapdoor->isOpened()) {
			currentTime = 0;
		}
	}

	else {
		spawnLemmings();
		updateLemmings(deltaTime);
		updateCurrentLevel(deltaTime);
		updateUI();
	}
}

void Scene::render()
{
	glm::mat4 modelview;

	maskedTexProgram.use();
	maskedTexProgram.setUniformMatrix4f("projection", projection);
	maskedTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	maskedTexProgram.setUniformMatrix4f("modelview", modelview);
	map->render(maskedTexProgram, Level::currentLevel().getLevelAttributes()->levelTexture, Level::currentLevel().getLevelAttributes()->maskedMap);
	
	Scene::shaderProgram().use();
	Scene::shaderProgram().setUniformMatrix4f("projection", projection);
	Scene::shaderProgram().setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	Scene::shaderProgram().setUniformMatrix4f("modelview", modelview);

	Level::currentLevel().getLevelAttributes()->trapdoor->render();
	Level::currentLevel().getLevelAttributes()->door->render();

	for (int i = 0; i < Level::currentLevel().getLevelAttributes()->numLemmings; ++i) {
		if (alive[i]) {
			lemmings[i].render();
		}
	}

	UI::getInstance().render();

}

VariableTexture& Scene::getMaskedMap() 
{
	return Level::currentLevel().getLevelAttributes()->maskedMap;
}

void Scene::changePauseStatus()
{
	paused = !paused;
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	Scene::shaderProgram().init();
	Scene::shaderProgram().addShader(vShader);
	Scene::shaderProgram().addShader(fShader);
	Scene::shaderProgram().link();
	if (!Scene::shaderProgram().isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << Scene::shaderProgram().log() << endl << endl;
	}
	Scene::shaderProgram().bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();

	vShader.initFromFile(VERTEX_SHADER, "shaders/maskedTexture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/maskedTexture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	maskedTexProgram.init();
	maskedTexProgram.addShader(vShader);
	maskedTexProgram.addShader(fShader);
	maskedTexProgram.link();
	if (!maskedTexProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << maskedTexProgram.log() << endl << endl;
	}
	maskedTexProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
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
	map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords, maskedTexProgram);

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
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
			Job *walkerJob = JobFactory::instance().createWalkerJob();
			lemmings[currentAlive-1].init(walkerJob, Level::currentLevel().getLevelAttributes()->trapdoor->getEnterPosition());
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
