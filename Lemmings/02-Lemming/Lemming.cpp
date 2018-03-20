#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Lemming.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
/*
enum LemmingAnims
{
	WALKING_LEFT, WALKING_RIGHT,
	FALLING_RIGHT, FALLING_LEFT,
	FLOATER_OPENING_RIGHT, FLOATER_OPENING_LEFT, FLOATER_FALLING_RIGHT, FLOATER_FALLING_LEFT,
	BLOCKER,
	CLIMBER_CLIMBLING_RIGHT, CLIMBER_CLIMBLING_LEFT, CLIMBER_LEDGING_RIGHT, CLIMBER_LEDGING_LEFT,
	BUILDER_RIGHT, BUILDER_LEFT,
	BASHER_RIGHT, BASHER_LEFT,
	DIGGER,
	MINER_RIGHT, MINER_LEFT,
	EXPLODER,
	FALLING_DEATH,
	DROWNING_DEATH,
	BURNING_DEATH,
	ESCAPING
};
*/
enum LemmingAnims
{
	WALKING_LEFT, WALKING_RIGHT,
	FALLING_RIGHT, FALLING_LEFT,
	FALLING_DEATH,
	DROWNING_DEATH,
	BURNING_DEATH,
	ESCAPING
};


void Lemming::init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram)
{
	initAnims(shaderProgram);
	sprite->setPosition(initialPosition);
}

void Lemming::update(int deltaTime)
{
	if(sprite->update(deltaTime) == 0)
		return;

	updateStateMachine();
}

void Lemming::render()
{
	sprite->render();
}

