#ifndef _NUMDISPLAYGREEN_INCLUDE
#define _NUMDISPLAYGREEN_INCLUDE

#include "NumDisplay.h"

class NumDisplayGreen : public NumDisplay
{
public:
	void setPosition(glm::vec2 position);

private:
	void displayNumAux(int firstDigit, int secondDigit);

};

#endif // _NUMDISPLAYGREEN_INCLUDE


