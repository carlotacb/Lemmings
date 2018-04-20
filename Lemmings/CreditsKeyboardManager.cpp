#include <GL/glew.h>
#include <GL/glut.h>
#include "CreditsKeyboardManager.h"
#include "Credits.h"
#include "StateManager.h"

void CreditsKeyboardManager::keyPressed(int key)
{
	
	if (key == 27) // Escape code
	{
		StateManager::instance().changeMenu();
	}
	
}

void CreditsKeyboardManager::keyReleased(int key)
{

}

void CreditsKeyboardManager::specialKeyPressed(int key)
{
}

void CreditsKeyboardManager::specialKeyReleased(int key)
{

}

