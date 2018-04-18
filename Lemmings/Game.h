#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "Menu.h"
#include "SoundManager.h"


// Game is a singleton (a class with a single instance) that represents our whole application

enum class GameState {
	MENU,
	PLAYING
};


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
		Texture buttonSprites;
		Texture jobNamesSprites;
		Texture infoWordSprites;
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
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	const SoundManager* getSoundManager() const;


private:
	bool bPlay;                       // Continue to play game?
	SoundManager soundManager;
	Menu menu;							
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
	int mouseX, mouseY;               // Mouse position
	bool bLeftMouse, bRightMouse;     // Mouse button states
	GameState currentState;

};


#endif // _GAME_INCLUDE


