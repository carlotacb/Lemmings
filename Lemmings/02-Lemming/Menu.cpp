#include <iostream>
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "Menu.h"


Menu::Menu()
{
	
}

Menu::~Menu()
{
	
}


void Menu::init() {

	initShaders();
	initTextures();
	
	menuFondo = Sprite::createSprite(glm::vec2(1024, 768), glm::vec2(1.f, 1.f), &menuTexture, &simpleTexProgram);
	menuLogo = Sprite::createSprite(glm::vec2(250, 56), glm::vec2(1.f, 1.f), &menuLogoTexture, &simpleTexProgram);
	menuFun = Sprite::createSprite(glm::vec2(44, 48), glm::vec2(1.f, 1.f), &menuFunTexture, &simpleTexProgram);
	menuTricky = Sprite::createSprite(glm::vec2(44, 48), glm::vec2(1.f, 1.f), &menuTrickyTexture, &simpleTexProgram);
	menuTaxing = Sprite::createSprite(glm::vec2(44, 48), glm::vec2(1.f, 1.f), &menuTaxingTexture, &simpleTexProgram);
	menuMayhem = Sprite::createSprite(glm::vec2(44, 48), glm::vec2(1.f, 1.f), &menuMayhemTexture, &simpleTexProgram);
	menuAbout = Sprite::createSprite(glm::vec2(44, 48), glm::vec2(1.f, 1.f), &menuAboutTexture, &simpleTexProgram);

	currentTime = 0.0f;
	menuLogo->setPosition(glm::vec2(35,10));
	menuFun->setPosition(glm::vec2(30,85));
	menuTricky->setPosition(glm::vec2(84,85));
	menuTaxing->setPosition(glm::vec2(138,85));
	menuMayhem->setPosition(glm::vec2(192,85));
	menuAbout->setPosition(glm::vec2(246,85));
}


void Menu::update(int deltaTime)
{
	currentTime += deltaTime;

}

void Menu::render()
{
	glm::mat4 modelview;
	simpleTexProgram.use();
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	simpleTexProgram.setUniformMatrix4f("projection", projection);
	simpleTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	menuFondo->render();
	menuLogo->render();
	menuFun->render();
	menuTricky->render();
	menuTaxing->render();
	menuMayhem->render();
	menuAbout->render();
}

void Menu::initShaders() {
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

void Menu::initTextures() {

	menuTexture.loadFromFile("images/layout.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuTexture.setWrapS(GL_CLAMP_TO_EDGE);
	menuTexture.setWrapT(GL_CLAMP_TO_EDGE);
	menuTexture.use();

	menuLogoTexture.loadFromFile("images/logoTransp.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuLogoTexture.use();

	menuFunTexture.loadFromFile("images/menu-fun.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuFunTexture.use();

	menuTrickyTexture.loadFromFile("images/menu-tricky.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuTrickyTexture.use();

	menuTaxingTexture.loadFromFile("images/menu-taxing.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuTaxingTexture.use();
	
	menuMayhemTexture.loadFromFile("images/menu-mayhem.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuMayhemTexture.use();
	
	menuAboutTexture.loadFromFile("images/menu-about.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuAboutTexture.use();
		
}




