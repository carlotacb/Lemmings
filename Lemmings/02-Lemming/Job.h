#ifndef _JOB_INCLUDE
#define _JOB_INCLUDE

#include "Sprite.h"

// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Job
{

public:
	virtual void updateStateMachine(int deltaTime) = 0;
	virtual int collisionFloor(int maxFall) = 0;
	virtual bool collision() = 0;
	virtual void initAnims(ShaderProgram &shaderProgram) = 0;
	bool finished();
	Job* getNextJob();
	Sprite *getJobSprite();

protected:
	Sprite *jobSprite;
	bool isFinished;
	Job *nextJob;

};

#endif // _JOB_INCLUDE


