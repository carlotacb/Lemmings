#ifndef _GREENNUMFACTORY_INCLUDE
#define _GREENNUMFACTORY_INCLUDE

#include "NumFactory.h"

class GreenNumFactory : NumFactory
{

public:

	static GreenNumFactory &instance()
	{
		static GreenNumFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Sprite *createNum();
	Sprite *createSymbol(char symbol);

private:
	glm::vec2 numPositions[11] = {
		glm::vec2(0, 0),
		glm::vec2(0.25, 0),
		glm::vec2(0.5, 0),
		glm::vec2(0.75, 0),
		glm::vec2(0, 0.25),
		glm::vec2(0.25,0.25),
		glm::vec2(0.5, 0.25),
		glm::vec2(0.75, 0.25),
		glm::vec2(0, 0.5),
		glm::vec2(0.25, 0.5),
		glm::vec2(0.75, 0.75)
	};
};


#endif // _GREENNUMFACTORY_INCLUDE

