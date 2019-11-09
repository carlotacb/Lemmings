#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Job.h"
#include "Scene.h"

/*
enum LemmingAnims
{
	WALKING_LEFT, WALKING_RIGHT,
	FALLING_RIGHT, FALLING_LEFT,
	FLOATER_OPENING_RIGHT, FLOATER_OPENING_LEFT, FLOATER_FALLING_RIGHT, FLOATER_FALLING_LEFT,
	BLOCKER,
	CLIMBER_CLIMBLING_RIGHT, CLIMBER_CLIMBLING_LEFT, CLIMBER_LEDGING_RIGHT, CLIMBER_LEDGING_LEFT,
	BUILDER_RIGHT, BUILDER_LEFT,
	BASHER_RIGHT, BASHER_LEFT,
	DIGGER,
	MINER_RIGHT, MINER_LEFT,
	EXPLODER,
	FALLING_DEATH,
	DROWNING_DEATH,
	BURNING_DEATH,
	ESCAPING
};
*/


int Job::collisionFloor(int maxFall)
{
	bool bContact = false;
	int fall = 0;
	glm::ivec2 posBase = jobSprite->position(); 

	posBase += glm::ivec2(7, 16);
	while ((fall < maxFall) && !bContact)
	{
		if ((Scene::getInstance().getMaskedMap().pixel(posBase.x, posBase.y + fall) == 0) && (Scene::getInstance().getMaskedMap().pixel(posBase.x + 1, posBase.y + fall) == 0))
			fall += 1;
		else
			bContact = true;
	}

	return fall;
}

bool Job::collision()
{
	glm::ivec2 posBase = jobSprite->position();

	posBase += glm::ivec2(7, 15);
	if ((Scene::getInstance().getMaskedMap().pixel(posBase.x, posBase.y) == 0) && (Scene::getInstance().getMaskedMap().pixel(posBase.x + 1, posBase.y) == 0))
		return false;

	return true;
}


bool Job::finished()
{
	return isFinished;
}

Job* Job::getNextJob()
{
	return nextJob;
}


Sprite* Job::getJobSprite()
{
	return jobSprite;
}

void Job::setWalkingRight(bool value)
{
	walkingRight = value;
}

bool Job::isWalkingRight()
{
	return walkingRight;
}


/*



	// DROWNING_DEATH
	sprite->setAnimationSpeed(DROWNING_DEATH, 12);
	for (int i = 0; i<16; i++)
		sprite->addKeyframe(DROWNING_DEATH, glm::vec2(float(i) / 16, 12.0f / 14));

	// BURNING_DEATH
	sprite->setAnimationSpeed(BURNING_DEATH, 12);
	for (int i = 0; i<16; i++)
		sprite->addKeyframe(BURNING_DEATH, glm::vec2(float(i) / 16, 13.0f / 14));

		*/
