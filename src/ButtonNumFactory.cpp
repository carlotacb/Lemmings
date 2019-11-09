#include "Game.h"
#include "ButtonNumFactory.h"
#include "ShaderManager.h"

Sprite* ButtonNumFactory::createNum()
{
	Sprite *numSprite = Sprite::createSprite(glm::ivec2(3, 8), glm::vec2(3.f/16, 0.25), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().numSprites);
	numSprite->setNumberAnimations(11);
	for (int i = 0; i < 11; ++i) {
		numSprite->addKeyframe(i, this->numPositions[i]);
	}
	numSprite->changeAnimation(10);

	return numSprite;
}

