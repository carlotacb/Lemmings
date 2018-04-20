#include <GL/glew.h>
#include <GL/glut.h>
#include "MenuKeyboardManager.h"
#include "Menu.h"
#include "StateManager.h"
#include "Game.h"

void MenuKeyboardManager::keyPressed(int key)
{
	if (key == 27) // Escape code
	{
		Game::instance().changeBplay();
	}	
}

void MenuKeyboardManager::keyReleased(int key)
{

}

void MenuKeyboardManager::specialKeyPressed(int key)
{
	if (key == GLUT_KEY_F1) { // key f1 go to playing
		int mode = Menu::getInstance().getMode();
		StateManager::instance().changeInfo(mode, 1);
	}
	else if (key == GLUT_KEY_F2) { // F2 go to Instructions
		StateManager::instance().changeInstructions();
	}

	else if (key == GLUT_KEY_F3) { // F3 go to About
		StateManager::instance().changeCredits();
	}
	else if (key == GLUT_KEY_UP)
	{
		Menu::getInstance().changeModeUp();
	}

	else if (key == GLUT_KEY_DOWN)
	{
		Menu::getInstance().changeModeDown();
	}
}

void MenuKeyboardManager::specialKeyReleased(int key)
{

}

