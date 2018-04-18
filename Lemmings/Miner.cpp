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
	MINER_RIGHT, MINER_LEFT
};


void Miner::initAnims(ShaderProgram &shaderProgram) {
	jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram, &Game::spriteSheets().lemmingAnimations, &Game::spriteSheets().rotatedLemmingAnimations);
	jobSprite->setNumberAnimations(2);


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

	state = MINER_RIGHT_STATE;
	jobSprite->changeAnimation(MINER_RIGHT);

	
}

void Miner::setWalkingRight(bool value)
{
	walkingRight = value;

	if (walkingRight) {
		state = MINER_RIGHT_STATE;
		jobSprite->changeAnimation(MINER_RIGHT);
	}
	else {
		state = MINER_LEFT_STATE;
		jobSprite->changeAnimation(MINER_LEFT);
	}
}

void Miner::updateStateMachine(int deltaTime) {
	int fall;

	switch (state)
	{
	
	case MINER_RIGHT_STATE:
		if (jobSprite->getAnimationCurrentFrame() == 0) {
			mine_right();
		}

		fall = collisionFloor(3);
		if (fall < 3)
			jobSprite->position() += glm::vec2(0, fall);
		else {
			isFinished = true;
			nextJob = JobFactory::instance().createFallerJob();
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
			isFinished = true;
			nextJob = JobFactory::instance().createFallerJob();
		}
	}
}

string Miner::getName()
{
	return "MINER";
}

void Miner::mine_right()
{
	glm::ivec2 posBase = jobSprite->position();

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
	glm::ivec2 posBase = jobSprite->position();

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







