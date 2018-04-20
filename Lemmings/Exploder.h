#ifndef _EXPLODER_INCLUDE
#define _EXPLODER_INCLUDE


#include "Job.h"


class Exploder : public Job
{
public:
	void initAnims(ShaderProgram &shaderProgram);
	void updateStateMachine(int deltaTime);
	void setWalkingRight(bool value);
	string getName();

private:
	enum ExploderState
	{
		EXPLODER_STATE,
		BURNING_DEATH_STATE
	};


private:
	ExploderState state;
	void explode();
};


#endif // _EXPLODER_INCLUDE



