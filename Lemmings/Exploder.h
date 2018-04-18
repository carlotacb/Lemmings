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
		EXPLODER_STATE
	};


private:
	ExploderState state;
};


#endif // _EXPLODER_INCLUDE



