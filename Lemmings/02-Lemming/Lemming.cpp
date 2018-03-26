#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Lemming.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


void Lemming::init(Job *job, const glm::vec2 &initialPosition, ShaderProgram &shaderProgram)
{
	this->shaderProgram = &shaderProgram;
	this->job = job;
	this->job->initAnims(shaderProgram);
	sprite = this->job->getJobSprite();
	sprite->setPosition(initialPosition);
}

void Lemming::update(int deltaTime)
{
	if (sprite->update(deltaTime) == 0)
		return;

	job->updateStateMachine(deltaTime);

	if (job->finished()) {
		changeJob(job->getNextJob());
	}
}

void Lemming::render()
{
	sprite->render();
}

void Lemming::changeJob(Job *nextJob)
{
	delete this->job;
	this->job = nextJob;
	this->job->initAnims(*shaderProgram);

	glm::ivec2 oldPosition = sprite->position();
	sprite = this->job->getJobSprite();
	sprite->setPosition(oldPosition);
}