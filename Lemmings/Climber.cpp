#include "Climber.h"
#include "Game.h"
#include "JobFactory.h"


enum ClimberAnims
{
	WALKING_LEFT, WALKING_RIGHT,
	CLIMBING_LEFT, CLIMBING_RIGHT,
	LEDGING_LEFT, LEDGING_RIGHT
};


void Climber::initAnims(ShaderProgram &shaderProgram) {
	jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram, &Game::spriteSheets().lemmingAnimations, &Game::spriteSheets().rotatedLemmingAnimations);
	jobSprite->setNumberAnimations(6);
	
	// CLIMBER 
	jobSprite->setAnimationSpeed(CLIMBING_RIGHT, 12);
	for (int i = 0; i<8; i++)
		jobSprite->addKeyframe(CLIMBING_RIGHT, glm::vec2(float(i) / 16, 4.0f / 14));

	jobSprite->setAnimationSpeed(CLIMBING_LEFT, 12);
	for (int i = 0; i<8; i++)
		jobSprite->addKeyframe(CLIMBING_LEFT, glm::vec2(float(15-i) / 16, 4.0f / 14), true);

	jobSprite->setAnimationSpeed(LEDGING_RIGHT, 12);
	for (int i = 0; i<8; i++)
		jobSprite->addKeyframe(LEDGING_RIGHT, glm::vec2(float(i+8) / 16, 4.0f / 14));

	jobSprite->setAnimationSpeed(LEDGING_LEFT, 12);
	for (int i = 0; i<8; i++)
		jobSprite->addKeyframe(LEDGING_LEFT, glm::vec2(float(7-i) / 16, 4.0f / 14), true);

	// WALKING
	jobSprite->setAnimationSpeed(WALKING_RIGHT, 12);
	for (int i = 0; i < 8; i++) {
		jobSprite->addKeyframe(WALKING_RIGHT, glm::vec2(float(i) / 16, 0.0f));
	}

	jobSprite->setAnimationSpeed(WALKING_LEFT, 12);
	for (int i = 0; i < 8; i++) {
		jobSprite->addKeyframe(WALKING_LEFT, glm::vec2(float(15 - i) / 16, 0.0f), true);
	}

}

void Climber::setWalkingRight(bool value)
{
	walkingRight = value;

	if (walkingRight) {
		jobSprite->changeAnimation(WALKING_RIGHT);
		state = WALKING_RIGHT_STATE;
	}
	else {
		jobSprite->changeAnimation(WALKING_LEFT);
		state = WALKING_LEFT_STATE;
	}
}

void Climber::updateStateMachine(int deltaTime) {
	int fall;

	switch (state)
	{
	case WALKING_LEFT_STATE:
		jobSprite->position() += glm::vec2(-1, -1);
		
		if (collision())
		{
			jobSprite->position() -= glm::vec2(-1, -1);
			jobSprite->changeAnimation(CLIMBING_LEFT);
			state = CLIMBING_LEFT_STATE;
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

				isFinished = true;
				nextJob = JobFactory::instance().createFallerJob();
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
			jobSprite->changeAnimation(CLIMBING_RIGHT);
			state = CLIMBING_RIGHT_STATE;
			
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
				isFinished = true;
				nextJob = JobFactory::instance().createFallerJob();
			}

		}
		break;
	case CLIMBING_LEFT_STATE:
		climbLeft();
		break;
	case CLIMBING_RIGHT_STATE:
		climbRight();
		break;
	case LEDGING_LEFT_STATE:
		if (jobSprite->isInLastFrame()) {
			jobSprite->position() += glm::vec2(-2, -3);
			jobSprite->changeAnimation(WALKING_LEFT);
			state = WALKING_LEFT_STATE;
		}
		break;
	case LEDGING_RIGHT_STATE:
		if (jobSprite->hasIterated()) {
			jobSprite->position() += glm::vec2(3, -3);
			jobSprite->changeAnimation(WALKING_RIGHT);
			state = WALKING_RIGHT_STATE;
		}
		break;

	}
}

string Climber::getName()
{
	return "CLIMBER";
}


void Climber::climbLeft()
{
	jobSprite->position() -= glm::vec2(0, 1);

	
	glm::vec2 posBase = jobSprite->position() + glm::vec2(7, 15);

	if (Scene::getInstance().getMaskedMap().pixel(jobSprite->position().x + 7, jobSprite->position().y + 1) != 0) {
		jobSprite->position() += glm::vec2(2, 0);
		isFinished = true;
		nextJob = JobFactory::instance().createFallerJob();
	}
	else if (Scene::getInstance().getMaskedMap().pixel(posBase.x - 1, posBase.y - 3) == 0) {
		jobSprite->changeAnimation(LEDGING_LEFT);
		state = LEDGING_LEFT_STATE;
	}

}

void Climber::climbRight()
{
	jobSprite->position() -= glm::vec2(0, 1);


	glm::vec2 posBase = jobSprite->position() + glm::vec2(8, 15);
	if (Scene::getInstance().getMaskedMap().pixel(jobSprite->position().x + 8, jobSprite->position().y + 1) != 0) {
		jobSprite->position() += glm::vec2(-2, 0);
		isFinished = true;
		nextJob = JobFactory::instance().createFallerJob();
	}
	else if (Scene::getInstance().getMaskedMap().pixel(posBase.x + 1, posBase.y - 3) == 0) {
		jobSprite->changeAnimation(LEDGING_RIGHT);
		state = LEDGING_RIGHT_STATE;
	}
}