#ifndef _NUMFACTORY_INCLUDE
#define _NUMFACTORY_INCLUDE

#include <glm/glm.hpp>
#include "Sprite.h"



class NumFactory
{

public:

	virtual Sprite *createNum() = 0;

};


#endif // _NUMFACTORY_INCLUDE

