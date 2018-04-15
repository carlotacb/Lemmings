#ifndef _FLOATER_INCLUDE
#define _FLOATER_INCLUDE


#include "Job.h"


class Floater: public Job
{
public:
	void initAnims(ShaderProgram &shaderProgram);
	void updateStateMachine(int deltaTime);
	void setWalkingRight(bool value);

private:
	void timeToFloat();

private:
	enum FloaterState
	{
		WALKING_RIGHT_STATE, WALKING_LEFT_STATE, FALLING_LEFT_STATE, FALLING_RIGHT_STATE, FLOTATING_RIGHT_STATE, FLOTATING_LEFT_STATE, FLOATER_OPENING_RIGHT_STATE, FLOATER_OPENING_LEFT_STATE
	};


private:
	FloaterState state;
};


#endif // _FLOATER_INCLUDE


