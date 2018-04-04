#ifndef _MINER_INCLUDE
#define _MINER_INCLUDE


#include "Job.h"


// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Miner : public Job
{
public:
	void initAnims(ShaderProgram &shaderProgram);
	void updateStateMachine(int deltaTime);

private:
	void mine_right();
	void mine_left();

private:
	enum MinerState
	{
		FALLING_LEFT_STATE, FALLING_RIGHT_STATE, MINER_RIGHT_STATE, MINER_LEFT_STATE
	};


private:
	MinerState state;
};


#endif // _MINER_INCLUDE