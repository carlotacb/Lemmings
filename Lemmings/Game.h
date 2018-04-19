#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include <GL/glew.h>
#include <GL/glut.h>
#include "Scene.h"
#include "Menu.h"
#include "SoundManager.h"
#include "MouseManager.h"
#include "KeyboardManager.h"
#include "GameState.h"
#include "ShaderManager.h"


// Game is a singleton (a class with a single instance) that represents our whole application


class Game {

private:
	struct SpriteSheets {
		Texture cursorSprites;
		Texture lemmingAnimations;
		Texture rotatedLemmingAnimations;
		Texture doorSprites;
		Texture trapdoorSprites;
		Texture numSprites;
		Texture greenNumSprites;
		Texture purpleNumSprites;
		Texture buttonSprites;
		Texture jobNamesSprites;
		Texture infoWordSprites;
		Texture resultsWordSprites;
		Texture stepSprite;
	};

	void initSpriteSheets();

public:
	Game() {}
	
	
	static Game &instance()	{
		static Game G;
	
		return G;
	}
	

	static SpriteSheets &spriteSheets()
	{
		static SpriteSheets spriteSheets;

		return spriteSheets;
	}

	void init();
	bool update(int deltaTime);
	void render();
	void changeBplay(bool newvalue);

	const SoundManager* getSoundManager() const;


private:
	SoundManager soundManager;
	bool bPlay; // Continue to play game?

};


#endif // _GAME_INCLUDE


