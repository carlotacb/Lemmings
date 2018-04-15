#include <iostream>
#include "DoorFactory.h"
#include "Game.h"
#include "DoorStandard.h"
#include "DoorEgypt.h"
#include "DoorMaya.h"
#include "DoorHell.h"



Door* DoorFactory::createDoor(string type)
{
	Door *door;
	if (type == "standard") {
		door = new DoorStandard();
	}
	else if (type == "egypt") {
		door = new DoorEgypt();

	}
	else if (type == "maya") {
		door = new DoorMaya();

	}
	else if (type == "hell") {
		door = new DoorHell();

	}
	return door;
}