void Lemming::setMapMask(VariableTexture *mapMask)
{
	mask = mapMask;
}
/*
void Lemming::initAnims(ShaderProgram &shaderProgram) {
	spritesheet.loadFromFile("images/lemming_anim.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f / 16, 1.f / 14), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);
	
	// WALKING
	sprite->setAnimationSpeed(WALKING_RIGHT, 12);
	for (int i = 0; i<8; i++)
		sprite->addKeyframe(WALKING_RIGHT, glm::vec2(float(i) / 16, 0.0f));

	sprite->setAnimationSpeed(WALKING_LEFT, 12);
	for (int i = 0; i<8; i++)
		sprite->addKeyframe(WALKING_LEFT, glm::vec2(float(i) / 16, 0.0f));

	// FALLING
	sprite->setAnimationSpeed(FALLING_RIGHT, 12);
	for (int i = 0; i<4; i++)
		sprite->addKeyframe(FALLING_RIGHT, glm::vec2(float(i) / 16, 2.0f / 14));

	sprite->setAnimationSpeed(FALLING_LEFT, 12);
	for (int i = 0; i<4; i++)
		sprite->addKeyframe(FALLING_LEFT, glm::vec2(float(i) / 16, 2.0f / 14));

	// FLOATER 

	sprite->setAnimationSpeed(FLOATER_OPENING_RIGHT, 12);
	for (int i = 0; i<4; i++)
		sprite->addKeyframe(FLOATER_OPENING_RIGHT, glm::vec2(float(i + 4) / 16, 2.0f / 14));

	sprite->setAnimationSpeed(FLOATER_OPENING_LEFT, 12);
	for (int i = 0; i<4; i++)
		sprite->addKeyframe(FLOATER_OPENING_LEFT, glm::vec2(float(i + 4) / 16, 2.0f / 14));

	sprite->setAnimationSpeed(FLOATER_FALLING_RIGHT, 12);
	for (int i = 0; i<4; i++)
		sprite->addKeyframe(FLOATER_FALLING_RIGHT, glm::vec2(float(i + 4) / 16, 2.0f / 14));

	sprite->setAnimationSpeed(FLOATER_FALLING_LEFT, 12);
	for (int i = 0; i<4; i++)
		sprite->addKeyframe(FLOATER_FALLING_LEFT, glm::vec2(float(i + 4) / 16, 2.0f / 14));

	// BLOCKER 
	sprite->setAnimationSpeed(BLOCKER, 12);
	for (int i = 0; i<16; i++)
		sprite->addKeyframe(BLOCKER, glm::vec2(float(i) / 16, 3.0f / 14));

	// CLIMBER 
	sprite->setAnimationSpeed(CLIMBER_CLIMBLING_RIGHT, 12);
	for (int i = 0; i<8; i++)
		sprite->addKeyframe(CLIMBER_CLIMBLING_RIGHT, glm::vec2(float(i) / 16, 4.0f / 14));

	sprite->setAnimationSpeed(CLIMBER_CLIMBLING_LEFT, 12);
	for (int i = 0; i<8; i++)
		sprite->addKeyframe(CLIMBER_CLIMBLING_LEFT, glm::vec2(float(i) / 16, 4.0f / 14));

	sprite->setAnimationSpeed(CLIMBER_LEDGING_RIGHT, 12);
	for (int i = 0; i<8; i++)
		sprite->addKeyframe(CLIMBER_LEDGING_RIGHT, glm::vec2((float(i) + 8) / 16, 4.0f / 14));

	sprite->setAnimationSpeed(CLIMBER_LEDGING_LEFT, 12);
	for (int i = 0; i<8; i++)
		sprite->addKeyframe(CLIMBER_LEDGING_LEFT, glm::vec2((float(i) + 8) / 16, 4.0f / 14));

	// BUILDER 
	sprite->setAnimationSpeed(BUILDER_RIGHT, 12);
	for (int i = 0; i<16; i++)
		sprite->addKeyframe(BUILDER_RIGHT, glm::vec2(float(i) / 16, 5.0f / 14));

	sprite->setAnimationSpeed(BUILDER_LEFT, 12);
	for (int i = 0; i<16; i++)
		sprite->addKeyframe(BUILDER_LEFT, glm::vec2(float(i) / 16, 5.0f / 14));

	// BASHER
	sprite->setAnimationSpeed(BASHER_RIGHT, 12);
	for (int i = 0; i<32; i++)
		sprite->addKeyframe(BASHER_RIGHT, glm::vec2(float(i % 16) / 16, (6.0f + i / 16) / 14));

	sprite->setAnimationSpeed(BASHER_LEFT, 12);
	for (int i = 0; i<32; i++)
		sprite->addKeyframe(BASHER_LEFT, glm::vec2(float(i % 16) / 16, (6.0f + i / 16) / 14));

	// DIGGER
	sprite->setAnimationSpeed(DIGGER, 12);
	for (int i = 0; i<8; i++)
		sprite->addKeyframe(DIGGER, glm::vec2(float(i) / 16, 8.0f / 14));

	// MINER
	sprite->setAnimationSpeed(MINER_RIGHT, 12);
	for (int i = 0; i<24; i++)
	if (i < 8) {
		sprite->addKeyframe(MINER_RIGHT, glm::vec2(float(i + 8) / 16, 8.0f / 14));
	}
	else {
		sprite->addKeyframe(MINER_RIGHT, glm::vec2(float(i) / 16, 9.0f / 14));
	}

	sprite->setAnimationSpeed(MINER_LEFT, 12);
	for (int i = 0; i<24; i++)
	if (i < 8) {
		sprite->addKeyframe(MINER_LEFT, glm::vec2(float(i + 8) / 16, 8.0f / 14));
	}
	else {
		sprite->addKeyframe(MINER_LEFT, glm::vec2(float(i) / 16, 9.0f / 14));
	}

	// EXPLODER
	sprite->setAnimationSpeed(EXPLODER, 12);
	for (int i = 0; i<16; i++)
		sprite->addKeyframe(EXPLODER, glm::vec2(float(i) / 16, 10.0f / 14));

	// FALLING_DEATH
	sprite->setAnimationSpeed(FALLING_DEATH, 12);
	for (int i = 0; i<16; i++)
		sprite->addKeyframe(FALLING_DEATH, glm::vec2(float(i) / 16, 11.0f / 14));

	// DROWNING_DEATH
	sprite->setAnimationSpeed(DROWNING_DEATH, 12);
	for (int i = 0; i<16; i++)
		sprite->addKeyframe(DROWNING_DEATH, glm::vec2(float(i) / 16, 12.0f / 14));

	// BURNING_DEATH
	sprite->setAnimationSpeed(BURNING_DEATH, 12);
	for (int i = 0; i<16; i++)
		sprite->addKeyframe(BURNING_DEATH, glm::vec2(float(i) / 16, 13.0f / 14));

	// ESCAPING
	sprite->setAnimationSpeed(ESCAPING, 12);
	for (int i = 0; i<7; i++)
		sprite->addKeyframe(ESCAPING, glm::vec2(float(i + 1) / 16, 1.0f / 14));

	state = FALLING_RIGHT_STATE;
	sprite->changeAnimation(FALLING_RIGHT);
	

	// WALKING
	sprite->setAnimationSpeed(WALKING_RIGHT, 12);
	for (int i = 0; i<8; i++)
	sprite->addKeyframe(WALKING_RIGHT, glm::vec2(float(i) / 16, 0.0f));

	sprite->setAnimationSpeed(WALKING_LEFT, 12);
	for (int i = 0; i<8; i++)
	sprite->addKeyframe(WALKING_LEFT, glm::vec2(float(i) / 16, 0.0f));

	// FALLING
	sprite->setAnimationSpeed(FALLING_RIGHT, 12);
	for (int i = 0; i<4; i++)
	sprite->addKeyframe(FALLING_RIGHT, glm::vec2(float(i) / 16, 2.0f / 14));

	sprite->setAnimationSpeed(FALLING_LEFT, 12);
	for (int i = 0; i<4; i++)
	sprite->addKeyframe(FALLING_LEFT, glm::vec2(float(i) / 16, 2.0f / 14));

	// FALLING_DEATH
	sprite->setAnimationSpeed(FALLING_DEATH, 12);
	for (int i = 0; i<16; i++)
	sprite->addKeyframe(FALLING_DEATH, glm::vec2(float(i) / 16, 11.0f / 14));

	// DROWNING_DEATH
	sprite->setAnimationSpeed(DROWNING_DEATH, 12);
	for (int i = 0; i<16; i++)
	sprite->addKeyframe(DROWNING_DEATH, glm::vec2(float(i) / 16, 12.0f / 14));

	// BURNING_DEATH
	sprite->setAnimationSpeed(BURNING_DEATH, 12);
	for (int i = 0; i<16; i++)
	sprite->addKeyframe(BURNING_DEATH, glm::vec2(float(i) / 16, 13.0f / 14));

	// ESCAPING
	sprite->setAnimationSpeed(ESCAPING, 12);
	for (int i = 0; i<7; i++)
	sprite->addKeyframe(ESCAPING, glm::vec2(float(i + 1) / 16, 1.0f / 14));

	state = FALLING_RIGHT_STATE;
	sprite->changeAnimation(FALLING_RIGHT);

}

void Lemming::updateStateMachine() {
	int fall;

	switch (state)
	{
	case FALLING_LEFT_STATE:
		fall = collisionFloor(2);
		if (fall > 0)
			sprite->position() += glm::vec2(0, fall);
		else {
			sprite->changeAnimation(WALKING_LEFT);
			state = WALKING_LEFT_STATE;
		}
		break;
	case FALLING_RIGHT_STATE:
		fall = collisionFloor(2);
		if (fall > 0)
			sprite->position() += glm::vec2(0, fall);
		else {
			sprite->changeAnimation(WALKING_RIGHT);
			state = WALKING_RIGHT_STATE;
		}
		break;
	case WALKING_LEFT_STATE:
		sprite->position() += glm::vec2(-1, -1);

		if (collision())
		{
			sprite->position() -= glm::vec2(-1, -1);
			sprite->changeAnimation(WALKING_RIGHT);
			state = WALKING_RIGHT_STATE;
		}
		else
		{
			fall = collisionFloor(3);
			if (fall > 0)
				sprite->position() += glm::vec2(0, 1);
			if (fall > 1)
				sprite->position() += glm::vec2(0, 1);
			if (fall > 2) {
				sprite->changeAnimation(FALLING_LEFT);
				state = FALLING_LEFT_STATE;
			}
		}
		break;
	case WALKING_RIGHT_STATE:
		sprite->position() += glm::vec2(1, -1);

		if (collision())
		{
			sprite->position() -= glm::vec2(1, -1);
			sprite->changeAnimation(WALKING_LEFT);
			state = WALKING_LEFT_STATE;
		}
		else
		{
			fall = collisionFloor(3);
			if (fall < 3)
				sprite->position() += glm::vec2(0, fall);
			else {
				sprite->changeAnimation(FALLING_RIGHT);
				state = FALLING_RIGHT_STATE;
			}

		}
		break;
	}
}

int Lemming::collisionFloor(int maxFall)
{
	bool bContact = false;
	int fall = 0;
	glm::ivec2 posBase = sprite->position() + glm::vec2(120, 0); // Add the map displacement
	
	posBase += glm::ivec2(7, 16);
	while((fall < maxFall) && !bContact)
	{
		if((mask->pixel(posBase.x, posBase.y+fall) == 0) && (mask->pixel(posBase.x+1, posBase.y+fall) == 0))
			fall += 1;
		else
			bContact = true;
	}

	return fall;
}

bool Lemming::collision()
{
	glm::ivec2 posBase = sprite->position() + glm::vec2(120, 0); // Add the map displacement
	
	posBase += glm::ivec2(7, 15);
	if((mask->pixel(posBase.x, posBase.y) == 0) && (mask->pixel(posBase.x+1, posBase.y) == 0))
		return false;

	return true;
}

*/





