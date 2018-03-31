#include <iostream>
#include "TrapdoorFactory.h"
#include "Game.h"




Sprite* TrapdoorFactory::createFunTrapdoor()
{
	Sprite *funTrapdoor = Sprite::createSprite(glm::vec2(41, 25), glm::vec2(1.f / 2, 1.f / 10), &Scene::shaderProgram(), &Game::spriteSheets().trapdoorSprites);

	funTrapdoor->setNumberAnimations(1);

	funTrapdoor->setAnimationSpeed(0, 12);
	for (int i = 0; i < 10; i++) {
		funTrapdoor->addKeyframe(0, glm::vec2(0, float(i)/10));
	}
	funTrapdoor->changeAnimation(0);

	return funTrapdoor;
}
