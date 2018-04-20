#include "InfoLevel.h"
#include "InfoLevelKeyboardManager.h"
#include "InfoLevelMouseManager.h"
#include "ShaderManager.h"
#include "KeyFactory.h"

void InfoLevel::init() 
{
	keyboardManager = &InfoLevelKeyboardManager::getInstance();
	mouseManager= &InfoLevelMouseManager::getInstance();
	currentTime = 0.0f;
}

void InfoLevel::setLevel(int numLevel, int levelMode)
{
	level = numLevel;
	mode = levelMode;

	initTextures();

	InfoLevelSprite = Sprite::createSprite(glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1.f, 1.f), &ShaderManager::getInstance().getShaderProgram(), &InfoLevelTexture);
	initSprites();
}

void InfoLevel::update(int deltaTime)
{
	currentTime += deltaTime;
}

void InfoLevel::render()
{
	ShaderManager::getInstance().useShaderProgram();

	InfoLevelSprite->render();
	menuWord->render();
	rightKey->render();
	playWord->render();
	leftKey->render();
}

void InfoLevel::initTextures() {
	
	string levelType;
	switch (mode) {
	case FUN_MODE:
		levelType = "fun";
		break;
	case TRICKY_MODE:
		levelType = "tricky";
		break;
	case TAXING_MODE:
		levelType = "taxing";
		break;
	}

	string levelName = levelType + to_string(level);

	InfoLevelTexture.loadFromFile("images/levels/" + levelName + "/info.png", TEXTURE_PIXEL_FORMAT_RGBA);
	InfoLevelTexture.setMinFilter(GL_NEAREST);
	InfoLevelTexture.setMagFilter(GL_NEAREST);

}

int InfoLevel::getMode()
{
	return mode;
}

int InfoLevel::getLevel()
{
	return level;
}

void InfoLevel::initSprites()
{
	leftKey = KeyFactory::instance().createLeftKey(glm::vec2(25, 15));
	leftKey->position() = glm::vec2(5, 173);
	
	menuWord = new Word("MENU");
	menuWord->setPosititon(glm::vec2(36, 173));

	rightKey = KeyFactory::instance().createRightKey(glm::vec2(25, 15));
	rightKey->position() = glm::vec2(280, 173);

	playWord = new Word("PLAY");
	playWord->setPosititon(glm::vec2(240, 173));


	
}