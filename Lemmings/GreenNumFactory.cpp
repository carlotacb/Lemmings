#include "Game.h"
#include "GreenNumFactory.h"

Sprite* GreenNumFactory::createNum(int num)
{
	Sprite *numSprite = Sprite::createSprite(glm::ivec2(7, 10), glm::vec2(38./256, 81./512), &Scene::shaderProgram(), &Game::spriteSheets().greenNumSprites);
	numSprite->setNumberAnimations(1);
	numSprite->addKeyframe(0, this->numPositions[num]);
	numSprite->changeAnimation(0);

	return numSprite;
}

Sprite* GreenNumFactory::createSymbol(char symbol)
{
	Sprite *numSprite = Sprite::createSprite(glm::ivec2(7, 10), glm::vec2(38. / 256, 81. / 512), &Scene::shaderProgram(), &Game::spriteSheets().greenNumSprites);
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
