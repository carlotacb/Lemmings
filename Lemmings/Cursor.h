#ifndef _CURSOR_INCLUDE
#define _CURSOR_INCLUDE


#include "Sprite.h"

class Cursor
{
public:
	static Cursor &getInstance()
	{
		static Cursor instance; // Guaranteed to be destroyed.
									   // Instantiated on first use.
		return instance;
	};

	void init();
	void render();
	void setPosition(glm::vec2 position);
	void setScrollLeftCursor();
	void setScrollRightCursor();
	void setFocusCursor();
	void setCrossCursor();

private:
	glm::vec2 position;
	Sprite *cursorSprite;
};


#endif // _BLOCKER_INCLUDE



