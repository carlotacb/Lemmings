#include "KeyboardManager.h"


void KeyboardManager::menuControlSpecialKey(int key, int mode)
{
	if (key == GLUT_KEY_F1) { // key f1 go to playing
		
		switch (mode)
		{
			case 0: // FUN Levels
				LevelManager::instance().infoLevel(Menu::instance().getMode(), 1);
				break;

			case 1: // TRICKY Levels
				LevelManager::instance().infoLevel(Menu::instance().getMode(), 1);
				break;

			case 2: // TAXING Levels
				LevelManager::instance().infoLevel(Menu::instance().getMode(), 1);
				break;
		}
		
		GameState::instance().setCurrentState(1);
		
	}



}