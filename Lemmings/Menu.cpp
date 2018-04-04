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

	menuBackground = Sprite::createSprite(glm::vec2(320, 185), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuTexture);
	menuLogo = Sprite::createSprite(glm::vec2(250, 56), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuLogoTexture);
	menuFun = Sprite::createSprite(glm::vec2(44, 48), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuFunTexture);
	menuTricky = Sprite::createSprite(glm::vec2(44, 48), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuTrickyTexture);
	menuTaxing = Sprite::createSprite(glm::vec2(44, 48), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuTaxingTexture);
	menuMayhem = Sprite::createSprite(glm::vec2(44, 48), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuMayhemTexture);
	menuAbout = Sprite::createSprite(glm::vec2(44, 48), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuAboutTexture);

	currentTime = 0.0f;
	menuBackground->setPosition(glm::vec2(0, 0));
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
	menuBackground->render();
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

	menuTexture.loadFromFile("images/menu/menu-background.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuLogoTexture.setMinFilter(GL_NEAREST);
	menuLogoTexture.setMagFilter(GL_NEAREST);

	menuLogoTexture.loadFromFile("images/menu/logoTransp.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuLogoTexture.setMinFilter(GL_NEAREST);
	menuLogoTexture.setMagFilter(GL_NEAREST);

	menuFunTexture.loadFromFile("images/menu/menu-fun.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuFunTexture.setMinFilter(GL_NEAREST);
	menuFunTexture.setMagFilter(GL_NEAREST);

	menuTrickyTexture.loadFromFile("images/menu/menu-tricky.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuTrickyTexture.setMinFilter(GL_NEAREST);
	menuTrickyTexture.setMagFilter(GL_NEAREST);

	menuTaxingTexture.loadFromFile("images/menu/menu-taxing.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuTaxingTexture.setMinFilter(GL_NEAREST);
	menuTaxingTexture.setMagFilter(GL_NEAREST);
	
	menuMayhemTexture.loadFromFile("images/menu/menu-mayhem.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuMayhemTexture.setMinFilter(GL_NEAREST);
	menuMayhemTexture.setMagFilter(GL_NEAREST);
	
	menuAboutTexture.loadFromFile("images/menu/menu-about.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuAboutTexture.setMinFilter(GL_NEAREST);
	menuAboutTexture.setMagFilter(GL_NEAREST);
		
}




