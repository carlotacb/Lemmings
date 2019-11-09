#ifndef _ESCAPER_INCLUDE
#define _ESCAPER_INCLUDE


#include "Job.h"
#include "SoundManager.h"


class Escaper : public Job
{
public:
	void initAnims(ShaderProgram &shaderProgram);
	void updateStateMachine(int deltaTime);
	void setWalkingRight(bool value);
	string getName();

private:
	enum EscaperState
	{
		ESCAPING_STATE
	};


private:
	EscaperState state;
	const SoundManager* soundManager;
	FMOD::Sound* escapeEfect;
};


#endif // _ESCAPER_INCLUDE


