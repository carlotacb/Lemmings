#include "Faller.h"
#include "Game.h"
#include "Scene.h"
#include "JobFactory.h"

enum FallerAnims
{
	FALLING_RIGHT, FALLING_LEFT,
	FALLING_DEATH
};


void Faller::initAnims(ShaderProgram &shaderProgram) 
{
	jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram, &Game::spriteSheets().lemmingAnimations, &Game::spriteSheets().rotatedLemmingAnimations);
	jobSprite->setNumberAnimations(3);

	// FALLING
	jobSprite->setAnimationSpeed(FALLING_RIGHT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FALLING_RIGHT, glm::vec2(float(i) / 16, 2.0f / 14));

	jobSprite->setAnimationSpeed(FALLING_LEFT, 12);
	for (int i = 0; i<4; i++)
		jobSprite->addKeyframe(FALLING_LEFT, glm::vec2((15 - float(i)) / 16, 2.0f / 14), true);

	
	// FALLING_DEATH
	jobSprite->setAnimationSpeed(FALLING_DEATH, 12);
	for (int i = 0; i<16; i++)
		jobSprite->addKeyframe(FALLING_DEATH, glm::vec2(float(i) / 16, 11.0f / 14));



	state = FALLING_RIGHT_STATE;
	jobSprite->changeAnimation(FALLING_RIGHT);

}

void Faller::setWalkingRight(bool value)
{
	walkingRight = value;

	if (walkingRight) {
		jobSprite->changeAnimation(FALLING_RIGHT);
		state = FALLING_RIGHT_STATE;
	}
	else {
		jobSprite->changeAnimation(FALLING_LEFT);
		state = FALLING_LEFT_STATE;
	}
}

void Faller::updateStateMachine(int deltaTime) {
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

		case FALLING_DEATH_STATE:
			break;
	}
}

string Faller::getName() 
{
	return "FALLER";
}








