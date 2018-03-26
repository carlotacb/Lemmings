#ifndef _DOORFACTORY_INCLUDE
#define _DOORFACTORY_INCLUDE

#include "Sprite.h"


class DoorFactory
{

public:

	static DoorFactory &instance()
	{
		static DoorFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Sprite *createFunDoor(ShaderProgram &shaderProgram);
	
};


#endif // _DOORFACTORY_INCLUDE

