#ifndef _RESULTSVIEW_INCLUDE
#define _RESULTSVIEW_INCLUDE

#include "Sprite.h"
#include "PurplePercentageDisplay.h"
#include "ShaderProgram.h"

class ResultsView
{

public:
	enum ResultsViewButtonName {
		RETRY,
		CONTINUE,
		MENU
	};


	static ResultsView &getInstance()
	{
		static ResultsView instance; // Guaranteed to be destroyed.
											   // Instantiated on first use.
		return instance;
	};

	void init(int goalPercentage, int currentPercentage);
	void render();
	
	int getSelectedButtonIndex();
	void changeSelectedButtonLeft();
	void changeSelectedButtonRight();

private:
	void initButtons();
	void renderButtons();

	void initShaders();

	Texture backgroundTexture;
	Sprite *background;

	PurplePercentageDisplay currentPercentageDisplay;
	PurplePercentageDisplay goalPercentageDisplay;

	Sprite *continueButton;
	Sprite *retryButton;
	Sprite *menuButton;

	int selectedButton;
	bool passedLevel;

	vector<ResultsViewButtonName> possibleButtons;

	ShaderProgram simpleTexProgram;
	glm::mat4 projection;

};

#endif // _BUTTON_INCLUDE


