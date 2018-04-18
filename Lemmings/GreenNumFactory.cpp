#include "Game.h"
#include "GreenNumFactory.h"
#include "ShaderManager.h"

Sprite* GreenNumFactory::createNum()
{
	Sprite *numSprite = Sprite::createSprite(glm::ivec2(7, 10), glm::vec2(38./256, 81./512), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().greenNumSprites);
	numSprite->setNumberAnimations(11);
	for (int i = 0; i < 11; ++i) {
		numSprite->addKeyframe(i, this->numPositions[i]);
	}
	numSprite->changeAnimation(10);

	return numSprite;
}

Sprite* GreenNumFactory::createSymbol(char symbol)
{
	Sprite *numSprite = Sprite::createSprite(glm::ivec2(7, 10), glm::vec2(38. / 256, 81. / 512), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().greenNumSprites);
	numSprite->setNumberAnimations(1);

	if (symbol == '-') {
		numSprite->addKeyframe(0, glm::vec2(0.5, 0.5));
		numSprite->changeAnimation(0);
	}
	else if (symbol == '%') {
		numSprite->addKeyframe(0, glm::vec2(0.75,0.5));
		numSprite->changeAnimation(0);
	}
	else {
		delete numSprite;
	}


	return numSprite;
}
