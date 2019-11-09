#include "Button.h"



void Button::init() {
	numDisplay.init();

	setPosition(glm::vec2(0, 0));
}

void Button::render() {
	numDisplay.render();
	buttonSprite->render();
}

void Button::setSprite(Sprite *sprite) {
	if (buttonSprite != NULL) {
		delete buttonSprite;
	}
	
	buttonSprite = sprite;
	buttonSprite->setPosition(position);
}

glm::vec2 Button::getPosition() {
	return position;
}

void Button::setPosition(glm::vec2 position) {
	this->position = position;
	
	numDisplay.setPosition(position);

	if (buttonSprite != NULL) {
		buttonSprite->setPosition(position);
	}
}

void Button::setNum(int num) {
	numDisplay.displayNum(num);
}