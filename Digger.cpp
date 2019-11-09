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
	DIGGER
};


void Digger::initAnims(ShaderProgram &shaderProgram) {
	jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram, &Game::spriteSheets().lemmingAnimations, &Game::spriteSheets().rotatedLemmingAnimations);
	jobSprite->setNumberAnimations(1);

	// DIGGER
	jobSprite->setAnimationSpeed(DIGGER, 12);
	for (int i = 0; i<8; i++)
		jobSprite->addKeyframe(DIGGER, glm::vec2(float(i) / 16, 8.0f / 14));


	state = DIGGING_STATE;
	jobSprite->changeAnimation(DIGGER);
}

void Digger::setWalkingRight(bool value)
{
	walkingRight = value;
}

void Digger::updateStateMachine(int deltaTime) {

	switch (state)
	{
	
	case DIGGING_STATE:
		if (!canDig()) {
			isFinished = true;

			int fall = collisionFloor(3);
			if (fall >= 3) {
				nextJob = JobFactory::instance().createFallerJob();
			}
			else {
				nextJob = JobFactory::instance().createWalkerJob();
			}
		}
		
		else if (jobSprite->isInFirstFrame() || jobSprite->getAnimationCurrentFrame() == 4) {
			dig();
		}

	}
}

string Digger::getName()
{
	return "DIGGER";
}

bool Digger::canDig()
{
	bool canDig = false;

	glm::ivec2 posBase = jobSprite->position();

	posBase += glm::ivec2(4, 14);


	for (int j = 0; j < 3; ++j) {
		for (int i = 0; i < 9; ++i) {
			int x = posBase.x + i;
			int y = posBase.y + j;
			if (Scene::getInstance().getPixel(x, y) == -1) {
				return true;
			}
		}
	}
	
	return false;
}

void Digger::dig()
{

	glm::ivec2 posBase = jobSprite->position();
	
	posBase += glm::ivec2(4, 14);

	int y = posBase.y;

	for (int i = 0; i < 9; ++i) {
		int x = posBase.x + i;
		Scene::getInstance().eraseMask(x, y);
	}

	jobSprite->position() += glm::ivec2(0, 1);

	
}







