#ifndef _LEMMING_INCLUDE
#define _LEMMING_INCLUDE


#include "Sprite.h"
#include "Job.h"



// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Lemming
{

public:
	void init(Job *job, const glm::vec2 &initialPosition);
	void update(int deltaTime);
	void render();
	void changeJob(Job *nextJob);

private:
	Job *job;
	Sprite *sprite;
	ShaderProgram *shaderProgram;
};

#endif // _LEMMING_INCLUDE

