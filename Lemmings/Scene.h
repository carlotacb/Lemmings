#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "MaskedTexturedQuad.h"
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

	static ShaderProgram &shaderProgram()
	{
		static ShaderProgram simpleTexProgram;

		return simpleTexProgram;
	}


	void init(string levelFilePath);
	void update(int deltaTime);
	void render();

	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton);

	void eraseMask(int x, int y);
	void applyMask(int x, int y);

	VariableTexture &getMaskedMap();

private:
	void initMap();
	void initShaders();
	void initCurrentLevel(string levelFilePath);
	void initUI();

public:
	float currentTime;

private:
	Level *currentLevel;

	MaskedTexturedQuad *map;
	ShaderProgram simpleTexProgram, maskedTexProgram;
	glm::mat4 projection;

	vector<Lemming> lemmings;
	vector<bool> alive;
	int currentAlive;

	UI ui;

};
#endif // _SCENE_INCLUDE

