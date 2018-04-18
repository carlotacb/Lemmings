#ifndef _PURPLENUMFACTORY_INCLUDE
#define _PURPLENUMFACTORY_INCLUDE

#include "NumFactory.h"

class PurpleNumFactory : NumFactory
{

public:

	static PurpleNumFactory &instance()
	{
		static PurpleNumFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Sprite *createNum();
	Sprite *createSymbol(char symbol);

private:
	glm::vec2 numPositions[11] = {
		glm::vec2(0, 0),
		glm::vec2(18./128, 0),
		glm::vec2(36./ 128, 0),
		glm::vec2(54./ 128, 0),
		glm::vec2(72./ 128, 0),
		glm::vec2(90./ 128, 0),
		glm::vec2(0, 24./ 64),
		glm::vec2(18./ 128, 24. / 64),
		glm::vec2(36./ 128, 24. / 64),
		glm::vec2(54./ 128, 24. / 64),
		glm::vec2(72. / 128, 24. / 64)
	};
};


#endif // _PURPLENUMFACTORY_INCLUDE

