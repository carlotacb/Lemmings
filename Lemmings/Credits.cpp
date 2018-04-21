#include "Credits.h"
#include "ShaderManager.h"
#include "CreditsMouseManager.h"
#include "CreditsKeyboardManager.h"
#include "Game.h"


void Credits::init()
{
	currentTime = 0.0f;
	initTextures();
	creditsLevelSprite = Sprite::createSprite(glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1.f, 1.f), &ShaderManager::getInstance().getShaderProgram(), &creditsLevelTexture);

	mouseManager = &CreditsMouseManager::getInstance();
	keyboardManager = &CreditsKeyboardManager::getInstance();

	soundManager = Game::instance().getSoundManager();
	music = soundManager->loadSound("sounds/CreditsSong.ogg", FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);

	channel = soundManager->playSound(music);
	channel->setVolume(1.f);
}

void Credits::update(int deltaTime)
{
	currentTime += deltaTime;

}

void Credits::render()
{
	ShaderManager::getInstance().useShaderProgram();
	creditsLevelSprite->render();
}

void Credits::initTextures() 
{
	creditsLevelTexture.loadFromFile("images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	creditsLevelTexture.setMinFilter(GL_NEAREST);
	creditsLevelTexture.setMagFilter(GL_NEAREST);

}

void Credits::endMusic() {
	channel->stop();
}