#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Scene.h"

void Game::init()
{
	bPlay = true;
	bLeftMouse = bRightMouse = false;
	currentState = GameState::PLAYING;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	menu.init();
	initSpriteSheets();
	Scene::getInstance().init();
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
	if(key == 27) // Escape code
		bPlay = false;

	
	if (key == VK_F1 && currentState == GameState::MENU) { // key p go to playing
		currentState = GameState::PLAYING;
		render();
	}

	if (key == 48 && currentState == GameState::PLAYING) { // key 0 returns you to menu
		currentState = GameState::MENU;
		render();
	}

	keys[key] = true;

}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	mouseX = x;
	mouseY = y;
	Scene::getInstance().mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
}

void Game::mousePress(int button)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		bLeftMouse = true;
		Scene::getInstance().mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
	else if(button == GLUT_RIGHT_BUTTON)
	{
		bRightMouse = true;
		Scene::getInstance().mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
}

void Game::mouseRelease(int button)
{
	if(button == GLUT_LEFT_BUTTON)
		bLeftMouse = false;
	else if(button == GLUT_RIGHT_BUTTON)
		bRightMouse = false;
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

	Game::spriteSheets().doorSprites.loadFromFile("images/lemming_doors.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().doorSprites.setMinFilter(GL_NEAREST);
	Game::spriteSheets().doorSprites.setMagFilter(GL_NEAREST);

	Game::spriteSheets().trapdoorSprites.loadFromFile("images/lemming_trapdoors.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().trapdoorSprites.setMinFilter(GL_NEAREST);
	Game::spriteSheets().trapdoorSprites.setMagFilter(GL_NEAREST);
}



