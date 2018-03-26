#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"
#include "Lemming.h"

class Menu {

public:
	Menu();
	~Menu();
	void init();
	void update(int deltaTime);
	void render();

private:

	// Functions

	void initShaders();
	void initTextures();
	
	// Parametres

	Texture menuTexture; 
	Texture menuLogoTexture;
	Texture menuFunTexture;
	Texture menuTrickyTexture;
	Texture menuTaxingTexture;
	Texture menuMayhemTexture;
	Texture menuAboutTexture;
	
	Sprite* menuBackground;
	Sprite* menuLogo;
	Sprite* menuFun;
	Sprite* menuTricky;
	Sprite* menuTaxing;
	Sprite* menuMayhem;
	Sprite* menuAbout;

	ShaderProgram simpleTexProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif