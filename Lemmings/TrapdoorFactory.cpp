#include <iostream>
#include "TrapdoorFactory.h"
#include "Game.h"
#include "TrapdoorStandard.h"
#include "TrapdoorHell.h"

Trapdoor* TrapdoorFactory::createTrapdoor(string type)
{
	Trapdoor *trapdoor;
	if (type == "standard") {
		trapdoor = new TrapdoorStandard();
	}
	else if (type == "hell") {
		trapdoor = new TrapdoorHell();

	}
	return trapdoor;
}
