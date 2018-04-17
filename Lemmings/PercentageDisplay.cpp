#include "PercentageDisplay.h"
#include "GreenNumFactory.h"

void PercentageDisplay::init() {
	setPosition(glm::vec2(0, 0));
}

void PercentageDisplay::displayPercentage(int num) {
	int firstDigit = num / 100;
	int secondDigit = (num /10) % 10;
	int thirdDigit = num % 10;
	
	delete firstNum;
	delete secondNum;
	delete thirdNum;

	if (firstDigit == 0) {
		firstNum = NULL;

		if (secondDigit == 0) {
			secondNum = NULL;
		}
		else {
			secondNum = GreenNumFactory::instance().createNum(secondDigit);
			secondNum->setPosition(this->position + glm::vec2(12, 0));
		}
	}
	else {
		firstNum = GreenNumFactory::instance().createNum(firstDigit);
		firstNum->setPosition(this->position + glm::vec2(4, 0));

		secondNum = GreenNumFactory::instance().createNum(secondDigit);
		secondNum->setPosition(this->position + glm::vec2(12, 0));
	}

	thirdNum = GreenNumFactory::instance().createNum(thirdDigit);
	thirdNum->setPosition(this->position + glm::vec2(20, 0));

	percentage = GreenNumFactory::instance().createSymbol('%');
	percentage->setPosition(this->position + glm::vec2(28, 0));

}

void PercentageDisplay::render() {
	if (firstNum != NULL) {
		firstNum->render();
	}

	if (secondNum != NULL) {
		secondNum->render();
	}

	if (thirdNum != NULL) {
		thirdNum->render();
	}

	if (percentage != NULL) {
		percentage->render();
	}
	
}

void PercentageDisplay::setPosition(glm::vec2 position) {
	this->position = position;

	if (firstNum != NULL) {
		firstNum->setPosition(this->position + glm::vec2(4, 0));
	}

	if (secondNum != NULL) {
		secondNum->setPosition(this->position + glm::vec2(12, 0));
	}

	if (thirdNum != NULL) {
		thirdNum->setPosition(this->position + glm::vec2(20, 0));
	}

	if (percentage != NULL) {
		percentage->setPosition(this->position + glm::vec2(28, 0));
	}


}



