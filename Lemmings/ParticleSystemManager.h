#ifndef _PARTICLESYSTEMMANAGER_INCLUDE
#define _PARTICLESYSTEMMANAGER_INCLUDE


#include "ParticleSystem.h"


class ParticleSystemManager 
{
public:
	static ParticleSystemManager &getInstance()
	{
		static ParticleSystemManager instance; // Guaranteed to be destroyed.
									// Instantiated on first use.
		return instance;
	};

	void init();
	void createNewParticleSystem(glm::vec2 position);
	void update(int deltaTime);
	void render();


private:
	vector<ParticleSystem*> particleSystems;
};


#endif // _PARTICLESYSTEMMANAGER_INCLUDE


