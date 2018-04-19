#include "InstructionsKeyboardManager.h"
#include "Instructions.h"
#include "LevelManager.h"
#include "Game.h"

void InstructionsKeyboardManager::keyPressed(int key)
{
	

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

