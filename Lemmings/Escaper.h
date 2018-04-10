#ifndef _ESCAPER_INCLUDE
#define _ESCAPER_INCLUDE


#include "Job.h"


class Escaper : public Job
{
public:
	void initAnims(ShaderProgram &shaderProgram);
	void updateStateMachine(int deltaTime);
	void setWalkingRight(bool value);


private:
	enum EscaperState
	{
		ESCAPING_STATE
	};


private:
	EscaperState state;
};


#endif // _ESCAPER_INCLUDE


