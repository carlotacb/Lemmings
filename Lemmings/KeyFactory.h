#ifndef _KEYFACTORY_INCLUDE
#define _KEYFACTORY_INCLUDE

#include "Sprite.h"


class KeyFactory
{

public:

	static KeyFactory &instance()
	{
		static KeyFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Sprite *createLeftKey(glm::ivec2 size = glm::ivec2(31, 18));
	Sprite *createRightKey(glm::ivec2 size = glm::ivec2(31, 18));
	Sprite *createEscapeKey(glm::ivec2 size = glm::ivec2(31, 18));

};


#endif // _KEYFACTORY_INCLUDE

