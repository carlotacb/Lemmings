#include "UI.h"
#include "Scene.h"
#include "ButtonFactory.h"
#include "JobFactory.h"

void UI::init() {
	backgroundTexture.loadFromFile("images/UI/black_frame.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgroundTexture.setMinFilter(GL_NEAREST);
	backgroundTexture.setMagFilter(GL_NEAREST);

	background = Sprite::createSprite(glm::vec2(UI_WIDTH, UI_HEIGHT), glm::vec2(1., 1.), &Scene::shaderProgram(), &backgroundTexture);

	
	
	selectFrameTexture.loadFromFile("images/UI/white_frame.png", TEXTURE_PIXEL_FORMAT_RGBA);
	selectFrameTexture.setMinFilter(GL_NEAREST);
	selectFrameTexture.setMagFilter(GL_NEAREST);

	selectFrame = Sprite::createSprite(glm::vec2(17, 25), glm::vec2(17./32, 25./32), &Scene::shaderProgram(), &selectFrameTexture);

	for (int i = 0; i < NUM_BUTTONS; ++i) {
		buttons[i] = ButtonFactory::instance().createButton(i);
		buttons[i].setNum(i);
	}

	setPosition(glm::vec2(0, 0));
}

void UI::render() {
	background->render();

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
}

void UI::setPosition(glm::vec2 position) {
	this->position = position;
	background->setPosition(position);

	for (int i = 0; i < NUM_BUTTONS; ++i) {
		buttons[i].setPosition(position + glm::vec2(16 * i + 1, 26));
	}
}

int UI::getButtonIndexInPos(int posX, int posY)
{
	for (int i = 0; i < NUM_BUTTONS; ++i) {
		int leftPos = position.x + 16 * i + 1;
		int rightPos = position.x + 16 * i + 17;

		if (leftPos <= posX && posX < rightPos && posY >= position.y + 26) {
			return i;
		}
	}

	return -1;
}

void UI::changeSelectedButton(int selectedButton) 
{
	this->selectedButton = selectedButton;

	selectFrame->setPosition(position + glm::vec2(16*selectedButton,25));
}

int UI::getSelectedButtonJobCount()
{
	return Level::currentLevel().getLevelAttributes()->jobCount[selectedButton - 2];
}

void UI::decreaseSelectedButtonJobCount()
{
	--Level::currentLevel().getLevelAttributes()->jobCount[selectedButton - 2];
}

