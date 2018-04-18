#ifndef _DIGGER_INCLUDE
#define _DIGGER_INCLUDE


#include "Job.h"


// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Digger: public Job
{
public:
	void initAnims(ShaderProgram &shaderProgram);
	void updateStateMachine(int deltaTime);
	void setWalkingRight(bool value);
	string getName();

private:
	void dig();

private:
	enum DiggerState
	{
		FALLING_LEFT_STATE, FALLING_RIGHT_STATE, DIGGING_STATE 
	};


private:
	DiggerState state;
};


#endif // _DIGGER_INCLUDE


