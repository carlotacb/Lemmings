#include "Particle.h"
#include "ShaderManager.h"
#include "Game.h"
#include <ctime>
#include <random>
#include <math.h>

#define PI 3.14159265359

Particle::Particle(ParticleColor color) 
{
	glm::vec2 coordTex;
	switch (color) {
		case PINK:
			coordTex = glm::vec2(0, 0);
			break;
		case BLUE:
			coordTex = glm::vec2(0.5, 0);
			break;
		case GREEN:
			coordTex = glm::vec2(0.25, 0);
			break;
		default:
			coordTex = glm::vec2(0, 0);
	}
	sprite = Sprite::createSprite(glm::ivec2(1, 1), glm::vec2(0.25, 1.), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().particleSprites);
	sprite->setNumberAnimations(1);
	sprite->addKeyframe(0, coordTex);
	sprite->changeAnimation(0);

	float angle = (rand() % 180) * PI / 180;
	speed = glm::vec2(2.5*cos(angle), -5 * sin(angle));
}

void Particle::setPosition(glm::vec2 positiona)
{
	position = positiona;
}

void Particle::update(int deltaTime)
{
	position += speed;
	sprite->position() = position;
	speed += glm::vec2(0, 0.25);
}

void Particle::render()
{
	glm::vec2 oldPosition = sprite->position();
	sprite->setPosition(sprite->position() - Level::currentLevel().getLevelAttributes()->cameraPos);
	sprite->render();
	sprite->setPosition(oldPosition);
}