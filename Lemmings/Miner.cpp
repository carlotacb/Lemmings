#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Miner.h"
#include "Game.h"
#include "Scene.h"
#include "JobFactory.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum MinerAnims
{
	FALLING_RIGHT, FALLING_LEFT,
	MINER_RIGHT, MINER_LEFT,
	FALLING_DEATH,
	DROWNING_DEATH,
	BURNING_DEATH
};


void Miner::initAnims(ShaderProgram &shaderProgram) {
	jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram, &Game::spriteSheets().lemmingAnimations, &Game::spriteSheets().rotatedLemmingAnimations);
	jobSprite->setNumberAnimations(7);

	// FALLING
	jobSprite->setAnimationSpeed(FALLING_RIGHT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FALLING_RIGHT, glm::vec2(float(i) / 16, 2.0f / 14));

	jobSprite->setAnimationSpeed(FALLING_LEFT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FALLING_LEFT, glm::vec2((15 - float(i)) / 16, 2.0f / 14), true);


	// MINER
	jobSprite->setAnimationSpeed(MINER_RIGHT, 12);
	for (int i = 0; i<24; i++)
		if (i < 8) {
			jobSprite->addKeyframe(MINER_RIGHT, glm::vec2(float(i + 8) / 16, 8.0f / 14));
		}
		else {
			jobSprite->addKeyframe(MINER_RIGHT, glm::vec2(float(i) / 16, 9.0f / 14));
		}

	jobSprite->setAnimationSpeed(MINER_LEFT, 12);
	for (int i = 0; i<24; i++)
		if (i < 8) {
			jobSprite->addKeyframe(MINER_LEFT, glm::vec2((15 - float(i + 8) )/ 16, 8.0f / 14),true);
		}
		else {
			jobSprite->addKeyframe(MINER_LEFT, glm::vec2(((15-float(i)) / 16), 9.0f / 14), true);
		}

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

	//state = MINER_RIGHT_STATE;
	//jobSprite->changeAnimation(MINER_RIGHT);

	if (isWalkingRight()) {
		state = MINER_RIGHT_STATE;
		jobSprite->changeAnimation(MINER_RIGHT);
	}
	else {
		state = MINER_LEFT_STATE;
		jobSprite->changeAnimation(MINER_LEFT);
	}
}

void Miner::setWalkingRight(bool value)
{
	walkingRight = value;
}

void Miner::updateStateMachine(int deltaTime) {
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
	
	case MINER_RIGHT_STATE:
		if (jobSprite->getAnimationCurrentFrame() == 0) {
			mine_right();
		}

		fall = collisionFloor(3);
		if (fall < 3)
			jobSprite->position() += glm::vec2(0, fall);
		else {
			jobSprite->changeAnimation(FALLING_RIGHT);
			state = FALLING_RIGHT_STATE;
		}
		break;
	case MINER_LEFT_STATE:
		if (jobSprite->getAnimationCurrentFrame() == 0) {
			mine_left();
		}

		fall = collisionFloor(3);
		if (fall < 3)
			jobSprite->position() += glm::vec2(0, fall);
		else {
			jobSprite->changeAnimation(FALLING_LEFT);
			state = FALLING_LEFT_STATE;
		}
	}
}

void Miner::mine_right()
{
	glm::ivec2 posBase = jobSprite->position() + Level::currentLevel().getLevelAttributes()->textureCoordStart;

	posBase += glm::ivec2(10, 16);
	
	int x = posBase.x;
	int y = posBase.y;
		
	for (int i = 0; i < 3; ++i) {
		Scene::getInstance().eraseMask(x + i, y);
		Scene::getInstance().eraseMask(x + i, y - 12);
	}
		
	for (int i = 0; i < 12; i += 11) {
		Scene::getInstance().eraseMask(x + 3, y - i);
		Scene::getInstance().eraseMask(x + 3, y - (i + 1));
	}
		
	for (int i = 1; i < 12; ++i) {
		Scene::getInstance().eraseMask(x + 4, y - i);
	}
	
	for (int i = 2; i < 11; ++i) {
		Scene::getInstance().eraseMask(x + 5, y - i);
	}

	jobSprite->position() += glm::vec2(1, 1);
}


void Miner::mine_left()
{
	glm::ivec2 posBase = jobSprite->position() + Level::currentLevel().getLevelAttributes()->textureCoordStart;

	posBase += glm::ivec2(0, 16);

	int x = posBase.x;
	int y = posBase.y;

	for (int i = 2; i < 11; ++i) {
		Scene::getInstance().eraseMask(x, y - i);
	}

	for (int i = 1; i < 12; ++i) {
		Scene::getInstance().eraseMask(x + 1, y - i);
	}

	for (int i = 0; i < 12; i += 11) {
		Scene::getInstance().eraseMask(x + 2, y - i);
		Scene::getInstance().eraseMask(x + 2, y - (i + 1));
	}

	for (int i = 3; i < 6; ++i) {
		for (int j = 0; j < 13; j += 12) {
			Scene::getInstance().eraseMask(x + i, y - j);
		}
	}
		
	jobSprite->position() += glm::vec2(-1, 1);
}







