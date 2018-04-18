#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <glm/glm.hpp>
#include <vector>
#include "MaskedTexturedQuad.h"
#include "SoundManager.h"
#include "Level.h"
#include "Lemming.h"
#include "UI.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene 
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

	
	void init(string levelFilePath);
	void update(int deltaTime);
	void render();

	void changePauseStatus();
	void changeSpeedUpStatus();
	bool isPaused();
	bool isSpeedUp();

	void eraseMask(int x, int y);
	void applyMask(int x, int y);

	int getNumLemmingAlive();
	int getLemmingIndexInPos(int posX, int posY);
	Lemming getLemming(int index);
	void assignJob(int lemmingIndex, Job *jobToAssign);

	VariableTexture &getMaskedMap();

private:
	void initMap();
	void initSounds();
	void initCurrentLevel(string levelFilePath);
	void initUI();

	void spawnLemmings();
	void updateLemmings(int deltaTime);
	void updateCurrentLevel(int deltaTime);
	void updateUI();

	
	bool insideRectangle(glm::vec2 point, glm::vec2 rectangleOrigin, glm::vec2 rectangleSize);

public:
	float currentTime;

private:
	bool paused = false;
	bool speedUp = false;

	MaskedTexturedQuad *map;

	vector<Lemming> lemmings;
	vector<bool> alive;
	int currentAlive; 
	const SoundManager* soundManager;
	FMOD::Sound* music, *dooropen;

};
#endif // _SCENE_INCLUDE

