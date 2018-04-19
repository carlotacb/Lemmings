#ifndef _RESULTS_INCLUDE
#define _RESULTS_INCLUDE

#include "GameState.h"
#include "Sprite.h"
#include "PurplePercentageDisplay.h"

class Results : public GameState
{

public:
	enum ResultsButtonName {
		RETRY,
		CONTINUE,
		MENU
	};


	static Results &getInstance()
	{
		static Results instance; // Guaranteed to be destroyed.
											   // Instantiated on first use.
		return instance;
	};

	void init();
	void update(int deltaTime);
	void render();
	
	void setPercentages(int goalPercentage, int currentPercentage);

	int getSelectedButtonIndex();
	void changeSelectedButtonLeft();
	void changeSelectedButtonRight();

private:
	void initButtons();
	void renderButtons();

	Texture backgroundTexture;
	Sprite *background;

	PurplePercentageDisplay currentPercentageDisplay;
	PurplePercentageDisplay goalPercentageDisplay;

	Sprite *continueButton;
	Sprite *retryButton;
	Sprite *menuButton;

	int selectedButton;
	bool passedLevel;

	vector<ResultsButtonName> possibleButtons;

};

#endif // _RESULTS_INCLUDE


