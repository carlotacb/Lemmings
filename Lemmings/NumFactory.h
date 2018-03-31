#ifndef _NUMFACTORY_INCLUDE
#define _NUMFACTORY_INCLUDE

#include <glm/glm.hpp>
#include "Sprite.h"



class NumFactory
{

public:

	static NumFactory &instance()
	{
		static NumFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Sprite *createNum(int num);

private:
	glm::vec2 numPositions[10] = {
		glm::vec2(0,0),
		glm::vec2(0.2, 0),
		glm::vec2(0.4, 0),
		glm::vec2(0.6, 0),
		glm::vec2(0.8, 0),
		glm::vec2(0,0.5),
		glm::vec2(0.2, 0.5),
		glm::vec2(0.4, 0.5),
		glm::vec2(0.6, 0.5),
		glm::vec2(0.8, 0.5)
	};
};


#endif // _NUMFACTORY_INCLUDE

