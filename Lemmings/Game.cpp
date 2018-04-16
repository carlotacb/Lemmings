#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Scene.h"
#include "MouseManager.h"

void Game::init()
{
	bPlay = true;
	bLeftMouse = bRightMouse = false;
	currentState = GameState::PLAYING;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	initSpriteSheets();
	menu.init();
	Scene::getInstance().init("levels/fun-2.txt");
}

bool Game::update(int deltaTime)
{
	switch (currentState) {

	case GameState::MENU:
		menu.update(deltaTime);
		break;

	case GameState::PLAYING:
		Scene::getInstance().update(deltaTime);
		break;
	}
	return bPlay;
}

void Game::render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (currentState) {

		case GameState::MENU:
			menu.render(); 
			break;

		case GameState::PLAYING:
			Scene::getInstance().render();
			break;
	}
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
	{
		if (currentState == GameState::PLAYING)
		{
			currentState = GameState::MENU;
			menu.init();
		}

		else if (currentState == GameState::MENU)
			bPlay = false;
	}

	keys[key] = true;

}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	if (key == GLUT_KEY_F1 && currentState == GameState::MENU) { // key f1 go to playing
		currentState = GameState::PLAYING;
		Scene::getInstance().init("levels/fun-2.txt");
	}

	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	mouseX = x/3;
	mouseY = y/3;
	MouseManager::getInstance().mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
}

void Game::mousePress(int button)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		bLeftMouse = true;
		MouseManager::getInstance().mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
	else if(button == GLUT_RIGHT_BUTTON)
	{
		bRightMouse = true;
		MouseManager::getInstance().mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
}

void Game::mouseRelease(int button)
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

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

void Game::initSpriteSheets()
{
	Game::spriteSheets().lemmingAnimations.loadFromFile("images/lemming_anim.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().lemmingAnimations.setMinFilter(GL_NEAREST);
	Game::spriteSheets().lemmingAnimations.setMagFilter(GL_NEAREST);

	Game::spriteSheets().rotatedLemmingAnimations.loadFromFile("images/rotated_lemming_anim.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().rotatedLemmingAnimations.setMinFilter(GL_NEAREST);
	Game::spriteSheets().rotatedLemmingAnimations.setMagFilter(GL_NEAREST);

	Game::spriteSheets().doorSprites.loadFromFile("images/levels/lemming_doors.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().doorSprites.setMinFilter(GL_NEAREST);
	Game::spriteSheets().doorSprites.setMagFilter(GL_NEAREST);

	Game::spriteSheets().trapdoorSprites.loadFromFile("images/levels/lemming_trapdoors.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().trapdoorSprites.setMinFilter(GL_NEAREST);
	Game::spriteSheets().trapdoorSprites.setMagFilter(GL_NEAREST);

	Game::spriteSheets().buttonSprites.loadFromFile("images/UI/buttons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().buttonSprites.setMinFilter(GL_NEAREST);
	Game::spriteSheets().buttonSprites.setMagFilter(GL_NEAREST);

	Game::spriteSheets().numSprites.loadFromFile("images/UI/nums.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().numSprites.setMinFilter(GL_NEAREST);
	Game::spriteSheets().numSprites.setMagFilter(GL_NEAREST);
}

const SoundManager * Game::getSoundManager() const {
	return &soundManager;
}