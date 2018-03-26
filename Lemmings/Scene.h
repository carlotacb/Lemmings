#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "MaskedTexturedQuad.h"
#include "Lemming.h"

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


	static 	VariableTexture &maskedMap()
	{
		static 	VariableTexture maskTexture; // Guaranteed to be destroyed.
							   // Instantiated on first use.
		return maskTexture;
	};

	static const int NUMLEMMINGS = 10;

	void init();
	void update(int deltaTime);
	void render();

	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton);

	void eraseMask(int x, int y);
	void applyMask(int x, int y);

private:
	void initShaders();
	void eraseMaskInMouse(int mouseX, int mouseY);
	void applyMaskInMouse(int mouseX, int mouseY);
	void initDoors(const glm::vec2 &initialTrapdoorPosition, const glm::vec2 &initialDoorPosition);

public:
	float currentTime;

private:
	Sprite *door;
	Sprite *trapdoor;
	Texture colorTexture;
	MaskedTexturedQuad *map;
	ShaderProgram simpleTexProgram, maskedTexProgram;
	glm::mat4 projection;
	Lemming lemmings[NUMLEMMINGS];
	bool alive[NUMLEMMINGS];
	int actualAlive;

};
#endif // _SCENE_INCLUDE

