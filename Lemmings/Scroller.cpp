#include "Scroller.h"
#include "Level.h"

#define SCROLL_BASE_DISPLACEMENT 5

void Scroller::scrollLeft()
{
	int scrollDisplacement = -SCROLL_BASE_DISPLACEMENT;
	scroll(scrollDisplacement);
	
}

void Scroller::scrollRight()
{
	int scrollDisplacement = SCROLL_BASE_DISPLACEMENT;
	scroll(scrollDisplacement);
}

bool Scroller::isScrolled()
{
	return scrolled;
}

void Scroller::iScroll()
{
	scrolled = false;
}

void Scroller::scroll(int scrollDisplacement)
{
	glm::vec2 cameraPos = Level::currentLevel().getLevelAttributes()->cameraPos;
	int maxCameraPosX = Level::currentLevel().getLevelAttributes()->levelSize.x - LEVEL_WIDTH;

	if (cameraPos.x + scrollDisplacement >= 0 && cameraPos.x + scrollDisplacement <= maxCameraPosX) {
		Level::currentLevel().getLevelAttributes()->cameraPos += glm::vec2(scrollDisplacement, 0);
		scrolled = true;
	}
}