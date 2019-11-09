#include "SceneKeyboardManager.h"
#include "StateManager.h"
#include "LevelManager.h"

void SceneKeyboardManager::keyPressed(int key)
{
	if (key == 27)
	{
		LevelManager::getInstance().endMusic();
		StateManager::instance().changeMenu();
	}
}

void SceneKeyboardManager::keyReleased(int key)
{

}

void SceneKeyboardManager::specialKeyPressed(int key)
{
	
}

void SceneKeyboardManager::specialKeyReleased(int key)
{

}