#ifndef _WALKER_INCLUDE
#define _WALKER_INCLUDE


#include "Job.h"


// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Walker : public Job
{

	
protected:
	virtual void initAnims(ShaderProgram &shaderProgram);
	virtual void updateStateMachine(int deltaTime);
	virtual int collisionFloor(int maxFall);
	virtual bool collision();
	
private:
	enum WalkerState
	{
		WALKING_LEFT_STATE, WALKING_RIGHT_STATE, FALLING_LEFT_STATE, FALLING_RIGHT_STATE
	};

private:
	WalkerState state;
};

#endif // _WALKER_INCLUDE


