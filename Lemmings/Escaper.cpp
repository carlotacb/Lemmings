#include "Escaper.h"
#include "Game.h"
#include "Scene.h"


enum EscaperAnims
{
	ESCAPING
};

void Escaper::initAnims(ShaderProgram &shaderProgram) {
	jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram, &Game::spriteSheets().lemmingAnimations, &Game::spriteSheets().rotatedLemmingAnimations);
	jobSprite->setNumberAnimations(1);

	// ESCAPING
	jobSprite->setAnimationSpeed(ESCAPING, 12);
	for (int i = 0; i<7; i++)
		jobSprite->addKeyframe(ESCAPING, glm::vec2(float(i + 1) / 16, 1.0f / 14));

	state = ESCAPING_STATE;
	jobSprite->changeAnimation(ESCAPING);
}

void Escaper::updateStateMachine(int deltaTime) {

	switch (state)
	{
	case ESCAPING_STATE:
		if (jobSprite->isInLastFrame()) {
			isFinished = true;
			nextJob = NULL;
		}
	}
}
