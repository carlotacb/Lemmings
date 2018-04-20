#include "Exploder.h"
#include "Game.h"
#include "Scene.h"
#include "Utils.h"
#include "ParticleSystemManager.h"
#include "LevelManager.h"

enum ExploderAnims 
{
	EXPLODER,
	BURNING_DEATH
};

void Exploder::initAnims(ShaderProgram &shaderProgram) 
{

	jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram, &Game::spriteSheets().lemmingAnimations, &Game::spriteSheets().rotatedLemmingAnimations);
	jobSprite->setNumberAnimations(2);

	// EXPLODER

	jobSprite->setAnimationSpeed(EXPLODER, 12);
	for (int i = 0; i < 16; i++) {
		jobSprite->addKeyframe(EXPLODER, glm::vec2(float(i) / 16, 10.0f / 14));
	}
		
	// BURNING_DEATH
	jobSprite->setAnimationSpeed(BURNING_DEATH, 12);
	for (int i = 0; i < 16; i++) {
		jobSprite->addKeyframe(BURNING_DEATH, glm::vec2(float(i) / 16, 13.0f / 14));
	}
		

	state = EXPLODER_STATE;
	jobSprite->changeAnimation(EXPLODER);

}

void Exploder::setWalkingRight(bool value)
{
	walkingRight = value;
}

void Exploder::updateStateMachine(int deltaTime) {

	switch (state) {
	case EXPLODER_STATE:
		if (jobSprite->isInLastFrame()) {
			state = BURNING_DEATH_STATE;
			jobSprite->changeAnimation(BURNING_DEATH);
		}
		break;
	case BURNING_DEATH_STATE:
		if (jobSprite->isInLastFrame()) {
			explode();
			isFinished = true;
			nextJob = NULL;
		}
		
		break;
	}
}

string Exploder::getName()
{
	return "BOMBER";
}

void Exploder::explode()
{
	glm::vec2 posBase = jobSprite->position();

	for (int i = 0; i < 16; ++i) {
		for (int j = 0; j < 22; ++j) {
			int offset;
			if (j >= 15) {
				offset = Utils::max(j - 17, 0);
			}
			else {
				offset = 15 - 2 * j;
			}
			if (i >= offset && i < 16-offset) {
				int x = posBase.x + i;
				int y = posBase.y + j;
				Scene::getInstance().eraseSpecialMask(x, y);
			}
		}
	}
	posBase += glm::ivec2(8, 15);

	ParticleSystemManager::getInstance().createNewParticleSystem(posBase);
}





