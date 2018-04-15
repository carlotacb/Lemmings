#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Digger.h"
#include "Game.h"
#include "Scene.h"
#include "JobFactory.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum DiggerAnims
{
	FALLING_RIGHT, FALLING_LEFT,
	DIGGER,
	FALLING_DEATH,
	DROWNING_DEATH,
	BURNING_DEATH,
	ESCAPING
};


void Digger::initAnims(ShaderProgram &shaderProgram) {
	jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram, &Game::spriteSheets().lemmingAnimations, &Game::spriteSheets().rotatedLemmingAnimations);
	jobSprite->setNumberAnimations(6);

	// FALLING
	jobSprite->setAnimationSpeed(FALLING_RIGHT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FALLING_RIGHT, glm::vec2(float(i) / 16, 2.0f / 14));

	jobSprite->setAnimationSpeed(FALLING_LEFT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FALLING_LEFT, glm::vec2((15 - float(i)) / 16, 2.0f / 14), true);


	// DIGGER
	jobSprite->setAnimationSpeed(DIGGER, 12);
	for (int i = 0; i<8; i++)
		jobSprite->addKeyframe(DIGGER, glm::vec2(float(i) / 16, 8.0f / 14));


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

	state = DIGGING_STATE;
	jobSprite->changeAnimation(DIGGER);

}

void Digger::setWalkingRight(bool value)
{
	walkingRight = value;
}

void Digger::updateStateMachine(int deltaTime) {
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
	case DIGGING_STATE:
		if (jobSprite->getAnimationCurrentFrame() == 0) {
			dig();
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

void Digger::dig()
{
	glm::ivec2 posBase = jobSprite->position() + glm::vec2(120, 0);
	
	posBase += glm::ivec2(5, 16);

	int y = posBase.y;

	for (int i = 0; i < 7; ++i) {
		int x = posBase.x + i;
		Scene::getInstance().eraseMask(x, y);
	}
	jobSprite->position() += glm::vec2(0, -1);
}







