#ifndef _BUTTONNUMFACTORY_INCLUDE
#define _BUTTONNUMFACTORY_INCLUDE

#include "NumFactory.h"



class ButtonNumFactory : NumFactory
{

public:

	static ButtonNumFactory &instance()
	{
		static ButtonNumFactory instance; // Guaranteed to be destroyed.
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


#endif // _BUTTONNUMFACTORY_INCLUDE

