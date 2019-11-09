#include "ParticleFactory.h"
#include <ctime>
#include <random>

Particle* ParticleFactory::createParticle()
{

	int color = rand() % 3;

	switch (color) {
		case 0:
			return new Particle(Particle::ParticleColor::BLUE);
		case 1:
			return new Particle(Particle::ParticleColor::GREEN);

		case 2:
			return new Particle(Particle::ParticleColor::PINK);

		default:
			return NULL;
	}
}

