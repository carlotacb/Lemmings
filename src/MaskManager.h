#ifndef _MASKMANAGER_INCLUDE
#define _MASKMANAGER_INCLUDE

class MaskManager
{
public:
	virtual void init() = 0;
	virtual void update() = 0;

	virtual void eraseMask(int x, int y) = 0; 
	virtual void applyMask(int x, int y) = 0;
	virtual void eraseSpecialMask(int x, int y) = 0;
	virtual void applySpecialMask(int x, int y) = 0;
	virtual char getPixel(int x, int y) = 0;

};


#endif // _MASKMANAGER_INCLUDE



