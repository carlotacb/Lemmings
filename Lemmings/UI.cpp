#include "UI.h"
#include "Scene.h"
#include "ButtonFactory.h"

void UI::init() {
	backgroundTexture.loadFromFile("images/UI/black_frame.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgroundTexture.setMinFilter(GL_NEAREST);
	backgroundTexture.setMagFilter(GL_NEAREST);

	background = Sprite::createSprite(glm::vec2(960, 25), glm::vec2(1., 1.), &Scene::shaderProgram(), &backgroundTexture);

	selectFrameTexture.loadFromFile("images/UI/white_frame.png", TEXTURE_PIXEL_FORMAT_RGBA);
	selectFrameTexture.setMinFilter(GL_NEAREST);
	selectFrameTexture.setMagFilter(GL_NEAREST);

	selectFrame = Sprite::createSprite(glm::vec2(17, 25), glm::vec2(1., 1.), &Scene::shaderProgram(), &selectFrameTexture);

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

void UI::setPosition(glm::vec2 position) {
	this->position = position;
	background->setPosition(position);

	for (int i = 0; i < NUM_BUTTONS; ++i) {
		buttons[i].setPosition(position + glm::vec2(15 * i, 0) + glm::vec2(i+1, 1));
	}
}

void UI::changeSelectedButton(int selectedButton) {
	this->selectedButton = selectedButton;

	selectFrame->setPosition(position + glm::vec2(16*selectedButton,0));
}