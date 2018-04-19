#ifndef _INSTRUCTIONS_INCLUDE
#define _INSTRUCTIONS_INCLUDE

#include "GameState.h"
#include "Texture.h"
#include "Sprite.h"
//#include "Text.h"

class Instructions : public GameState
{

public:
	static Instructions &getInstance()
	{
		static Instructions instance;
		return instance;
	};

	void init();
	void update(int deltaTime);
	void render();

private:

	// Functions
	void initTextures();
	void initSprites();

	// Parametres
	Texture instructionsLevelTexture;
	Sprite* instructionsLevelSprite;

	//vector<Text*> instructionPages;

	Sprite *leftKey;
	Sprite *rightKey;
	Sprite *escapeKey;

};


#endif // _INSTRUCTIONS_INCLUDE