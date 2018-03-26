#ifndef _TRAPDOORFACTORY_INCLUDE
#define _TRAPDOORFACTORY_INCLUDE

#include "Sprite.h"


class TrapdoorFactory
{

public:

	static TrapdoorFactory &instance()
	{
		static TrapdoorFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Sprite *createFunTrapdoor(ShaderProgram &shaderProgram);
	
};


#endif // _TRAPDOORFACTORY_INCLUDE

