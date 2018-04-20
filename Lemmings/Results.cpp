#include "Results.h"
#include "ResultsMouseManager.h"
#include "ResultsKeyboardManager.h"
#include "Texture.h"
#include "Game.h"
#include "ShaderManager.h"

void Results::init()
{
	mouseManager = &ResultsMouseManager::getInstance();
	keyboardManager = &ResultsKeyboardManager::getInstance();
	currentTime = 0.0f;
}

void Results::update(int deltaTime)
{
	currentTime += deltaTime;
}

void Results::render()
{

	ShaderManager::getInstance().useShaderProgram();

	background->render();

	currentPercentageDisplay.render();
	goalPercentageDisplay.render();

	renderButtons();
}

int Results::getSelectedButtonIndex()
{
	return selectedButton;
}

int Results::getSelectedButton()
{
	return possibleButtons[selectedButton];
}

void Results::changeSelectedButtonLeft()
{
	--selectedButton;
	if (selectedButton < 0) {
		selectedButton = possibleButtons.size() - 1;
	}
}

void Results::changeSelectedButtonRight()
{
	++selectedButton;

	if (selectedButton == possibleButtons.size()) {
		selectedButton = 0;
	}
}

void Results::setPercentages(int goalPercentage, int currentPercentage)
{
	passedLevel = currentPercentage >= goalPercentage;
	string texturePath = "";
	if (passedLevel) {
		possibleButtons = vector<ResultsButtonName>(3);
		possibleButtons[0] = RETRY;
		possibleButtons[1] = CONTINUE;
		possibleButtons[2] = MENU;
		selectedButton = 1;


		if (currentPercentage == 100) {
			texturePath = "images/results/perfect.png";
		}
		else if (goalPercentage == currentPercentage) {
			texturePath = "images/results/justInTick.png";
		}
		else if (currentPercentage < 100) {
			texturePath = "images/results/good.png";
		}
	}
	else {
		possibleButtons = vector<ResultsButtonName>(2);
		possibleButtons[0] = RETRY;
		possibleButtons[1] = MENU;
		selectedButton = 0;

		if (currentPercentage == 0) {
			texturePath = "images/results/disaster.png";
		}
		else if (currentPercentage < goalPercentage) {
			texturePath = "images/results/practice.png";
		}
	}

	backgroundTexture.loadFromFile(texturePath, TEXTURE_PIXEL_FORMAT_RGBA);
	backgroundTexture.setMinFilter(GL_NEAREST);
	backgroundTexture.setMagFilter(GL_NEAREST);

	background = Sprite::createSprite(glm::ivec2(CAMERA_WIDTH, CAMERA_HEIGHT), glm::vec2(1, 1), &ShaderManager::getInstance().getShaderProgram(), &backgroundTexture);
	background->setPosition(glm::vec2(0, 0));

	goalPercentageDisplay.init();
	goalPercentageDisplay.displayPercentage(goalPercentage);
	goalPercentageDisplay.setPosition(glm::vec2(200, 49));

	currentPercentageDisplay.init();
	currentPercentageDisplay.displayPercentage(currentPercentage);
	currentPercentageDisplay.setPosition(glm::vec2(200, 61));
	initButtons();

}

void Results::initButtons()
{
	continueButton = Sprite::createSprite(glm::ivec2(77, 12), glm::vec2(144. / 256, 25. / 256), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().resultsWordSprites);
	continueButton->setNumberAnimations(2);
	continueButton->addKeyframe(0, glm::vec2(0,0));
	continueButton->addKeyframe(1, glm::vec2(0, 25. / 256));
	continueButton->changeAnimation(0);

	menuButton = Sprite::createSprite(glm::ivec2(77, 12), glm::vec2(144. / 256, 25. / 256), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().resultsWordSprites);
	menuButton->setNumberAnimations(2);
	menuButton->addKeyframe(0, glm::vec2(0, 50. / 256));
	menuButton->addKeyframe(1, glm::vec2(0, 75. / 256));
	menuButton->changeAnimation(0);

	retryButton = Sprite::createSprite(glm::ivec2(77, 12), glm::vec2(144. / 256, 25. / 256), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().resultsWordSprites);
	retryButton->setNumberAnimations(2);
	retryButton->addKeyframe(0, glm::vec2(0,100. / 256));
	retryButton->addKeyframe(1, glm::vec2(0,125. / 256));
	retryButton->changeAnimation(0);

	if (passedLevel) {
		retryButton->setPosition(glm::vec2(65, 150));
		continueButton->setPosition(glm::vec2(125, 150));
		menuButton->setPosition(glm::vec2(215, 150));
	}

	else {
		retryButton->setPosition(glm::vec2(100, 150));
		menuButton->setPosition(glm::vec2(200, 150));
	}
}

void Results::renderButtons()
{
	for (int i = 0; i < possibleButtons.size(); ++i) {
		Sprite *currentButton;
		ResultsButtonName buttonName = possibleButtons[i];
		
		switch (buttonName)
		{
			case RETRY:
				currentButton = retryButton;
				break;
			case CONTINUE:
				currentButton = continueButton;
				break;
			case MENU:
				currentButton = menuButton;
				break;
			default:
				break;
		}

		if (i == selectedButton) {
			currentButton->changeAnimation(1);
		}
		else {
			currentButton->changeAnimation(0);
		}
		currentButton->render();
	}
}