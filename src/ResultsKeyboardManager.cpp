#include <GL/glew.h>
#include <GL/glut.h>
#include "ResultsKeyboardManager.h"
#include "Results.h"
#include "LevelManager.h"
#include "StateManager.h"
#include "Game.h"

void ResultsKeyboardManager::keyPressed(int key)
{
	if (key == 13)
	{
		int selected = Results::getInstance().getSelectedButton();
		int currentLevel = LevelManager::getInstance().getActualLevel();
		int currentMode = LevelManager::getInstance().getActualMode();

		switch (selected) {
			case 0: // RETRY
				StateManager::instance().changeInfo(currentMode, currentLevel);
				break;

			case 1: // CONTINUE
				
				switch (currentMode) {
					case FUN_MODE:
						if (currentLevel < 4) StateManager::instance().changeInfo(currentMode, currentLevel + 1);
						else if (currentLevel == 4) StateManager::instance().changeInfo(currentMode, 7);
						else StateManager::instance().changeInfo(TRICKY_MODE, 1);
						break;
					case TRICKY_MODE:
						if (currentLevel < 3) StateManager::instance().changeInfo(currentMode, currentLevel + 1);
						else StateManager::instance().changeInfo(TAXING_MODE, 1);
						break;
					case TAXING_MODE:
						StateManager::instance().changeMenu();
						break;
				}

				break;

			case 2: // MENU
				StateManager::instance().changeMenu();
				break;
		}
	}
}

void ResultsKeyboardManager::keyReleased(int key)
{

}

void ResultsKeyboardManager::specialKeyPressed(int key)
{
	if (key == GLUT_KEY_RIGHT)
	{
		Results::getInstance().changeSelectedButtonRight();
	}

	else if (key == GLUT_KEY_LEFT)
	{
		Results::getInstance().changeSelectedButtonLeft();
	}
}

void ResultsKeyboardManager::specialKeyReleased(int key)
{

}

