#include "GameState.h"

int GameState::getCurrentState()
{
	return currentState;
}

void GameState::setCurrentState(int newState)
{
	currentState = newState;
}

void GameState::keyPressed(int key)
{
	if (key == 27) // Escape code
	{
		if (currentState != 0)
		{
			currentState = 0;
			Menu::instance().init();
		}

		else if (currentState == 0)
			Game::instance().changeBplay(false);
	}

	int mode = Menu::instance().getMode();

	if (key == GLUT_KEY_UP && mode != 0) // Escape code
	{
		if (mode == 1) {
			Menu::instance().changeMode(0, glm::vec2(1.f, 256. / 1024));
		}
		else if (mode == 2) {
			Menu::instance().changeMode(1, glm::vec2(1.f, 512. / 1024));
		}
	}

	if (key == GLUT_KEY_DOWN && mode != 2) // Escape code
	{
		if (mode == 0)
		{
			Menu::instance().changeMode(1, glm::vec2(1.f, 512. / 1024));
		}

		else if (mode == 1) {
			Menu::instance().changeMode(2, glm::vec2(1.f, 768. / 1024));
		}
	}

	keys[key] = true;

}

void GameState::keyReleased(int key)
{
	keys[key] = false;
}

void GameState::specialKeyPressed(int key)
{
	if (currentState == 0) KeyboardManager::getInstance().menuControlSpecialKey(key, Menu::instance().getMode());
	

	/*{
		if (key == GLUT_KEY_F1) { // key f1 go to playing
			currentState = 1;
			Scene::getInstance().init("levels/fun-1.txt");
		}

		else if (key == GLUT_KEY_F2) { // F2 go to Instructions
			currentState = 2;
		}

		else if (key == GLUT_KEY_F3) { // F3 go to About
			currentState = 3;

		}

	}*/
	
	specialKeys[key] = true;
}

void GameState::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void GameState::mouseMove(int x, int y)
{
	int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

	float aspectRatioX = (float(CAMERA_WIDTH) / windowWidth);
	float aspectRatioy = (float(CAMERA_HEIGHT) / windowHeight);
	mouseX = x * aspectRatioX;
	mouseY = y * aspectRatioy;

	MouseManager::getInstance().mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
}

void GameState::mousePress(int button)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		bLeftMouse = true;
		MouseManager::getInstance().mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		bRightMouse = true;
		MouseManager::getInstance().mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
}

void GameState::mouseRelease(int button)
{
	if (button == GLUT_LEFT_BUTTON) {
		bLeftMouse = false;
		MouseManager::getInstance().mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}

	else if (button == GLUT_RIGHT_BUTTON) {
		bRightMouse = false;
		MouseManager::getInstance().mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}

}

bool GameState::getKey(int key) const
{
	return keys[key];
}

bool GameState::getSpecialKey(int key) const
{
	return specialKeys[key];
}

