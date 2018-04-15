#include <iostream>
#include "Door.h"
#include "Game.h"


void Door::update(int deltaTime) 
{
	doorSprite->update(deltaTime);
}

void Door::render() 
{
	doorSprite->render();
}

void Door::setPosition(glm::vec2 position)
{
	doorSprite->setPosition(position);
}


glm::vec2 Door::getPosition() 
{
	return doorSprite->position();
}

glm::vec2 Door::getEscapePosition()
{
	return doorSprite->position() + escapeOffset;
}