#include "InfoLevelKeyboardManager.h"
#include "LevelManager.h"
#include "Game.h"
#include "StateManager.h"

void InfoLevelKeyboardManager::keyPressed(int key)
{
	if (key == 27) // Escape code
	{
		StateManager::instance().changeMenu();
	}
}

void InfoLevelKeyboardManager::keyReleased(int key)
{

}

void InfoLevelKeyboardManager::specialKeyPressed(int key)
{
	
	if (key == GLUT_KEY_RIGHT)
	{
		StateManager::instance().changeScene(InfoLevel::instance().getMode(), InfoLevel::instance().getLevel());
	}

	else if (key == GLUT_KEY_LEFT)
	{
		StateManager::instance().changeMenu();
	}
}

void InfoLevelKeyboardManager::specialKeyReleased(int key)
{

}

