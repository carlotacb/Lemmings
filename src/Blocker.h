#ifndef _BLOCKER_INCLUDE
#define _BLOCKER_INCLUDE


#include "Job.h"


// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Blocker : public Job
{
public:
	void initAnims(ShaderProgram &shaderProgram);
	void updateStateMachine(int deltaTime);
	void setWalkingRight(bool value);
	string getName();

private:
	enum BlockerState
	{
		BLOCKING_STATE
	};


private:
	BlockerState state;
};


#endif // _BLOCKER_INCLUDE



