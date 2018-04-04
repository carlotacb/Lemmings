#include "Exploder.h"
#include "Game.h"
#include "Scene.h"


enum ExploderAnims 
{
	EXPLODER
};

void Exploder::initAnims(ShaderProgram &shaderProgram) 
{

	jobSprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &shaderProgram, &Game::spriteSheets().lemmingAnimations, &Game::spriteSheets().rotatedLemmingAnimations);
	jobSprite->setNumberAnimations(1);

	// EXPLODER

	jobSprite->setAnimationSpeed(EXPLODER, 12);
	for (int i = 0; i<16; i++)
		jobSprite->addKeyframe(EXPLODER, glm::vec2(float(i) / 16, 10.0f / 14));

	state = EXPLODER_STATE;
	jobSprite->changeAnimation(EXPLODER);

}

void Exploder::updateStateMachine(int deltaTime) {

	switch (state) {
	case EXPLODER_STATE:
		if (jobSprite->isInLastFrame()) {
			isFinished = true;
			nextJob = NULL;
		}
	}
}







