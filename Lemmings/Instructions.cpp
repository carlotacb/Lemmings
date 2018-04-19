#include "Instructions.h"
#include "ShaderManager.h"
#include "InstructionsMouseManager.h"
#include "InstructionsKeyboardManager.h"
#include "KeyFactory.h"


void Instructions::init()
{
	currentTime = 0.0f;
	initTextures();
	initSprites();
	mouseManager = &InstructionsMouseManager::getInstance();
	keyboardManager = &InstructionsKeyboardManager::getInstance();
}

void Instructions::update(int deltaTime)
{
	currentTime += deltaTime;

}

void Instructions::render()
{
	ShaderManager::getInstance().useShaderProgram();
	instructionsLevelSprite->render();
	leftKey->render();
	rightKey->render();
	escapeKey->render();
}

void Instructions::initTextures()
{
	instructionsLevelTexture.loadFromFile("images/menu/menuBackground.png", TEXTURE_PIXEL_FORMAT_RGBA);
	instructionsLevelTexture.setMinFilter(GL_NEAREST);
	instructionsLevelTexture.setMagFilter(GL_NEAREST);

}

void Instructions::initSprites()
{
	leftKey = KeyFactory::instance().createLeftKey();
	leftKey->position() = glm::vec2(200, 150);

	rightKey = KeyFactory::instance().createRightKey();
	rightKey->position() = glm::vec2(230, 150);

	escapeKey = KeyFactory::instance().createEscapeKey();
	escapeKey->position() = glm::vec2(30, 150);

	instructionsLevelSprite = Sprite::createSprite(glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1.f, 1.f), &ShaderManager::getInstance().getShaderProgram(), &instructionsLevelTexture);
}