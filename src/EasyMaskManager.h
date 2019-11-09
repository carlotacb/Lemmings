#ifndef _EASYMASKMANAGER_INCLUDE
#define _EASYMASKMANAGER_INCLUDE

#include "MaskManager.h"

class EasyMaskManager : public MaskManager
{
public:
	static EasyMaskManager &getInstance()
	{
		static EasyMaskManager instance; // Guaranteed to be destroyed.
										 // Instantiated on first use.
		return instance;
	};

	void init();
	void update();

	void eraseMask(int x, int y);
	void applyMask(int x, int y);
	void eraseSpecialMask(int x, int y);
	void applySpecialMask(int x, int y);
	char getPixel(int x, int y);

};


#endif // _EASYMASKMANAGER_INCLUDE



