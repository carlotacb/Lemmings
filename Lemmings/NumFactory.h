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
		glm::vec2(0, 0),
		glm::vec2(0.25, 0),
		glm::vec2(0.5, 0),
		glm::vec2(0.75, 0),
		glm::vec2(0, 0.25),
		glm::vec2(0.25,0.25),
		glm::vec2(0.5, 0.25),
		glm::vec2(0.75, 0.25),
		glm::vec2(0, 0.5),
		glm::vec2(0.25, 0.5)
	};
};


#endif // _NUMFACTORY_INCLUDE

