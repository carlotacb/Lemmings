#include "ParticleSystem.h"
#include "ParticleFactory.h"
#include <ctime>
#include <random>

ParticleSystem::ParticleSystem()
{
	alive = true;

	numParticles = rand() % 16 + 10;
	particles.resize(numParticles);

	for (int i = 0; i < numParticles; ++i) {
		particles[i] = ParticleFactory::getInstance().createParticle();
	}
}

void ParticleSystem::setPosition(glm::vec2 position)
{
	for (int i = 0; i < numParticles; ++i) {
		particles[i]->setPosition(position);
	}
}


void ParticleSystem::update(int deltaTime)
{
	currentTime += deltaTime;
	if (currentTime / 1000 > 5) {
		alive = false;
	}
	else {
		for (int i = 0; i < numParticles; ++i) {
			particles[i]->update(deltaTime);
		}
	}
	
}

void ParticleSystem::render()
{
	for (int i = 0; i < numParticles; ++i) {
		particles[i]->render();
	}
}

bool ParticleSystem::notFinished()
{
	return alive;
}
