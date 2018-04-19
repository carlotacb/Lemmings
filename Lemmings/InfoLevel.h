#ifndef _INFOLEVEL_INCLUDE
#define _INFOLEVEL_INCLUDE

#include "GameState.h"
#include "Texture.h"
#include "Sprite.h"

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

private:

	// Functions
	void initTextures();

	// Parametres
	Texture InfoLevelTexture;
	Sprite* InfoLevelSprite;

	int mode;
	int level;

};


#endif