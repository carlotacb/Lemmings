#include "Builder.h"
#include "Game.h"
#include "ShaderManager.h"
#include "JobFactory.h"


enum BuilderAnims
{
	BUILDING_LEFT, BUILDING_RIGHT,
	NOSTEPS
};


void Builder::initAnims(ShaderProgram &shaderProgram) {
	jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram, &Game::spriteSheets().lemmingAnimations, &Game::spriteSheets().rotatedLemmingAnimations);
	jobSprite->setNumberAnimations(3);
	
	// BUILDER 
	jobSprite->setAnimationSpeed(BUILDING_RIGHT, 12);
	for (int i = 0; i<16; i++)
		jobSprite->addKeyframe(BUILDING_RIGHT, glm::vec2(float(i) / 16, 5.0f / 14));

	jobSprite->setAnimationSpeed(BUILDING_LEFT, 12);
	for (int i = 0; i<16; i++)
		jobSprite->addKeyframe(BUILDING_LEFT, glm::vec2(float(15- i) / 16, 5.0f / 14), true);
	
	jobSprite->setAnimationSpeed(NOSTEPS, 12);
	for (int i = 0; i<6; i++)
		jobSprite->addKeyframe(NOSTEPS, glm::vec2(float(10 + i) / 16, 0));


}

void Builder::setWalkingRight(bool value)
{
	walkingRight = value;

	if (walkingRight) {
		jobSprite->changeAnimation(BUILDING_RIGHT);
		state = BUILDING_RIGHT_STATE;
	}
	else {
		jobSprite->changeAnimation(BUILDING_LEFT);
		state = BUILDING_LEFT_STATE;
	}
}

void Builder::updateStateMachine(int deltaTime) {
	int fall;

	switch (state)
	{
	case BUILDING_LEFT_STATE:
		if (cannotBuildLeft()) {
			jobSprite->changeAnimation(NOSTEPS);
			state = NOSTEPS_STATE;
		}
		else {
			buildLeft();
		}
		break;
	case BUILDING_RIGHT_STATE:
		if (cannotBuildRight()) {
			jobSprite->changeAnimation(NOSTEPS);
			state = NOSTEPS_STATE;
			
		}
		else {
			buildRight();
		}

		break;
	case NOSTEPS_STATE:
		if (jobSprite->isInLastFrame()) {
			isFinished = true;
			nextJob = JobFactory::instance().createWalkerJob();
		}
		break;
	}
}

string Builder::getName()
{
	return "BUILDER";
}


void Builder::buildLeft()
{
	if (jobSprite->hasIterated()) {
		glm::vec2 posBase = jobSprite->position() + glm::vec2(3, 15);
		Scene::getInstance().buildStep(posBase);
		jobSprite->position() += glm::vec2(-2, -1);
		++buildedSteps;
		jobSprite->setIterated(false);
	}
}

void Builder::buildRight()
{
	if (jobSprite->hasIterated()) {
		glm::vec2 posBase = jobSprite->position() + glm::vec2(8, 15);
		Scene::getInstance().buildStep(posBase);
		jobSprite->position() += glm::vec2(2, -1);
		++buildedSteps;
		jobSprite->setIterated(false);
	}
}

bool Builder::cannotBuildRight()
{
	
	bool obtured = false;

	glm::vec2 posBase = jobSprite->position() + glm::vec2(9, 15);
	for (int i = 0; i < 4; ++i) {
		if (Scene::getInstance().getPixel(posBase.x + i, posBase.y) != 0) {
			obtured = true;
		}
	}
	return buildedSteps >= MAX_STEPS || obtured;
}

bool Builder::cannotBuildLeft()
{

	bool obtured = false;

	glm::vec2 posBase = jobSprite->position() + glm::vec2(3, 15);
	for (int i = 0; i < 4; ++i) {
		if (Scene::getInstance().getPixel(posBase.x + i, posBase.y) != 0) {
			obtured = true;
		}
	}
	return buildedSteps >= MAX_STEPS || obtured;
}