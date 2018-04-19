#include "UI.h"
#include "Scene.h"
#include "Level.h"
#include "ShaderManager.h"
#include "PredefinedWordFactory.h"
#include "ButtonFactory.h"
#include "UIAdapter.h"

void UI::init() {
	backgroundTexture.loadFromFile("images/UI/black_frame.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgroundTexture.setMinFilter(GL_NEAREST);
	backgroundTexture.setMagFilter(GL_NEAREST);

	background = Sprite::createSprite(glm::vec2(UI_WIDTH, UI_HEIGHT), glm::vec2(1., 1.), &ShaderManager::getInstance().getShaderProgram(), &backgroundTexture);

	jobName = PredefinedWordFactory::instance().createJobWord();

	outWord = PredefinedWordFactory::instance().createInfoWord("OUT");
	numberOutLemmings.init();

	inWord = PredefinedWordFactory::instance().createInfoWord("IN");
	numberInLemmings.init();

	timeWord = PredefinedWordFactory::instance().createInfoWord("TIME");
	time.init();

	selectFrameTexture.loadFromFile("images/UI/white_frame.png", TEXTURE_PIXEL_FORMAT_RGBA);
	selectFrameTexture.setMinFilter(GL_NEAREST);
	selectFrameTexture.setMagFilter(GL_NEAREST);

	selectFrame = Sprite::createSprite(glm::vec2(17, 25), glm::vec2(17./32, 25./32), &ShaderManager::getInstance().getShaderProgram(), &selectFrameTexture);

	for (int i = 0; i < NUM_BUTTONS; ++i) {
		buttons[i] = ButtonFactory::instance().createButton(i);
		buttons[i].setNum(i);
	}

	setPosition(glm::vec2(0, 0));
}

void UI::render() {
	background->render();

	if (jobName != NULL) {
		jobName->render();
	}

	outWord->render();
	numberOutLemmings.render();

	inWord->render();
	numberInLemmings.render();

	timeWord->render();
	time.render();

	for (int i = 0; i < NUM_BUTTONS; ++i) {
		buttons[i].render();
	}

	if (selectedButton != -1) {
		selectFrame->render();
	}
}

void UI::update() 
{
	int *jobCount = Level::currentLevel().getLevelAttributes()->jobCount;
	for (int i = 0; i < 8; ++i) {
		buttons[i + 2].setNum(jobCount[i]);
	}

	buttons[Button::ButtonNames::MINUS_BUTTON].setNum(Level::currentLevel().getLevelAttributes()->minReleaseRate);
	buttons[Button::ButtonNames::PLUS_BUTTON].setNum(Level::currentLevel().getLevelAttributes()->releaseRate);

	numberOutLemmings.displayNum(Scene::getInstance().getNumLemmingAlive());
	numberInLemmings.displayPercentage(35);
	time.displayTime(Level::currentLevel().getLevelAttributes()->time -  Scene::getInstance().currentTime/1000);
}

void UI::setPosition(glm::vec2 position) {
	this->position = position;
	background->setPosition(position);

	jobName->setPosition(position + glm::vec2(0, 1));
	
	outWord->setPosition(position + glm::vec2(113, 1));
	numberOutLemmings.setPosition(position + glm::vec2(140, 1));

	inWord->setPosition(position + glm::vec2(180, 1));
	numberInLemmings.setPosition(position + glm::vec2(200, 1));

	timeWord->setPosition(position + glm::vec2(247, 1));
	time.setPosition(position + glm::vec2(280, 1));

	for (int i = 0; i < NUM_BUTTONS; ++i) {
		buttons[i].setPosition(position + glm::vec2(16 * i + 1, 13));
	}
}

int UI::getButtonIndexInPos(int posX, int posY)
{
	for (int i = 0; i < NUM_BUTTONS; ++i) {
		int leftPos = position.x + 16 * i + 1;
		int rightPos = position.x + 16 * i + 17;

		if (leftPos <= posX && posX < rightPos && posY >= position.y + 13) {
			if (i != Button::PAUSE_BUTTON && Scene::getInstance().isPaused()) {
				return -1;
			}
			else {
				return i;
			}
		}
	}

	return -1;
}

void UI::changeSelectedButton(int selectedButton) 
{
	this->selectedButton = selectedButton;

	selectFrame->setPosition(position + glm::vec2(16*selectedButton,12));
}

int UI::getSelectedButtonJobCount()
{
	return Level::currentLevel().getLevelAttributes()->jobCount[selectedButton - 2];
}

void UI::decreaseSelectedButtonJobCount()
{
	--Level::currentLevel().getLevelAttributes()->jobCount[selectedButton - 2];
}

void UI::changeDisplayedJob(string lemmingJobName)
{
	UIAdapter::getInstance().changeJobName(jobName, lemmingJobName);
}
