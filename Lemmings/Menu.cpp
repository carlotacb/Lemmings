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

	menuBackground = Sprite::createSprite(glm::vec2(320, 230), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuTexture);
	menuLogo = Sprite::createSprite(glm::vec2(250, 56), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuLogoTexture);
	menuAbout = Sprite::createSprite(glm::vec2(151, 42), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuAboutTexture);
	menuHelp = Sprite::createSprite(glm::vec2(44, 48), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuHelpTexture);
	menuExit = Sprite::createSprite(glm::vec2(44, 48), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuExitTexture);
	menuMode = Sprite::createSprite(glm::vec2(44, 48), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuModeTexture);
	menuPlaying = Sprite::createSprite(glm::vec2(111, 52), glm::vec2(1.f, 1.f), &simpleTexProgram, &menuPlayingTexture);
	
	currentTime = 0.0f;
	menuBackground->setPosition(glm::vec2(0, 0));
	menuLogo->setPosition(glm::vec2(35,10));
	menuPlaying->setPosition(glm::vec2(35,85));
	menuAbout->setPosition(glm::vec2(246,85));
	menuHelp->setPosition(glm::vec2(300,85));
	menuExit->setPosition(glm::vec2(300,100));
	menuMode->setPosition(glm::vec2(900,85));
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
	menuAbout->render();
	menuHelp->render();
	menuMode->render();
	menuExit->render();
	menuPlaying->render();
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

	menuTexture.loadFromFile("images/menu/menuBackground.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuTexture.setMinFilter(GL_NEAREST);
	menuTexture.setMagFilter(GL_NEAREST);

	menuLogoTexture.loadFromFile("images/menu/logo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuLogoTexture.setMinFilter(GL_NEAREST);
	menuLogoTexture.setMagFilter(GL_NEAREST);

	menuAboutTexture.loadFromFile("images/menu/aboutSprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuAboutTexture.setMinFilter(GL_NEAREST);
	menuAboutTexture.setMagFilter(GL_NEAREST);

	menuHelpTexture.loadFromFile("images/menu/helpSprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuHelpTexture.setMinFilter(GL_NEAREST);
	menuHelpTexture.setMagFilter(GL_NEAREST);

	menuExitTexture.loadFromFile("images/menu/exitSprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuExitTexture.setMinFilter(GL_NEAREST);
	menuExitTexture.setMagFilter(GL_NEAREST);

	menuModeTexture.loadFromFile("images/menu/modeSpriteSheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuModeTexture.setMinFilter(GL_NEAREST);
	menuModeTexture.setMagFilter(GL_NEAREST);

	menuPlayingTexture.loadFromFile("images/menu/player1Sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuPlayingTexture.setMinFilter(GL_NEAREST);
	menuPlayingTexture.setMagFilter(GL_NEAREST);
}




