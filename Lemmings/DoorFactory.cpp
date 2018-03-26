#include <iostream>
#include "DoorFactory.h"
#include "Game.h"




Sprite* DoorFactory::createFunDoor(ShaderProgram &shaderProgram)
{
	Sprite *funDoor = Sprite::createSprite(glm::vec2(41, 32), glm::vec2(1.f / 3, 1.f / 8), &shaderProgram, &Game::spriteSheets().doorSprites);

	funDoor->setNumberAnimations(1);

	funDoor->setAnimationSpeed(0, 12);
	for (int i = 0; i < 6; i++) {
		funDoor->addKeyframe(0, glm::vec2(float(i%3) / 3, i/3));
	}
	funDoor->changeAnimation(0);

	return funDoor;
}
