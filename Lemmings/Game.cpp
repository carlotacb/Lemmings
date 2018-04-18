#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Scene.h"
#include "MouseManager.h"
#include "ShaderManager.h"

void Game::init()
{
	bPlay = true;
	bLeftMouse = bRightMouse = false;
	currentState = GameStatus::PLAYING;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	initSpriteSheets();
	ShaderManager::getInstance().init();
	menu.init();
	Scene::getInstance().init("levels/fun-2.txt");
}

bool Game::update(int deltaTime)
{
	switch (currentState) {

	case GameStatus::MENU:
		menu.update(deltaTime);
		break;

	case GameStatus::PLAYING:
		Scene::getInstance().update(deltaTime);
		break;
	}
	return bPlay;
}

void Game::render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (currentState) {

		case GameStatus::MENU:
			menu.render(); 
			break;

		case GameStatus::PLAYING:
			Scene::getInstance().render();
			break;
	}
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
	{
		if (currentState == GameStatus::PLAYING)
		{
			currentState = GameStatus::MENU;
			menu.init();
		}

		else if (currentState == GameStatus::MENU)
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
	if (key == GLUT_KEY_F1 && currentState == GameStatus::MENU) { // key f1 go to playing
		currentState = GameStatus::PLAYING;
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
	int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

	float aspectRatioX = (float(CAMERA_WIDTH) / windowWidth);
	float aspectRatioy = (float(CAMERA_HEIGHT) / windowHeight);
	mouseX = x * aspectRatioX;
	mouseY = y * aspectRatioy;

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
	Game::spriteSheets().cursorSprites.loadFromFile("images/UI/cursor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().cursorSprites.setMinFilter(GL_NEAREST);
	Game::spriteSheets().cursorSprites.setMagFilter(GL_NEAREST);

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
	
	Game::spriteSheets().greenNumSprites.loadFromFile("images/UI/green_nums.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().greenNumSprites.setMinFilter(GL_NEAREST);
	Game::spriteSheets().greenNumSprites.setMagFilter(GL_NEAREST);

	Game::spriteSheets().purpleNumSprites.loadFromFile("images/results/pink_nums.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().purpleNumSprites.setMinFilter(GL_NEAREST);
	Game::spriteSheets().purpleNumSprites.setMagFilter(GL_NEAREST);

	Game::spriteSheets().jobNamesSprites.loadFromFile("images/UI/work_names.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().jobNamesSprites.setMinFilter(GL_NEAREST);
	Game::spriteSheets().jobNamesSprites.setMagFilter(GL_NEAREST);

	Game::spriteSheets().infoWordSprites.loadFromFile("images/UI/reserved_words.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().infoWordSprites.setMinFilter(GL_NEAREST);
	Game::spriteSheets().infoWordSprites.setMagFilter(GL_NEAREST);

	Game::spriteSheets().resultsWordSprites.loadFromFile("images/results/buttons.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Game::spriteSheets().resultsWordSprites.setMinFilter(GL_NEAREST);
	Game::spriteSheets().resultsWordSprites.setMagFilter(GL_NEAREST);

}

const SoundManager * Game::getSoundManager() const {
	return &soundManager;
}