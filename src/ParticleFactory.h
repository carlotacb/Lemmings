#ifndef _PARTICLEFACTORY_INCLUDE
#define _PARTICLEFACTORY_INCLUDE

#include "Particle.h"


class ParticleFactory
{

public:

	static ParticleFactory &getInstance()
	{
		static ParticleFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Particle *createParticle();

};


#endif // _PARTICLEFACTORY_INCLUDE

