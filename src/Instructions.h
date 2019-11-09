#ifndef _INSTRUCTIONS_INCLUDE
#define _INSTRUCTIONS_INCLUDE

#include "GameState.h"
#include "Texture.h"
#include "Sprite.h"
#include "Word.h"
#include "SoundManager.h"

#define LINESPAGE 20

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
	void passPageLeft();
	void passPageRight();
	void endMusic();

private:

	// Functions
	void initTextures();
	void initSprites();
	void initLines();

	int actualPage;

	// Parametres
	Texture instructionsLevelTexture;
	Sprite* instructionsLevelSprite;

	vector<Word*> instructionPages;

	Sprite *leftKey;
	Sprite *rightKey;
	Sprite *escapeKey;
	Word *instructionsWord;

	bool onlyLeft;
	bool onlyRight;

	const SoundManager* soundManager;
	FMOD::Sound* music;
	FMOD::Channel* channel;

};


#endif // _INSTRUCTIONS_INCLUDE