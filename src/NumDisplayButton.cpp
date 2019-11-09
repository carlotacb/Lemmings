#include "NumDisplayButton.h"
#include "ButtonNumFactory.h"

void NumDisplayButton::initAux()
{
	leftNum = ButtonNumFactory::instance().createNum();
	rightNum = ButtonNumFactory::instance().createNum();
}

void NumDisplayButton::displayNumAux(int firstDigit, int secondDigit)
{
	leftNum->changeAnimation(firstDigit);
	rightNum->changeAnimation(secondDigit);
}

void NumDisplayButton::setPosition(glm::vec2 position) {
	this->position = position;
	leftNum->setPosition(this->position + glm::vec2(4, 1));
	rightNum->setPosition(this->position + glm::vec2(8, 1));
}

