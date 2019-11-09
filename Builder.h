#ifndef _BUILDER_INCLUDE
#define _BUILDER_INCLUDE


#include "Job.h"

#define MAX_STEPS 12


class Builder : public Job
{

	
public:
	void initAnims(ShaderProgram &shaderProgram);
	void updateStateMachine(int deltaTime);
	void setWalkingRight(bool value);
	string getName();
	
private:
	enum BuilderState
	{
		BUILDING_LEFT_STATE, BUILDING_RIGHT_STATE, NOSTEPS_STATE
	};

private:
	BuilderState state;

	void buildLeft();
	void buildRight();

	bool cannotBuildRight();
	bool cannotBuildLeft();

	int buildedSteps = 0;
	
};

#endif // _BUILDER_INCLUDE


