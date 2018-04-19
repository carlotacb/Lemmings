#include "InfoLevel.h"
#include "ShaderManager.h"

void InfoLevel::init() 
{

	currentTime = 0.0f;
}

void InfoLevel::setLevel(int numLevel, int levelMode)
{
	level = numLevel;
	mode = levelMode;

	initTextures();

	InfoLevelSprite = Sprite::createSprite(glm::vec2(320, 230), glm::vec2(1.f, 1.f), &ShaderManager::getInstance().getShaderProgram(), &InfoLevelTexture);
}

void InfoLevel::update(int deltaTime)
{
	currentTime += deltaTime;

}

void InfoLevel::render()
{
	
	InfoLevelSprite->render();
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