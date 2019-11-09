#ifndef _LETTERFACTORY_INCLUDE
#define _LETTERFACTORY_INCLUDE

#include "Sprite.h"


class LetterFactory
{

public:

	static LetterFactory &instance()
	{
		static LetterFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Sprite *createLetter(char c);

};


#endif // _LETTERFACTORY_INCLUDE

