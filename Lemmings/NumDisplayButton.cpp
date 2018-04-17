#include "NumDisplayButton.h"
#include "ButtonNumFactory.h"

void NumDisplayButton::displayNumAux(int firstDigit, int secondDigit)
{
	leftNum = ButtonNumFactory::instance().createNum(firstDigit);
	rightNum = ButtonNumFactory::instance().createNum(secondDigit);

	leftNum->setPosition(this->position + glm::vec2(4, 1));
	rightNum->setPosition(this->position + glm::vec2(8, 1));
}

void NumDisplayButton::setPosition(glm::vec2 position) {
	this->position = position;

	if (leftNum != NULL) {
		leftNum->setPosition(this->position + glm::vec2(4, 1));
	}

	if (rightNum != NULL) {
		rightNum->setPosition(this->position + glm::vec2(8, 1));
	}
}

