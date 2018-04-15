#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Floater.h"
#include "Game.h"
#include "Scene.h"
#include "JobFactory.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum FloaterAnims
{
	WALKING_LEFT, WALKING_RIGHT,
	FALLING_RIGHT, FALLING_LEFT,
	FLOATER_OPENING_RIGHT, FLOATER_OPENING_LEFT, FLOATER_FALLING_RIGHT, FLOATER_FALLING_LEFT,
	DROWNING_DEATH,
	BURNING_DEATH,
};


void Floater::initAnims(ShaderProgram &shaderProgram) {
	jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram, &Game::spriteSheets().lemmingAnimations, &Game::spriteSheets().rotatedLemmingAnimations);
	jobSprite->setNumberAnimations(10);

	// WALKING
	jobSprite->setAnimationSpeed(WALKING_RIGHT, 12);
	for (int i = 0; i < 8; i++) {
		jobSprite->addKeyframe(WALKING_RIGHT, glm::vec2(float(i) / 16, 0.0f));
	}

	jobSprite->setAnimationSpeed(WALKING_LEFT, 12);
	for (int i = 0; i < 8; i++) {
		jobSprite->addKeyframe(WALKING_LEFT, glm::vec2((15 - float(i)) / 16, 0.0f), true);
	}

	// FALLING
	jobSprite->setAnimationSpeed(FALLING_RIGHT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FALLING_RIGHT, glm::vec2(float(i) / 16, 2.0f / 14));

	jobSprite->setAnimationSpeed(FALLING_LEFT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FALLING_LEFT, glm::vec2((15 - float(i)) / 16, 2.0f / 14), true);

	// FLOATER 

	jobSprite->setAnimationSpeed(FLOATER_OPENING_RIGHT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FLOATER_OPENING_RIGHT, glm::vec2(float(i + 4) / 16, 2.0f / 14));

	jobSprite->setAnimationSpeed(FLOATER_OPENING_LEFT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FLOATER_OPENING_LEFT, glm::vec2((15 - float(i + 4)) / 16, 2.0f / 14), true);

	jobSprite->setAnimationSpeed(FLOATER_FALLING_RIGHT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FLOATER_FALLING_RIGHT, glm::vec2(float(i + 8) / 16, 2.0f / 14));

	jobSprite->setAnimationSpeed(FLOATER_FALLING_LEFT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FLOATER_FALLING_LEFT, glm::vec2((15 - float(i + 8)) / 16, 2.0f / 14), true);


	// DROWNING_DEATH
	jobSprite->setAnimationSpeed(DROWNING_DEATH, 12);
	for (int i = 0; i<16; i++)
		jobSprite->addKeyframe(DROWNING_DEATH, glm::vec2(float(i) / 16, 12.0f / 14));

	// BURNING_DEATH
	jobSprite->setAnimationSpeed(BURNING_DEATH, 12);
	for (int i = 0; i<16; i++)
		jobSprite->addKeyframe(BURNING_DEATH, glm::vec2(float(i) / 16, 13.0f / 14));

	state = WALKING_RIGHT_STATE;
	jobSprite->changeAnimation(WALKING_RIGHT);

}

void Floater::updateStateMachine(int deltaTime) {
	int fall;

	switch (state)
	{
	case WALKING_LEFT_STATE:
		jobSprite->position() += glm::vec2(-1, -1);

		if (collision())
		{
			jobSprite->position() -= glm::vec2(-1, -1);
			jobSprite->changeAnimation(WALKING_RIGHT);
			state = WALKING_RIGHT_STATE;
		}
		else
		{
			fall = collisionFloor(3);
			if (fall > 0) {
				jobSprite->position() += glm::vec2(0, 1);
			}
			if (fall > 1) {
				jobSprite->position() += glm::vec2(0, 1);
			}

			if (fall > 2) {
				jobSprite->changeAnimation(FALLING_LEFT);
				state = FALLING_LEFT_STATE;
			}
			else {
				if (jobSprite->position() == Level::currentLevel().getLevelAttributes()->door->getEscapePosition()) {
					isFinished = true;
					nextJob = JobFactory::instance().createEscaperJob();
				}
			}
		}
		break;

	case WALKING_RIGHT_STATE:
		jobSprite->position() += glm::vec2(1, -1);

		if (collision())
		{
			jobSprite->position() -= glm::vec2(1, -1);
			jobSprite->changeAnimation(WALKING_LEFT);
			state = WALKING_LEFT_STATE;
		}
		else
		{
			fall = collisionFloor(3);
			if (fall < 3) {
				jobSprite->position() += glm::vec2(0, fall);

				if (jobSprite->position() == Level::currentLevel().getLevelAttributes()->door->getEscapePosition()) {
					isFinished = true;
					nextJob = JobFactory::instance().createEscaperJob();
				}
			}
			else {
				jobSprite->changeAnimation(FALLING_RIGHT);
				state = FALLING_RIGHT_STATE;
			}

		}
		break;

	case FALLING_LEFT_STATE:
		if (jobSprite->hasIterated()) {
			jobSprite->changeAnimation(FLOATER_OPENING_LEFT);
			state = FLOATER_OPENING_LEFT_STATE;
		}
		else {
			fall = collisionFloor(2);
			if (fall > 0) {
				jobSprite->position() += glm::vec2(0, fall);
			}
		}
		break;
	case FALLING_RIGHT_STATE:
		if (jobSprite->hasIterated()) {
			jobSprite->changeAnimation(FLOATER_OPENING_RIGHT);
			state = FLOATER_OPENING_RIGHT_STATE;
		}
		else {
			fall = collisionFloor(2);
			if (fall > 0) {
				jobSprite->position() += glm::vec2(0, fall);
			}
		}
		break;

	case FLOATER_OPENING_LEFT_STATE:
		if (jobSprite->hasIterated()) {
			jobSprite->changeAnimation(FLOATER_FALLING_LEFT);
			state = FLOTATING_LEFT_STATE;
		}
		break;

	case FLOATER_OPENING_RIGHT_STATE:
		if (jobSprite->hasIterated()) {
			jobSprite->changeAnimation(FLOATER_FALLING_RIGHT);
			state = FLOTATING_RIGHT_STATE;
		}
		break;

	case FLOTATING_LEFT_STATE:
		fall = collisionFloor(2);
		if (fall > 0)
			jobSprite->position() += glm::vec2(0, fall);
		else {
			jobSprite->changeAnimation(WALKING_LEFT);
			state = WALKING_LEFT_STATE;
		}
		break;
	
	case FLOTATING_RIGHT_STATE:
		fall = collisionFloor(2);
		if (fall > 0)
			jobSprite->position() += glm::vec2(0, fall);
		else {
			jobSprite->changeAnimation(WALKING_RIGHT);
			state = WALKING_RIGHT_STATE;
		}
		break;

	}
}

void Floater::timeToFloat()
{
	glm::ivec2 posBase = jobSprite->position() + Level::currentLevel().getLevelAttributes()->offset;
	
	posBase += glm::ivec2(5, 16);

	int y = posBase.y;

	for (int i = 0; i < 7; ++i) {
		int x = posBase.x + i;
		Scene::getInstance().eraseMask(x, y);
	}
	jobSprite->position() += glm::vec2(0, -1);
}


void Floater::setWalkingRight(bool value) {
	return;
}




