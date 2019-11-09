#include <iostream>
#include "ShaderManager.h"
#include "TrapdoorHell.h"
#include "Game.h"


void TrapdoorHell::init() {
	trapdoorSprite = Sprite::createSprite(glm::vec2(41, 25), glm::vec2(1.f / 2, 1.f / 10), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().trapdoorSprites);

	enterOffset = glm::vec2(13, 0);

	trapdoorSprite->setNumberAnimations(1);

	trapdoorSprite->setAnimationSpeed(0, 12);
	for (int i = 0; i < 10; i++) {
		trapdoorSprite->addKeyframe(0, glm::vec2(0.5, float(i) / 10));
	}
	trapdoorSprite->changeAnimation(0);
}
