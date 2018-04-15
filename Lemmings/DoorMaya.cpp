#include <iostream>
#include "DoorMaya.h"
#include "Game.h"


void DoorMaya::init() {
	doorSprite = Sprite::createSprite(glm::vec2(41, 32), glm::vec2(1.f / 3, 1.f / 8), &Scene::shaderProgram(), &Game::spriteSheets().doorSprites);

	escapeOffset = glm::vec2(13, 16);

	doorSprite->setNumberAnimations(1);

	doorSprite->setAnimationSpeed(0, 12);
	for (int i = 2; i < 8; i++) {
		doorSprite->addKeyframe(0, glm::vec2(1.f/3, i / 8));
	}
	doorSprite->changeAnimation(0);
}
