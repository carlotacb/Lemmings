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
		int selected = Results::getInstance().getSelectedButtonIndex();
		int currentLevel = LevelManager::instance().getActualLevel();
		int currentMode = LevelManager::instance().getActualMode();

		switch (selected) {
			case 0: // RETRY
				StateManager::instance().changeInfo(currentMode, currentLevel);
				break;

			case 1: // CONTINUE
				StateManager::instance().changeInfo(currentMode, currentLevel + 1);
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

