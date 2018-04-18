#include "Scroller.h"
#include "Level.h"

#define SCROLL_BASE_DISPLACEMENT 5

void Scroller::scroll(int posX) 
{
	glm::vec2 cameraPos = Level::currentLevel().getLevelAttributes()->cameraPos;
	int maxCameraPosX = Level::currentLevel().getLevelAttributes()->levelSize.x - LEVEL_WIDTH;

	int scrollDisplacement;

	if (0 <= posX && posX < SCROLL_WIDTH) {
		scrollDisplacement = -SCROLL_BASE_DISPLACEMENT;
	}
	else if (LEVEL_WIDTH - SCROLL_WIDTH <= posX && posX < LEVEL_WIDTH) {
		scrollDisplacement = SCROLL_BASE_DISPLACEMENT;
	}

	if (cameraPos.x + scrollDisplacement >= 0 && cameraPos.x + scrollDisplacement <= maxCameraPosX) {
		Level::currentLevel().getLevelAttributes()->cameraPos += glm::vec2(scrollDisplacement, 0);
		scrolled = true;
	}
}

bool Scroller::isScrolled()
{
	return scrolled;
}

void Scroller::iScroll()
{
	scrolled = false;
}