#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Basher.h"
#include "Game.h"
#include "Scene.h"
#include "JobFactory.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum BasherAnims
{
	FALLING_RIGHT, FALLING_LEFT,
	BASHER_RIGHT, BASHER_LEFT,
	FALLING_DEATH,
	DROWNING_DEATH,
	BURNING_DEATH,
	ESCAPING
};

void Basher::initAnims(ShaderProgram &shaderProgram) {
	jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram, &Game::spriteSheets().lemmingAnimations, &Game::spriteSheets().rotatedLemmingAnimations);
	jobSprite->setNumberAnimations(8);

	// FALLING
	jobSprite->setAnimationSpeed(FALLING_RIGHT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FALLING_RIGHT, glm::vec2(float(i) / 16, 2.0f / 14));

	jobSprite->setAnimationSpeed(FALLING_LEFT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FALLING_LEFT, glm::vec2((15 - float(i)) / 16, 2.0f / 14), true);

	// BASHER
	jobSprite->setAnimationSpeed(BASHER_RIGHT, 12);
	for (int i = 0; i<32; i++)
		jobSprite->addKeyframe(BASHER_RIGHT, glm::vec2(float(i % 16) / 16, (6.0f + i / 16) / 14));
	jobSprite->setAnimationSpeed(BASHER_LEFT, 12);
	for (int i = 0; i<32; i++)
		jobSprite->addKeyframe(BASHER_LEFT, glm::vec2((15 - float(i % 16)) / 16, (6.0f + i / 16) / 14), true);
	
	// FALLING_DEATH
	jobSprite->setAnimationSpeed(FALLING_DEATH, 12);
	for (int i = 0; i<16; i++)
		jobSprite->addKeyframe(FALLING_DEATH, glm::vec2(float(i) / 16, 11.0f / 14));

	// DROWNING_DEATH
	jobSprite->setAnimationSpeed(DROWNING_DEATH, 12);
	for (int i = 0; i<16; i++)
		jobSprite->addKeyframe(DROWNING_DEATH, glm::vec2(float(i) / 16, 12.0f / 14));

	// BURNING_DEATH
	jobSprite->setAnimationSpeed(BURNING_DEATH, 12);
	for (int i = 0; i<16; i++)
		jobSprite->addKeyframe(BURNING_DEATH, glm::vec2(float(i) / 16, 13.0f / 14));

	state = BASHING_RIGHT_STATE;
	jobSprite->changeAnimation(BASHER_RIGHT);

}

void Basher::setWalkingRight(bool value)
{
	walkingRight = value;
	if (walkingRight) {
		jobSprite->changeAnimation(BASHER_RIGHT);
		state = BASHING_RIGHT_STATE;
	}
	else {
		jobSprite->changeAnimation(BASHER_LEFT);
		state = BASHING_LEFT_STATE;
	}
	

}

void Basher::updateStateMachine(int deltaTime) {
	int fall;

	switch (state)
	{
	case FALLING_LEFT_STATE:
		fall = collisionFloor(2);
		if (fall > 0)
			jobSprite->position() += glm::vec2(0, fall);
		else {
			isFinished = true;
			nextJob = JobFactory::instance().createWalkerJob();
		}
		break;
	case FALLING_RIGHT_STATE:
		fall = collisionFloor(2);
		if (fall > 0)
			jobSprite->position() += glm::vec2(0, fall);
		else {
			isFinished = true;
			nextJob = JobFactory::instance().createWalkerJob();
		}
		break;
	case BASHING_RIGHT_STATE:

		bashRight();

		fall = collisionFloor(3);
		if (fall < 3)
			jobSprite->position() += glm::vec2(0, fall);
		else {
			jobSprite->changeAnimation(FALLING_RIGHT);
			state = FALLING_RIGHT_STATE;
		}


	case BASHING_LEFT_STATE:
		int currentFrame = jobSprite->getAnimationCurrentFrame();
		if (currentFrame == 2 || currentFrame == 18) {
			bashLeft();
		}

		fall = collisionFloor(3);
		if (fall < 3)
			jobSprite->position() += glm::vec2(0, fall);
		else {
			jobSprite->changeAnimation(FALLING_RIGHT);
			state = FALLING_RIGHT_STATE;
		}
	}
}

void Basher::bashRight()
{
	int currentFrame = jobSprite->getAnimationCurrentFrame();
	if (currentFrame == 2 || currentFrame == 18) {
		glm::ivec2 posBase = jobSprite->position();

		posBase += glm::ivec2(8, 16);

		int y = posBase.y;
		int x = posBase.x;
		
		for (int i = 0; i <= 6; ++i) {
			for (int j = 0; j <= 8; ++j) {
				Scene::getInstance().eraseMask(x + i, y -1 - j);
			}
		}

		for (int i = 0; i <= 6; ++i) {
			Scene::getInstance().eraseMask(x + 7, y -2 - i);
		}
	}
	

	if (!((7 <= currentFrame && currentFrame <= 15) || (23 <= currentFrame && currentFrame <= 31))) {
		jobSprite->position() += glm::vec2(1, 0);
	}
}


void Basher::bashLeft()
{

}






