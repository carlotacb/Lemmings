#ifndef _PREDEFINEDWORDFACTORY_INCLUDE
#define _PREDEFINEDWORDFACTORY_INCLUDE

#include <glm/glm.hpp>
#include "Button.h"


class PredefinedWordFactory
{

public:

	static PredefinedWordFactory &instance()
	{
		static PredefinedWordFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Sprite *createJobWord(string jobName);
	Sprite *createInfoWord(string infoWord);

};


#endif // _PREDEFINEDWORDFACTORY_INCLUDE

