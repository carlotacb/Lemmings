#include "Menu.h"
#include "InfoLevel.h"
#include "Scene.h"
#include "Results.h"
#include "Credits.h"
#include "Instructions.h"
#include "Game.h"
#include "StateManager.h"

void StateManager::changeMenu()
{
	Menu::getInstance().init();
	Game::instance().setGameState(&Menu::getInstance());
}

void StateManager::changeInfo(int levelMode, int levelNum)
{
	InfoLevel::instance().init();
	InfoLevel::instance().setLevel(1, levelMode);
	Game::instance().setGameState(&InfoLevel::instance());
}

void StateManager::changeScene(int levelMode, int levelNum)
{
	string modeName;
	switch (levelMode) {
	case FUN_MODE:
		modeName = "fun";
		break;
	case TRICKY_MODE:
		modeName = "tricky";
		break;
	case TAXING_MODE:
		modeName = "taxing";
		break;
	}

	Scene::getInstance().startLevel(modeName, levelNum);
	Scene::getInstance().init();
	Game::instance().setGameState(&Scene::getInstance());

}

void StateManager::changeResults(int goalPercentage, int currentPercentage)
{
	Results::getInstance().init();
	Results::getInstance().setPercentages(goalPercentage, currentPercentage);
	Game::instance().setGameState(&Results::getInstance());
}

void StateManager::changeCredits()
{
	Credits::instance().init();
	Game::instance().setGameState(&Credits::instance());
}

void StateManager::changeInstructions()
{
	Instructions::getInstance().init();
	Game::instance().setGameState(&Instructions::getInstance());
}
