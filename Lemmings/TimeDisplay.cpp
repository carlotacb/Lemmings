#include "TimeDisplay.h"
#include "GreenNumFactory.h"

void TimeDisplay::init() {
	setPosition(glm::vec2(0, 0));
}

void TimeDisplay::displayTime(int num) {
	int firstDigit = num / 60;
	int secondDigit = (num %60) / 10;
	int thirdDigit = (num % 60) % 10;
	
	delete minutes;
	delete firstDigitSeconds;
	delete secondDigitSeconds;

	minutes = GreenNumFactory::instance().createNum(firstDigit);
	minutes->setPosition(this->position + glm::vec2(4, 0));

	hyphen = GreenNumFactory::instance().createSymbol('-');
	hyphen->setPosition(this->position + glm::vec2(12, 0));

	firstDigitSeconds = GreenNumFactory::instance().createNum(secondDigit);
	firstDigitSeconds->setPosition(this->position + glm::vec2(20, 0));
	
	secondDigitSeconds = GreenNumFactory::instance().createNum(thirdDigit);
	secondDigitSeconds->setPosition(this->position + glm::vec2(28, 0));

}

void TimeDisplay::render() {
	if (minutes != NULL) {
		minutes->render();
	}

	if (firstDigitSeconds != NULL) {
		firstDigitSeconds->render();
	}

	if (secondDigitSeconds != NULL) {
		secondDigitSeconds->render();
	}

	if (hyphen != NULL) {
		hyphen->render();
	}
	
}

void TimeDisplay::setPosition(glm::vec2 position) {
	this->position = position;

	if (minutes != NULL) {
		minutes->setPosition(this->position + glm::vec2(4, 0));
	}

	if (hyphen != NULL) {
		hyphen->setPosition(this->position + glm::vec2(12, 0));
	}


	if (firstDigitSeconds != NULL) {
		firstDigitSeconds->setPosition(this->position + glm::vec2(20, 0));
	}

	if (secondDigitSeconds != NULL) {
		secondDigitSeconds->setPosition(this->position + glm::vec2(28, 0));
	}

	

}



