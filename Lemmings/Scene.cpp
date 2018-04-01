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
	initMap();
	initCurrentLevel(levelFilePath);
	initUI();
}


void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	
	if (((int)currentTime / 1000) > currentAlive) {
		++currentAlive;
		if (currentAlive < currentLevel->getLevelAttributes()->numLemmings) {
			alive[currentAlive] = true;
		}	
	}

	for (int i = 0; i < currentLevel->getLevelAttributes()->numLemmings; ++i) {
		if (alive[i]) {
			lemmings[i].update(deltaTime);
		}
	}

	currentLevel->getLevelAttributes()->door->update(deltaTime);
	currentLevel->getLevelAttributes()->trapdoor->update(deltaTime);
	if (currentLevel->getLevelAttributes()->trapdoor->getAnimationCurrentFrame() == 9) {
		currentLevel->getLevelAttributes()->trapdoor->setAnimationSpeed(0, 0);
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
	map->render(maskedTexProgram, currentLevel->getLevelAttributes()->colorTexture, currentLevel->getLevelAttributes()->maskedMap);
	
	Scene::shaderProgram().use();
	Scene::shaderProgram().setUniformMatrix4f("projection", projection);
	Scene::shaderProgram().setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	Scene::shaderProgram().setUniformMatrix4f("modelview", modelview);

	currentLevel->getLevelAttributes()->trapdoor->render();
	currentLevel->getLevelAttributes()->door->render();

	for (int i = 0; i < currentLevel->getLevelAttributes()->numLemmings; ++i) {
		if (alive[i]) {
			lemmings[i].render();
		}
	}

	ui.render();

}

void Scene::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton)
{
	if (bLeftButton) {

	}
	else if (bRightButton) {

	}
}

VariableTexture& Scene::getMaskedMap() 
{
	return currentLevel->getLevelAttributes()->maskedMap;
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

void Scene::initMap() 
{
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(CAMERA_WIDTH), float(CAMERA_HEIGHT)) };
	glm::vec2 texCoords[2] = { glm::vec2(120.f / 512.0, 0.f), glm::vec2((120.f + 320.f) / 512.0f, 160.f / 256.0f) };

	map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords, maskedTexProgram);

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
}

void Scene::initCurrentLevel(string levelFilePath) 
{
	currentLevel = Level::createFromFile(levelFilePath);
	currentLevel->init();
	currentTime = 0.0f;

	lemmings = vector<Lemming>(currentLevel->getLevelAttributes()->numLemmings, Lemming());
	alive = vector<bool>(currentLevel->getLevelAttributes()->numLemmings, false);

	for (int i = 0; i < currentLevel->getLevelAttributes()->numLemmings; ++i) {
		Job *walkerJob = JobFactory::instance().createWalkerJob();
		lemmings[i].init(walkerJob, currentLevel->getLevelAttributes()->lemmingSpawnPos);

		alive[i] = false;
	}

	currentAlive = 0;
	alive[currentAlive] = true;

}

void Scene::initUI()
{
	ui.init();
	ui.setPosition(glm::vec2(0, 134));
}

void Scene::eraseMask(int x, int y) {
	currentLevel->getLevelAttributes()->maskedMap.setPixel(x, y, 0);
}

void Scene::applyMask(int x, int y) {
	currentLevel->getLevelAttributes()->maskedMap.setPixel(x, y, 255);
}