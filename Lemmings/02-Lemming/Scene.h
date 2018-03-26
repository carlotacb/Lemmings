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
	Scene();
	~Scene();

	static const int NUMLEMMINGS = 50;

	void init();
	void update(int deltaTime);
	void render();
	
	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton);

private:
	void initShaders();
	void eraseMask(int mouseX, int mouseY);
	void applyMask(int mouseX, int mouseY);
	void printDoors(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram);

private:
	Texture colorTexture;
	VariableTexture maskTexture;
	Sprite *door; 
	Texture spritesheet;
	MaskedTexturedQuad *map;
	ShaderProgram simpleTexProgram, maskedTexProgram;
	float currentTime;
	glm::mat4 projection;
	//vector<Lemming> lemmings;
	Lemming lemmings[NUMLEMMINGS];
	bool alive[NUMLEMMINGS];
	int actualAlive;
};


#endif // _SCENE_INCLUDE

