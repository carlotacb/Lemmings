#include "MouseManager.h"
#include "Scene.h"
#include "UI.h"
#include "Button.h"
#include "JobFactory.h"

void MouseManager::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton)
{

	ScreenArea screenArea = getScreenArea(mouseX, mouseY);

	switch (mouseState) {

		case LEFT_MOUSE_PRESSED:
			if (!bLeftButton) {
				mouseState = NONE;

			}
			break;

		case RIGHT_MOUSE_PRESSED:
			
			if (!bRightButton) {
				mouseState = NONE;
			}
			break;

		case NONE:

			if (bLeftButton) {
				mouseState = LEFT_MOUSE_PRESSED;

				if (screenArea == ScreenArea::UI) {
					leftClickOnUI(mouseX, mouseY);
				}
				else  if (screenArea == ScreenArea::MAP) {
					leftClickOnMap(mouseX, mouseY);
				}

			}

			else if (bRightButton) {
				mouseState = RIGHT_MOUSE_PRESSED;

				if (screenArea == ScreenArea::UI) {
				}
				else if (screenArea == ScreenArea::MAP) {

				}

			}

			break;
	}
}

MouseManager::ScreenArea MouseManager::getScreenArea(int mouseX, int mouseY)
{
	if (
		0 <= mouseX 
		&& mouseX < LEVEL_WIDTH
		&& 0 <= mouseY
		&& mouseY < LEVEL_HEIGHT
	) {
		return ScreenArea::MAP;
	}
	else if (
		0 <= mouseX
		&& mouseX < UI_WIDTH
		&& LEVEL_HEIGHT <= mouseY
		&& mouseY < LEVEL_HEIGHT + UI_HEIGHT
	) {
		return ScreenArea::UI;
	}
}

void MouseManager::leftClickOnUI(int posX, int posY)
{
	int clickedButtonIndex = UI::getInstance().getButtonIndexInPos(posX);
	UI::getInstance().changeSelectedButton(clickedButtonIndex);

	if (clickedButtonIndex == -1) {
		return;
	}

	activateButton(clickedButtonIndex);
}

void MouseManager::activateButton(int buttonIndex) 
{
	delete jobToAssign;
	jobToAssign = NULL;

	switch (buttonIndex)
	{
	case Button::MINUS_BUTTON:
		if (Level::currentLevel().getLevelAttributes()->releaseRate > Level::currentLevel().getLevelAttributes()->minReleaseRate) {
			--Level::currentLevel().getLevelAttributes()->releaseRate;
		}
		break;
	case Button::PLUS_BUTTON:
		if (Level::currentLevel().getLevelAttributes()->releaseRate < 99) {
			++Level::currentLevel().getLevelAttributes()->releaseRate;
		}
		break;
	case Button::CLIMBER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			jobToAssign = JobFactory::instance().createDiggerJob();
		}
		break;
	case Button::FLOATER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			jobToAssign = JobFactory::instance().createDiggerJob();
		}
		break;
	case Button::EXPLODER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			jobToAssign = JobFactory::instance().createExploderJob();
		}
		break;
	case Button::BLOCKER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			jobToAssign = JobFactory::instance().createBlockerJob();
		}
		break;
	case Button::BUILDER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			jobToAssign = JobFactory::instance().createDiggerJob();
		}
		break;
	case Button::BASHER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			jobToAssign = JobFactory::instance().createBasherJob();
		}
		break;
	case Button::MINER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			jobToAssign = JobFactory::instance().createMinerJob();
		}
		break;
	case Button::DIGGER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			jobToAssign = JobFactory::instance().createDiggerJob();
		}
		break;
	case Button::PAUSE_BUTTON:

		break;
	case Button::NUKE_BUTTON:

		break;
	default:
		break;
	}

}

void MouseManager::leftClickOnMap(int posX, int posY)
{
	if (jobToAssign != NULL) {

		int selectedLemmingIndex = Scene::getInstance().getLemmingIndexInPos(posX, posY);
		if (selectedLemmingIndex != -1) {
			Scene::getInstance().assignJob(selectedLemmingIndex, jobToAssign);
			jobToAssign = NULL;
			UI::getInstance().decreaseSelectedButtonJobCount();
			UI::getInstance().changeSelectedButton(-1);
		}
	}
}