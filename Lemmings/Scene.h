#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include "GameState.h"
#include <glm/glm.hpp>
#include <vector>
#include "MaskedTexturedQuad.h"
#include "Level.h"
#include "UI.h"
#include "Word.h"
#include "MaskManager.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene : public GameState
{

public:

	static Scene &getInstance()
	{
		static Scene instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

	void eraseMask(int x, int y);
	void applyMask(int x, int y);
	void eraseSpecialMask(int x, int y);
	void applySpecialMask(int x, int y);
	
	void buildStep(glm::vec2 position);
	
	void changePauseStatus();
	void changeSpeedUpStatus();
	bool isPaused();
	bool isSpeedUp();
	
	char getPixel(int x, int y);

	
	VariableTexture &getMaskedMap();

	void setMaskManager(MaskManager* maskManager);

private:
	void initMap();
	void initUI();
	void updateUI();

	bool paused = false;
	bool speedUp = false;

	MaskedTexturedQuad *map;

	MaskManager *maskManager;

};

#endif // _SCENE_INCLUDE

