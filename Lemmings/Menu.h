#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"

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
	Texture menuAboutTexture;
	Texture menuHelpTexture;
	Texture menuExitTexture;
	Texture menuModeTexture;
	Texture menuPlayingTexture;
	
	Sprite* menuBackground;
	Sprite* menuLogo;
	Sprite* menuAbout;
	Sprite* menuHelp;
	Sprite* menuExit;
	Sprite* menuMode;
	Sprite* menuPlaying;

	ShaderProgram simpleTexProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif