#include "InstructionsKeyboardManager.h"
#include "StateManager.h"
#include "Game.h"

void InstructionsKeyboardManager::keyPressed(int key)
{
	if (key == 27)
	{
		StateManager::instance().changeMenu();
	}

}

void InstructionsKeyboardManager::keyReleased(int key)
{

}

void InstructionsKeyboardManager::specialKeyPressed(int key)
{
	if (key == GLUT_KEY_RIGHT)
	{
		
	}

	else if (key == GLUT_KEY_LEFT)
	{
		
	}
}

void InstructionsKeyboardManager::specialKeyReleased(int key)
{

}

