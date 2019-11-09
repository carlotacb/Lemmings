#include "PredefinedWordFactory.h"
#include "Game.h"
#include "Scene.h"
#include "Sprite.h"
#include "ShaderManager.h"

Sprite* PredefinedWordFactory::createJobWord()
{
	Sprite *jobNameSprite = Sprite::createSprite(glm::ivec2(60, 10), glm::vec2(297. / 512, 81. / 1024), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().jobNamesSprites);
	jobNameSprite->setNumberAnimations(10);

	jobNameSprite->addKeyframe(WALKER, glm::vec2(0, 0));
	jobNameSprite->addKeyframe(MINER, glm::vec2(0, 81. / 1024));
	jobNameSprite->addKeyframe(FLOATER, glm::vec2(0, 162. / 1024));
	jobNameSprite->addKeyframe(FALLER, glm::vec2(0, 243. / 1024));
	jobNameSprite->addKeyframe(DIGGER, glm::vec2(0, 324. / 1024));
	jobNameSprite->addKeyframe(CLIMBER, glm::vec2(0, 405. / 1024));
	jobNameSprite->addKeyframe(BUILDER, glm::vec2(0, 486. / 1024));
	jobNameSprite->addKeyframe(BLOCKER, glm::vec2(0, 567. / 1024));
	jobNameSprite->addKeyframe(BASHER, glm::vec2(0, 648. / 1024));
	jobNameSprite->addKeyframe(NONE, glm::vec2(0, 0.75));

	jobNameSprite->changeAnimation(NONE);

	return jobNameSprite;
}

Sprite* PredefinedWordFactory::createInfoWord(string infoName)
{
	Sprite *infoWordSprite = Sprite::createSprite(glm::ivec2(30, 10), glm::vec2(168. / 512, 81. / 256), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().infoWordSprites);
	infoWordSprite->setNumberAnimations(1);

	glm::vec2 textureCoord;

	if (infoName == "IN") {
		textureCoord = glm::vec2(0, 0);
	}
	else if (infoName == "OUT") {
		textureCoord = glm::vec2(0.5, 0);
	}
	else if (infoName == "TIME") {
		textureCoord = glm::vec2(0, 0.5);

	}

	infoWordSprite->addKeyframe(0, textureCoord);
	infoWordSprite->changeAnimation(0);

	return infoWordSprite;
}
