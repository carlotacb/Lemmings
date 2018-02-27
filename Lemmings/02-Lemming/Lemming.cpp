#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Lemming.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum LemmingAnims
{
	WALKING_LEFT, WALKING_RIGHT
};


void Lemming::init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/lemming.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(48, 48), glm::vec2(0.125, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);
	
		sprite->setAnimationSpeed(WALKING_RIGHT, 8);
		for(int i=0; i<8; i++)
			sprite->addKeyframe(WALKING_RIGHT, glm::vec2(float(i) / 8, 0.0f));
		
		sprite->setAnimationSpeed(WALKING_LEFT, 8);
		for(int i=0; i<8; i++)
			sprite->addKeyframe(WALKING_LEFT, glm::vec2(float(i) / 8, 0.5f));
		
	sprite->changeAnimation(WALKING_RIGHT);
	sprite->setPosition(initialPosition);
}

void Lemming::update(int deltaTime)
{
	int state = sprite->animation();

	sprite->update(deltaTime);

	if(collisionFloor(1) == 0)
	{
		if(state == WALKING_LEFT)
		{
			sprite->position() += glm::vec2(-3, -3);
			if(collision())
			{
				sprite->position() -= glm::vec2(-3, -3);
				sprite->changeAnimation(WALKING_RIGHT);
			}
		}
		else if(state == WALKING_RIGHT)
		{
			sprite->position() += glm::vec2(3, -3);
			if(collision())
			{
				sprite->position() -= glm::vec2(3, -3);
				sprite->changeAnimation(WALKING_LEFT);
			}
		}
	}
	
	int fall = collisionFloor(1);
	if(fall > 0)
	{
		// Fall
		sprite->position() += glm::vec2(0, 3);
	}
}

void Lemming::render()
{
	sprite->render();
}

void Lemming::setMapMask(VariableTexture *mapMask)
{
	mask = mapMask;
}

int Lemming::collisionFloor(int maxFall)
{
	bool bContact = false;
	int fall = 0;
	glm::ivec2 posBase = sprite->position() / 3.f + glm::vec2(120, 0);
	
	posBase += glm::ivec2(7, 16);
	while((fall <= maxFall) && !bContact)
	{
		if((mask->pixel(posBase.x, posBase.y) == 0) && (mask->pixel(posBase.x+1, posBase.y) == 0))
			fall += 1;
		else
			bContact = true;
	}

	return fall;
}

bool Lemming::collision()
{
	glm::ivec2 posBase = sprite->position() / 3.f + glm::vec2(120, 0);
	
	posBase += glm::ivec2(7, 15);
	if((mask->pixel(posBase.x, posBase.y) == 0) && (mask->pixel(posBase.x+1, posBase.y) == 0))
		return false;

	return true;
}







