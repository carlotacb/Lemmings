#ifndef _BASHER_INCLUDE
#define _BASHER_INCLUDE


#include "Job.h"


// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Basher : public Job
{
public:
	void initAnims(ShaderProgram &shaderProgram);
	void updateStateMachine(int deltaTime);
	void setWalkingRight(bool value);

private:
	void bash_right();
	void bash_left();

private:
	enum BasherState
	{
		FALLING_LEFT_STATE, FALLING_RIGHT_STATE, BASHING_RIGHT_STATE, BASHING_LEFT_STATE
	};


private:
	BasherState state;
};


#endif // _DIGGER_INCLUDE



