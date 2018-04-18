#include "MouseManager.h"
#include "Scene.h"
#include "Scroller.h"
#include "UI.h"
#include "UIAdapter.h"
#include "JobAssigner.h"

void MouseManager::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton)
{
	posX = mouseX;
	posY = mouseY;

	ScreenClickedArea screenClickedArea = getClickedScreenArea(mouseX, mouseY);
	screenMovedArea = getMovedScreenArea(mouseX, mouseY);

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

				if (screenClickedArea == ScreenClickedArea::UI) {
					leftClickOnUI(mouseX, mouseY);
				}
				else  if (screenClickedArea == ScreenClickedArea::MAP) {
					leftClickOnMap(mouseX, mouseY);
				}

			}

			else if (bRightButton) {
				mouseState = RIGHT_MOUSE_PRESSED;

				if (screenClickedArea == ScreenClickedArea::UI) {
				}
				else if (screenClickedArea == ScreenClickedArea::MAP) {

				}

			}
			else {

			}

			break;
	}
}

void MouseManager::update()
{
	if (mouseState == NONE) {
		if (screenMovedArea == ScreenMovedArea::SCROLL_AREA) {
			Scroller::getInstance().scroll(posX);
		}
		else if (screenMovedArea == ScreenMovedArea::LEVEL) {
			int lemmingIndex = Scene::getInstance().getLemmingIndexInPos(posX, posY);
			UIAdapter::getInstance().changeFocusedLemming(lemmingIndex);

		}
	}
}

MouseManager::ScreenClickedArea MouseManager::getClickedScreenArea(int mouseX, int mouseY)
{
	if (
		0 <= mouseX 
		&& mouseX < LEVEL_WIDTH
		&& 0 <= mouseY
		&& mouseY < LEVEL_HEIGHT
	) {
		return ScreenClickedArea::MAP;
	}
	else if (
		0 <= mouseX
		&& mouseX < UI_WIDTH
		&& LEVEL_HEIGHT <= mouseY
		&& mouseY < LEVEL_HEIGHT + UI_HEIGHT
	) {
		return ScreenClickedArea::UI;
	}
}

MouseManager::ScreenMovedArea MouseManager::getMovedScreenArea(int mouseX, int mouseY)
{
	if (
		(0 <= mouseX && mouseX < SCROLL_WIDTH) || (LEVEL_WIDTH - SCROLL_WIDTH <= mouseX && mouseX < LEVEL_WIDTH)
		&& mouseY < LEVEL_HEIGHT
	) {
		return ScreenMovedArea::SCROLL_AREA;
	}
	else if (SCROLL_WIDTH <= mouseX && mouseX < LEVEL_WIDTH - SCROLL_WIDTH && mouseY < LEVEL_HEIGHT) {
		return ScreenMovedArea::LEVEL;
	}
}


void MouseManager::leftClickOnUI(int posX, int posY)
{
	int clickedButtonIndex = UI::getInstance().getButtonIndexInPos(posX, posY);
	UIAdapter::getInstance().changeSelectedButton(clickedButtonIndex);
}


void MouseManager::leftClickOnMap(int posX, int posY)
{

	if (JobAssigner::getInstance().hasJobToAssign()) {

		int selectedLemmingIndex = Scene::getInstance().getLemmingIndexInPos(posX, posY);
		JobAssigner::getInstance().assigJobLemming(selectedLemmingIndex);
		UI::getInstance().decreaseSelectedButtonJobCount();
	}
}