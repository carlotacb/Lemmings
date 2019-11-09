#ifndef _BASHER_INCLUDE
#define _BASHER_INCLUDE


#include "Job.h"


class Basher : public Job
{
public:
	void initAnims(ShaderProgram &shaderProgram);
	void updateStateMachine(int deltaTime);
	void setWalkingRight(bool value);
	string getName();

private:
	bool bashRight();
	bool bashLeft();

private:
	enum BasherState
	{
		BASHING_RIGHT_STATE, BASHING_LEFT_STATE
	};


private:
	BasherState state;
};


#endif // _BASHER_INCLUDE



