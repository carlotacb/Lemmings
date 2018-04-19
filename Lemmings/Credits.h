#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE

#include "GameState.h"
#include "Texture.h"
#include "Sprite.h"

class Credits : public GameState
{

public:
	static Credits &instance()
	{
		static Credits instance;
		return instance;
	};

	void init();
	void update(int deltaTime);
	void render();

private:

	// Functions
	void initTextures();

	// Parametres
	Texture creditsLevelTexture;
	Sprite* creditsLevelSprite;

};


#endif