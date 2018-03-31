#include <iostream>
#include "Game.h"
#include "NumFactory.h"





Sprite* NumFactory::createNum(int num)
{
	Sprite *numSprite = Sprite::createSprite(glm::ivec2(3, 8), glm::vec2(0.2, 0.5), &Scene::shaderProgram(), &Game::spriteSheets().numSprites);
	numSprite->setNumberAnimations(1);
	numSprite->addKeyframe(0, this->numPositions[num]);
	numSprite->changeAnimation(0);

	return numSprite;
}

