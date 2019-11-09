#include "PurplePercentageDisplay.h"
#include "PurpleNumFactory.h"

void PurplePercentageDisplay::init() {
	firstNum = PurpleNumFactory::instance().createNum();
	secondNum = PurpleNumFactory::instance().createNum();
	thirdNum = PurpleNumFactory::instance().createNum();
	percentage = PurpleNumFactory::instance().createSymbol('%');
	setPosition(glm::vec2(0, 0));

}

void PurplePercentageDisplay::displayPercentage(int num) {
	int firstDigit = num / 100;
	int secondDigit = (num / 10) % 10;
	int thirdDigit = num % 10;

	if (firstDigit == 0) {
		firstNum->changeAnimation(10);

		if (secondDigit == 0) {
			secondNum->changeAnimation(10);
		}
		else {
			secondNum->changeAnimation(secondDigit);
		}
	}
	else {
		firstNum->changeAnimation(firstDigit);
		secondNum->changeAnimation(secondDigit);
	}

	thirdNum->changeAnimation(thirdDigit);

}

void PurplePercentageDisplay::render() {
	firstNum->render();
	secondNum->render();
	thirdNum->render();
	percentage->render();

}

void PurplePercentageDisplay::setPosition(glm::vec2 position) {
	this->position = position;
	firstNum->setPosition(this->position + glm::vec2(0, 0));
	secondNum->setPosition(this->position + glm::vec2(7, 0));
	thirdNum->setPosition(this->position + glm::vec2(14, 0));
	percentage->setPosition(this->position + glm::vec2(21, 0));
}






