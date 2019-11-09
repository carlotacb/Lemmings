#include "TimeDisplay.h"
#include "GreenNumFactory.h"

void TimeDisplay::init() {
	minutes = GreenNumFactory::instance().createNum();
	hyphen = GreenNumFactory::instance().createSymbol('-');
	firstDigitSeconds = GreenNumFactory::instance().createNum();
	secondDigitSeconds = GreenNumFactory::instance().createNum();
	setPosition(glm::vec2(0, 0));

}

void TimeDisplay::displayTime(int num) {
	int firstDigit = num / 60;
	int secondDigit = (num %60) / 10;
	int thirdDigit = (num % 60) % 10;

	minutes->changeAnimation(firstDigit);
	firstDigitSeconds->changeAnimation(secondDigit);
	secondDigitSeconds->changeAnimation(thirdDigit);
}

void TimeDisplay::render() {
	minutes->render();
	firstDigitSeconds->render();
	secondDigitSeconds->render();
	hyphen->render();
}

void TimeDisplay::setPosition(glm::vec2 position) {
	this->position = position;
	minutes->setPosition(this->position + glm::vec2(4, 0));
	hyphen->setPosition(this->position + glm::vec2(12, 0));
	firstDigitSeconds->setPosition(this->position + glm::vec2(20, 0));
	secondDigitSeconds->setPosition(this->position + glm::vec2(28, 0));

}



