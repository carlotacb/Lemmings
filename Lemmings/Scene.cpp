#include <iostream>
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "Scene.h"
#include "JobFactory.h"
#include "DoorFactory.h"

Scene::Scene()
{
	map = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
}


void Scene::init()
{
	glm::vec2 geom[2] = {glm::vec2(0.f, 0.f), glm::vec2(float(CAMERA_WIDTH), float(CAMERA_HEIGHT))};
	glm::vec2 texCoords[2] = {glm::vec2(120.f / 512.0, 0.f), glm::vec2((120.f + 320.f) / 512.0f, 160.f / 256.0f)};

	initShaders();

	map = MaskedTexturedQuad::createTexturedQuad(geom, texCoords, maskedTexProgram);
	colorTexture.loadFromFile("images/fun1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	colorTexture.setMinFilter(GL_NEAREST);
	colorTexture.setMagFilter(GL_NEAREST);
	
	Scene::maskedMap().loadFromFile("images/fun1_mask.png", TEXTURE_PIXEL_FORMAT_L);
	Scene::maskedMap().setMinFilter(GL_NEAREST);
	Scene::maskedMap().setMagFilter(GL_NEAREST);

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	for (int i = 0; i < NUMLEMMINGS; ++i) {
		Job *diggerJob = JobFactory::instance().createDiggerJob();
		lemmings[i].init(diggerJob, glm::vec2(60, 30), simpleTexProgram);

		alive[i] = false;
	}
	actualAlive = 0;
	alive[actualAlive] = true;

	initDoors(glm::vec2(217, 100));
	
}

void Scene::initDoors(const glm::vec2 &initialPosition) {
	//Pos porta final: glm::vec2(230, 113)
	//Pos porta inicial: glm::vec2(60, 30)
		
	door = DoorFactory::instance().createFunDoor(simpleTexProgram);
	door->setPosition(initialPosition);
}


void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	
	if (((int)currentTime / 1000) > actualAlive) {
		++actualAlive;
		if (actualAlive < NUMLEMMINGS) {
			alive[actualAlive] = true;
		}	
	}

	for (int i = 0; i < NUMLEMMINGS; ++i) {
		if (alive[i]) {
			lemmings[i].update(deltaTime);
		}
	}

	door->update(deltaTime);
}

void Scene::render()
{
	glm::mat4 modelview;

	maskedTexProgram.use();
	maskedTexProgram.setUniformMatrix4f("projection", projection);
	maskedTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	maskedTexProgram.setUniformMatrix4f("modelview", modelview);
	map->render(maskedTexProgram, colorTexture, Scene::maskedMap());
	
	simpleTexProgram.use();
	simpleTexProgram.setUniformMatrix4f("projection", projection);
	simpleTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	simpleTexProgram.setUniformMatrix4f("modelview", modelview);

	door->render();

	for (int i = 0; i < NUMLEMMINGS; ++i) {
		if (alive[i]) {
			lemmings[i].render();
		}
	}


}

void Scene::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton)
{
	if(bLeftButton)
		eraseMaskInMouse(mouseX, mouseY);
	else if(bRightButton)
		applyMaskInMouse(mouseX, mouseY);
}

void Scene::eraseMaskInMouse(int mouseX, int mouseY)
{
	int posX, posY;

	// Transform from mouse coordinates to map coordinates
	//   The map is enlarged 3 times and displaced 120 pixels
	posX = mouseX / 3 + 120;
	posY = mouseY / 3;

	for (int y = max(0, posY - 3); y <= min(Scene::maskedMap().height() - 1, posY + 3); y++)
		for (int x = max(0, posX - 3); x <= min(Scene::maskedMap().width() - 1, posX + 3); x++)
			eraseMask(x, y);
}

void Scene::applyMaskInMouse(int mouseX, int mouseY)
{
	int posX, posY;

	// Transform from mouse coordinates to map coordinates
	//   The map is enlarged 3 times and displaced 120 pixels
	posX = mouseX / 3 + 120;
	posY = mouseY / 3;

	for (int y = max(0, posY - 3); y <= min(Scene::maskedMap().height() - 1, posY + 3); y++)
		for (int x = max(0, posX - 3); x <= min(Scene::maskedMap().width() - 1, posX + 3); x++)
			applyMask(x, y);
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
	simpleTexProgram.init();
	simpleTexProgram.addShader(vShader);
	simpleTexProgram.addShader(fShader);
	simpleTexProgram.link();
	if (!simpleTexProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleTexProgram.log() << endl << endl;
	}
	simpleTexProgram.bindFragmentOutput("outColor");
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

void Scene::eraseMask(int x, int y) {
	Scene::maskedMap().setPixel(x, y, 0);
}

void Scene::applyMask(int x, int y) {
	Scene::maskedMap().setPixel(x, y, 255);
}