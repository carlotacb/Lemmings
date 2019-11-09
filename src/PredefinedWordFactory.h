#ifndef _PREDEFINEDWORDFACTORY_INCLUDE
#define _PREDEFINEDWORDFACTORY_INCLUDE

#include <glm/glm.hpp>
#include "Button.h"


class PredefinedWordFactory
{

public:
	enum JobNames {
		WALKER,
		MINER,
		FLOATER,
		FALLER,
		DIGGER,
		CLIMBER,
		BUILDER,
		BLOCKER,
		BASHER,
		NONE
	};

	static PredefinedWordFactory &instance()
	{
		static PredefinedWordFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Sprite *createJobWord();
	Sprite *createInfoWord(string infoWord);

};


#endif // _PREDEFINEDWORDFACTORY_INCLUDE

