#include "SceneKeyboardManager.h"
#include "StateManager.h"

void SceneKeyboardManager::keyPressed(int key)
{
	if (key == 27)
	{
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