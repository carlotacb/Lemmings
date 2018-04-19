#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"

class Menu {

public:
	static Menu &instance()
	{
		static Menu instance;
		return instance;
	};

	Menu();
	~Menu();
	void init();
	void update(int deltaTime);
	void render();
	void changeMode(int newmode, glm::vec2 coord);
	int getMode();

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

	int mode; // 0 = FUN, 1 = TRICKY, 2 = TAXING

	ShaderProgram simpleTexProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif