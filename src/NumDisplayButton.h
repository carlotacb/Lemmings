#ifndef _NUMDISPLAYBUTTON_INCLUDE
#define _NUMDISPLAYBUTTON_INCLUDE

#include "NumDisplay.h"

class NumDisplayButton : public NumDisplay
{
	public:
		void setPosition(glm::vec2 position);

	private:
		void initAux();
		void displayNumAux(int firstDigit, int secondDigit);

};

#endif // _NUMDISPLAYBUTTON_INCLUDE


