#include "PercentageDisplay.h"
#include "GreenNumFactory.h"

void PercentageDisplay::init() {
	firstNum = GreenNumFactory::instance().createNum();
	secondNum = GreenNumFactory::instance().createNum();
	thirdNum = GreenNumFactory::instance().createNum();
	percentage = GreenNumFactory::instance().createSymbol('%');
	setPosition(glm::vec2(0, 0));

}

void PercentageDisplay::displayPercentage(int num) {
	int firstDigit = num / 100;
	int secondDigit = (num /10) % 10;
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

void PercentageDisplay::render() {
	firstNum->render();
	secondNum->render();
	thirdNum->render();
	percentage->render();
	
}

void PercentageDisplay::setPosition(glm::vec2 position) {
	this->position = position;
	firstNum->setPosition(this->position + glm::vec2(4, 0));
	secondNum->setPosition(this->position + glm::vec2(12, 0));
	thirdNum->setPosition(this->position + glm::vec2(20, 0));
	percentage->setPosition(this->position + glm::vec2(28, 0));
}



