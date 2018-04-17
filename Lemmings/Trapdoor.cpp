#include <iostream>
#include "Trapdoor.h"
#include "Game.h"


void Trapdoor::update(int deltaTime)
{
	if (trapdoorSprite->isInLastFrame()) {
		trapdoorSprite->setAnimationSpeed(0, 0);
		opened = true;
	}
	trapdoorSprite->update(deltaTime);
}

void Trapdoor::render()
{
	trapdoorSprite->render();
}

bool Trapdoor::isOpened()
{
	return opened;
}

void Trapdoor::setPosition(glm::vec2 position)
{
	trapdoorSprite->setPosition(position);
}


glm::vec2 Trapdoor::getPosition()
{
	return trapdoorSprite->position();
}

glm::vec2 Trapdoor::getEnterPosition()
{
	return trapdoorSprite->position() + enterOffset;
}