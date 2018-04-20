#include "InstructionsKeyboardManager.h"
#include "StateManager.h"
#include "Instructions.h"
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
		Instructions::getInstance().passPageRight();
		
	}

	else if (key == GLUT_KEY_LEFT)
	{
		Instructions::getInstance().passPageLeft();
	}
}

void InstructionsKeyboardManager::specialKeyReleased(int key)
{

}

