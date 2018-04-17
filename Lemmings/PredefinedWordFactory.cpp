#include "PredefinedWordFactory.h"
#include "Game.h"
#include "Scene.h"
#include "Sprite.h"

Sprite* PredefinedWordFactory::createJobWord(string jobName)
{
	Sprite *jobNameSprite = Sprite::createSprite(glm::ivec2(60, 10), glm::vec2(297. / 512, 81. / 1024), &Scene::shaderProgram(), &Game::spriteSheets().jobNamesSprites);
	jobNameSprite->setNumberAnimations(1);

	glm::vec2 textureCoord;

	if (jobName == "WALKER") {
		textureCoord = glm::vec2(0, 0);
	}
	else if (jobName == "MINER") {
		textureCoord = glm::vec2(0, 81. / 1024);
	}
	else if (jobName == "FLOATER") {
		textureCoord = glm::vec2(0, 162. / 1024);

	}
	else if (jobName == "FALLER") {
		textureCoord = glm::vec2(0, 243. / 1024);

	}
	else if (jobName == "DIGGER") {
		textureCoord = glm::vec2(0, 324. / 1024);

	}
	else if (jobName == "CLIMBER") {
		textureCoord = glm::vec2(0, 405. / 1024);

	}
	else if (jobName == "BUILDER") {
		textureCoord = glm::vec2(0, 486. / 1024);

	}
	else if (jobName == "BASHER") {
		textureCoord = glm::vec2(0, 567. / 1024);

	}

	jobNameSprite->addKeyframe(0, textureCoord);
	jobNameSprite->changeAnimation(0);

	return jobNameSprite;
}

Sprite* PredefinedWordFactory::createInfoWord(string infoName)
{
	Sprite *infoWordSprite = Sprite::createSprite(glm::ivec2(30, 10), glm::vec2(168. / 512, 81. / 256), &Scene::shaderProgram(), &Game::spriteSheets().infoWordSprites);
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
