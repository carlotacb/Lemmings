#include "Game.h"

void Game::init()
{
	bPlay = true;
	GameState::instance().setCurrentState(0);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	initSpriteSheets();
	ShaderManager::getInstance().init();
	Menu::instance().init();
	Scene::getInstance().init("levels/fun-1.txt");
}

bool Game::update(int deltaTime)
{
	switch (GameState::instance().getCurrentState()) {

	case 0: // Menu
		Menu::instance().update(deltaTime);
		break;

	case 1: // Playing
		Scene::getInstance().update(deltaTime);
		break;

	case 2: // About
		break;

	case 3: // Help
		break;
	}

	return bPlay;
}

void Game::render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (GameState::instance().getCurrentState()) {

		case 0: // Menu
			Menu::instance().render();
			break;

		case 1: // Playing
			Scene::getInstance().render();
			break;

		case 2: // About
			break;

		case 3: // Help
			break;
	}
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

void Game::changeBplay(bool newvalue)
{
	bPlay = newvalue;
}



const SoundManager * Game::getSoundManager() const {
	return &soundManager;
}