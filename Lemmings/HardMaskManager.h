#ifndef _HARDMASKMANAGER_INCLUDE
#define _HARDMASKMANAGER_INCLUDE

#include "MaskManager.h"

#include <vector>

class HardMaskManager : public MaskManager
{
public:
	
	static HardMaskManager &getInstance()
	{
		static HardMaskManager instance; // Guaranteed to be destroyed.
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

private:
	void regenerateMask(int x, int y);

	std::vector<std::vector<int>> timeWhenDissapear;
	std::vector<std::vector<int>> timeToAppear;
};


#endif // _HARDMASKMANAGER_INCLUDE


