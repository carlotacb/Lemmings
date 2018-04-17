#include "NumDisplayGreen.h"
#include "GreenNumFactory.h"

void NumDisplayGreen::displayNumAux(int firstDigit, int secondDigit)
{
	if (firstDigit != 0) {
		leftNum = GreenNumFactory::instance().createNum(firstDigit);
		leftNum->setPosition(this->position + glm::vec2(4, 0));
	}
	else {
		leftNum = NULL;
	}

	rightNum = GreenNumFactory::instance().createNum(secondDigit);
	rightNum->setPosition(this->position + glm::vec2(12, 0));
}

void NumDisplayGreen::setPosition(glm::vec2 position) {
	this->position = position;

	if (leftNum != NULL) {
		leftNum->setPosition(this->position + glm::vec2(4, 0));
	}

	if (rightNum != NULL) {
		rightNum->setPosition(this->position + glm::vec2(12, 0));
	}
}

