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
		jobSprite->addKeyframe(BASHER_LEFT, glm::vec2(float(i % 16) / 16, (6.0f + i / 16) / 14));
	
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
		if (jobSprite->getAnimationCurrentFrame() == 0) {
			bash_right();
		}

		fall = collisionFloor(3);
		if (fall < 3)
			jobSprite->position() += glm::vec2(0, fall);
		else {
			jobSprite->changeAnimation(FALLING_RIGHT);
			state = FALLING_RIGHT_STATE;
		}
	case BASHING_LEFT_STATE:
		if (jobSprite->getAnimationCurrentFrame() == 0) {
			bash_left();
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

void Basher::bash_right()
{
	glm::ivec2 posBase = jobSprite->position() + glm::vec2(120, 0);

	posBase += glm::ivec2(8, 16);

	int y = posBase.y;
	int x = posBase.x;
	
	Scene::getInstance().eraseMask(x, y);
	Scene::getInstance().eraseMask(x, y-1);
	Scene::getInstance().eraseMask(x, y-2);
	Scene::getInstance().eraseMask(x, y-3);
	Scene::getInstance().eraseMask(x, y-4);
	Scene::getInstance().eraseMask(x, y-5);
	Scene::getInstance().eraseMask(x, y-6);

	/*Scene::getInstance().eraseMask(x, y - 8);

	Scene::getInstance().eraseMask(x + 1, y - 8);

	Scene::getInstance().eraseMask(x + 2, y - 8);

	Scene::getInstance().eraseMask(x + 3, y);
	Scene::getInstance().eraseMask(x + 3, y - 8);
	
	Scene::getInstance().eraseMask(x + 4, y);
	Scene::getInstance().eraseMask(x + 4, y - 1);
	Scene::getInstance().eraseMask(x + 4, y - 2);
	Scene::getInstance().eraseMask(x + 4, y - 3);
	Scene::getInstance().eraseMask(x + 4, y - 4);
	Scene::getInstance().eraseMask(x + 4, y - 5);
	Scene::getInstance().eraseMask(x + 4, y - 6);
	Scene::getInstance().eraseMask(x + 4, y - 7);
	Scene::getInstance().eraseMask(x + 4, y - 8);

	Scene::getInstance().eraseMask(x + 5, y);
	Scene::getInstance().eraseMask(x + 5, y - 1);
	Scene::getInstance().eraseMask(x + 5, y - 2);
	Scene::getInstance().eraseMask(x + 5, y - 3);
	Scene::getInstance().eraseMask(x + 5, y - 4);
	Scene::getInstance().eraseMask(x + 5, y - 5);
	Scene::getInstance().eraseMask(x + 5, y - 6);
	Scene::getInstance().eraseMask(x + 5, y - 7);
	Scene::getInstance().eraseMask(x + 5, y - 8);

	Scene::getInstance().eraseMask(x + 6, y - 1);
	Scene::getInstance().eraseMask(x + 6, y - 2);
	Scene::getInstance().eraseMask(x + 6, y - 3);
	Scene::getInstance().eraseMask(x + 6, y - 4);
	Scene::getInstance().eraseMask(x + 6, y - 5);
	Scene::getInstance().eraseMask(x + 6, y - 6);*/

	jobSprite->position() += glm::vec2(1, 0);
}


void Basher::bash_left()
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






