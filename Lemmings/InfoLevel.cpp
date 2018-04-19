#include <iostream>
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "InfoLevel.h"

InfoLevel::InfoLevel()
{

}

InfoLevel::~InfoLevel()
{

}

void InfoLevel::init(int mode, int numlevel) {

	initShaders();
	initTextures(mode, numlevel);

	InfoLevelSprite = Sprite::createSprite(glm::vec2(320, 230), glm::vec2(1.f, 1.f), &simpleTexProgram, &InfoLevelTexture);
	
	currentTime = 0.0f;
	InfoLevelSprite->setPosition(glm::vec2(0, 0));
}

void InfoLevel::update(int deltaTime)
{
	currentTime += deltaTime;

}

void InfoLevel::render()
{
	glm::mat4 modelview;
	simpleTexProgram.use();
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	simpleTexProgram.setUniformMatrix4f("projection", projection);
	simpleTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	InfoLevelSprite->render();
}

void InfoLevel::initShaders() {
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
}

void InfoLevel::initTextures(int mode, int numlevel) {
	
	string levelType;
	if (mode == 0) levelType = "fun";
	if (mode == 1) levelType = "tricky";
	if (mode == 2) levelType = "taxing";

	string levelName = levelType + to_string(numlevel);

	InfoLevelTexture.loadFromFile("images/levels/" + levelName + "/info.png", TEXTURE_PIXEL_FORMAT_RGBA);
	InfoLevelTexture.setMinFilter(GL_NEAREST);
	InfoLevelTexture.setMagFilter(GL_NEAREST);

}