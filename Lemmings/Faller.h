#ifndef _FALLER_INCLUDE
#define _FALLER_INCLUDE


#include "Job.h"

class Faller: public Job
{
public:
	void initAnims(ShaderProgram &shaderProgram);
	void updateStateMachine(int deltaTime);
	void setWalkingRight(bool value);
	string getName();


private:
	enum FallerState
	{
		FALLING_LEFT_STATE, FALLING_RIGHT_STATE, FALLING_DEATH_STATE
	};


private:
	FallerState state;
};


#endif // _FALLER_INCLUDE


