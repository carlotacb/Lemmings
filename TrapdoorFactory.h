#ifndef _TRAPDOORFACTORY_INCLUDE
#define _TRAPDOORFACTORY_INCLUDE

#include "Sprite.h"
#include "Trapdoor.h"

class TrapdoorFactory
{

public:

	static TrapdoorFactory &instance()
	{
		static TrapdoorFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Trapdoor *createTrapdoor(string type);
	
};


#endif // _TRAPDOORFACTORY_INCLUDE

