#include "Countdown.h"
#include "ButtonNumFactory.h"
#include "Level.h"
#include "LevelManager.h"

#define MAX_SEC 5

Countdown::Countdown()
{
	goalTime = MAX_SEC + LevelManager::getInstance().getCurrentTime();
	countNum = ButtonNumFactory::instance().createNum();
	countNum->changeAnimation(MAX_SEC);
	over = false;
}

void Countdown::render()
{
	glm::vec2 oldPosition = countNum->position();
	countNum->setPosition(countNum->position() - Level::currentLevel().getLevelAttributes()->cameraPos);
	countNum->render();
	countNum->setPosition(oldPosition);

}

void Countdown::setPosition(glm::vec2 position)
{
	countNum->setPosition(position);
}

void Countdown::update(int deltaTime)
{
	int currentTime = LevelManager::getInstance().getCurrentTime();
	int currentSec = goalTime - currentTime;
	if (currentSec <= 0) {
		over = true;
	}
	else {
		countNum->changeAnimation(currentSec);
	}
}

bool Countdown::isOver()
{
	return over;
}