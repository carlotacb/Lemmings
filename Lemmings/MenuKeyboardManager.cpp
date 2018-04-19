#include <GL/glew.h>
#include <GL/glut.h>
#include "MenuKeyboardManager.h"
#include "Menu.h"
#include "LevelManager.h"
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

		switch (mode)
		{
		case 0: // FUN Levels
			LevelManager::instance().infoLevel(mode, 1);
			break;

		case 1: // TRICKY Levels
			LevelManager::instance().infoLevel(mode, 1);
			break;

		case 2: // TAXING Levels
			LevelManager::instance().infoLevel(mode, 1);
			break;
		}
	}
	else if (key == GLUT_KEY_F2) { // F2 go to Instructions
		
	}

	else if (key == GLUT_KEY_F3) { // F3 go to About
		

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

