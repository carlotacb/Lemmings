#include <GL/glew.h>
#include <GL/glut.h>
#include "ResultsKeyboardManager.h"
#include "Results.h"
#include "LevelManager.h"
#include "Game.h"

void ResultsKeyboardManager::keyPressed(int key)
{	
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

