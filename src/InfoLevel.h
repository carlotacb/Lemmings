#ifndef _INFOLEVEL_INCLUDE
#define _INFOLEVEL_INCLUDE

#include "GameState.h"
#include "Texture.h"
#include "Sprite.h"
#include "Word.h"

class InfoLevel : public GameState
{

public:
	static InfoLevel &instance()
	{
		static InfoLevel instance;
		return instance;
	};

	void init();
	void update(int deltaTime);
	void render();

	void setLevel(int level, int mode);
	int getMode();
	int getLevel();

private:

	// Functions
	void initTextures();
	void initSprites();

	// Parametres
	Texture InfoLevelTexture;
	Sprite* InfoLevelSprite;
	Sprite *leftKey;
	Sprite *rightKey;
	Word *playWord;
	Word *menuWord;

	int mode;
	int level;

};


#endif