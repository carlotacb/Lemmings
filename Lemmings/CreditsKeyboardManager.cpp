#include <GL/glew.h>
#include <GL/glut.h>
#include "CreditsKeyboardManager.h"
#include "Credits.h"
#include "LevelManager.h"
#include "Game.h"

void CreditsKeyboardManager::keyPressed(int key)
{
	
	if (key == 27) // Escape code
	{
		Game::instance().changeBplay();
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

