#include <iostream>
#include "Game.h"
#include "Scene.h"
#include "ButtonFactory.h"
#include "Sprite.h"





Button ButtonFactory::createButton(int buttonName) {
	Button button = Button();
	button.init();

	Sprite *buttonSprite = Sprite::createSprite(glm::ivec2(15, 23), glm::vec2(1./6, 0.5), &Scene::shaderProgram(), &Game::spriteSheets().buttonSprites);
	buttonSprite->setNumberAnimations(1);

	glm::vec2 textureCoord;

	switch (buttonName)
	{
	case Button::MINUS_BUTTON:
		textureCoord = glm::vec2(0,0);
		break;
	case Button::PLUS_BUTTON:
		textureCoord = glm::vec2(1./6, 0);
		break;
	case Button::CLIMBER_BUTTON:
		textureCoord = glm::vec2(2. / 6, 0.5);
		break;
	case Button::FLOATER_BUTTON:
		textureCoord = glm::vec2(4. / 6, 0.5);
		break;
	case Button::EXPLODER_BUTTON:
		textureCoord = glm::vec2(4. / 6, 0);
		break;
	case Button::BLOCKER_BUTTON:
		textureCoord = glm::vec2(5. / 6, 0);
		break;
	case Button::BUILDER_BUTTON:
		textureCoord = glm::vec2(1. / 6, 0.5);
		break;
	case Button::BASHER_BUTTON:
		textureCoord = glm::vec2(0, 0.5);
		break;
	case Button::MINER_BUTTON:
		textureCoord = glm::vec2(5. / 6, 0.5);
		break;
	case Button::DIGGER_BUTTON:
		textureCoord = glm::vec2(3. / 6, 0.5);
		break;
	case Button::PAUSE_BUTTON:
		textureCoord = glm::vec2(2. / 6, 0);
		break;
	case Button::NUKE_BUTTON:
		textureCoord = glm::vec2(3. / 6, 0);
		break;
	default:
		break;
	}

	buttonSprite->addKeyframe(0, textureCoord);
	buttonSprite->changeAnimation(0);

	button.setSprite(buttonSprite);

	return button;
}

