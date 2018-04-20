#ifndef _DIGGER_INCLUDE
#define _DIGGER_INCLUDE


#include "Job.h"


class Digger: public Job
{
public:
	void initAnims(ShaderProgram &shaderProgram);
	void updateStateMachine(int deltaTime);
	void setWalkingRight(bool value);
	string getName();

private:
	void dig();
	bool canDig();
private:
	enum DiggerState
	{
		DIGGING_STATE 
	};


private:
	DiggerState state;
	bool firstTime = true;
};


#endif // _DIGGER_INCLUDE


