#ifndef _MOUSEMANAGER_INCLUDE
#define _MOUSEMANAGER_INCLUDE


class MouseManager
{

public:

	virtual void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) = 0;


private:
	int posX, posY;

};
#endif // _MOUSEMANAGER_INCLUDE

