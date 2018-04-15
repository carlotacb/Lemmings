#include <iostream>
#include "DoorStandard.h"
#include "Game.h"


void DoorStandard::init() {
	doorSprite = Sprite::createSprite(glm::vec2(41, 32), glm::vec2(1.f / 3, 1.f / 8), &Scene::shaderProgram(), &Game::spriteSheets().doorSprites);

	escapeOffset = glm::vec2(13,16);

	doorSprite->setNumberAnimations(1);

	doorSprite->setAnimationSpeed(0, 12);
	for (int i = 0; i < 6; i++) {
		doorSprite->addKeyframe(0, glm::vec2(float(i % 3) / 3, float(i / 3)/8));
	}
	doorSprite->changeAnimation(0);
}
