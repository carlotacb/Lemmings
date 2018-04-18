#include "Game.h"
#include "PurpleNumFactory.h"
#include "ShaderManager.h"

Sprite* PurpleNumFactory::createNum()
{
	Sprite *numSprite = Sprite::createSprite(glm::ivec2(6, 9), glm::vec2(18./128, 24./64), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().purpleNumSprites);
	numSprite->setNumberAnimations(11);
	for (int i = 0; i < 11; ++i) {
		numSprite->addKeyframe(i, this->numPositions[i]);
	}
	numSprite->changeAnimation(10);

	return numSprite;
}

Sprite* PurpleNumFactory::createSymbol(char symbol)
{
	Sprite *numSprite = Sprite::createSprite(glm::ivec2(6, 9), glm::vec2(18. / 128, 24. / 64), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().purpleNumSprites);
	numSprite->setNumberAnimations(1);

	if (symbol == '%') {
		numSprite->addKeyframe(0, glm::vec2(72. / 128, 24. / 64));
		numSprite->changeAnimation(0);
	}
	else {
		delete numSprite;
	}


	return numSprite;
}
