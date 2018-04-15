#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Walker.h"
#include "Game.h"
#include "Scene.h"
#include "JobFactory.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum WalkerAnims
{
	WALKING_LEFT, WALKING_RIGHT,
	FALLING_RIGHT, FALLING_LEFT,
	FALLING_DEATH,
	DROWNING_DEATH,
	BURNING_DEATH,
	ESCAPING
};


void Walker::initAnims(ShaderProgram &shaderProgram) {
	jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram, &Game::spriteSheets().lemmingAnimations, &Game::spriteSheets().rotatedLemmingAnimations);
	jobSprite->setNumberAnimations(7);
	
	// WALKING
	jobSprite->setAnimationSpeed(WALKING_RIGHT, 12);
	for (int i = 0; i < 8; i++) {
		jobSprite->addKeyframe(WALKING_RIGHT, glm::vec2(float(i) / 16, 0.0f));
	}

	jobSprite->setAnimationSpeed(WALKING_LEFT, 12);
	for (int i = 0; i < 8; i++) {
		jobSprite->addKeyframe(WALKING_LEFT, glm::vec2((15-float(i)) / 16, 0.0f), true);
	}


	// FALLING
	jobSprite->setAnimationSpeed(FALLING_RIGHT, 12);
	for (int i = 0; i < 4; i++) {
		jobSprite->addKeyframe(FALLING_RIGHT, glm::vec2(float(i) / 16, 2.0f / 14));
	}

	jobSprite->setAnimationSpeed(FALLING_LEFT, 12);
	for (int i = 0; i < 4; i++) {
		jobSprite->addKeyframe(FALLING_LEFT, glm::vec2((15 - float(i)) / 16, 2.0f / 14), true);
	}


	// FALLING_DEATH
	jobSprite->setAnimationSpeed(FALLING_DEATH, 12);
	for (int i = 0; i < 16; i++) {
		jobSprite->addKeyframe(FALLING_DEATH, glm::vec2(float(i) / 16, 11.0f / 14));
	}

	// DROWNING_DEATH
	jobSprite->setAnimationSpeed(DROWNING_DEATH, 12);
	for (int i = 0; i<16; i++) {
		jobSprite->addKeyframe(DROWNING_DEATH, glm::vec2(float(i) / 16, 12.0f / 14));
	}

	// BURNING_DEATH
	jobSprite->setAnimationSpeed(BURNING_DEATH, 12);
	for (int i = 0; i<16; i++) {
		jobSprite->addKeyframe(BURNING_DEATH, glm::vec2(float(i) / 16, 13.0f / 14));
	}

	state = FALLING_RIGHT_STATE;
	jobSprite->changeAnimation(FALLING_RIGHT);
}

void Walker::setWalkingRight(bool value)
{
	walkingRight = value;
}

void Walker::updateStateMachine(int deltaTime) {
	int fall;

	switch (state)
	{
	case FALLING_LEFT_STATE:
		fall = collisionFloor(2);
		if (fall > 0)
			jobSprite->position() += glm::vec2(0, fall);
		else {
			jobSprite->changeAnimation(WALKING_LEFT);
			state = WALKING_LEFT_STATE;
			setWalkingRight(false);
		}
		break;
	case FALLING_RIGHT_STATE:
		fall = collisionFloor(2);
		if (fall > 0)
			jobSprite->position() += glm::vec2(0, fall);
		else {
			jobSprite->changeAnimation(WALKING_RIGHT);
			state = WALKING_RIGHT_STATE;
			setWalkingRight(true);
		}
		break;
	case WALKING_LEFT_STATE:
		jobSprite->position() += glm::vec2(-1, -1);
		
		if (collision())
		{
			jobSprite->position() -= glm::vec2(-1, -1);
			jobSprite->changeAnimation(WALKING_RIGHT);
			state = WALKING_RIGHT_STATE;
			setWalkingRight(true);
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
			setWalkingRight(false);
			
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
	}
}


