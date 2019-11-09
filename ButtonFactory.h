#ifndef _BUTTONFACTORY_INCLUDE
#define _BUTTONFACTORY_INCLUDE

#include <glm/glm.hpp>
#include "Button.h"


class ButtonFactory
{

public:

	static ButtonFactory &instance()
	{
		static ButtonFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Button createButton(int buttonName);

};


#endif // _BUTTONFACTORY_INCLUDE

