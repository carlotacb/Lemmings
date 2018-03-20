#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "MaskedTexturedQuad.h"
#include "Lemming.h"
#include "Digger.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:

	static Scene& getInstance() 
	{
		static Scene instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Scene();
	~Scene();

	static const int NUMLEMMINGS = 1;

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

private:
	Texture colorTexture;
	VariableTexture maskTexture;
	MaskedTexturedQuad *map;
	ShaderProgram simpleTexProgram, maskedTexProgram;
	float currentTime;
	glm::mat4 projection;
	//vector<Lemming> lemmings;
	Digger lemmings[NUMLEMMINGS];
	bool alive[NUMLEMMINGS];
	int actualAlive;
};


#endif // _SCENE_INCLUDE

