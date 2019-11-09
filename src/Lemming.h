#ifndef _LEMMING_INCLUDE
#define _LEMMING_INCLUDE


#include "Sprite.h"
#include "Job.h"
#include "Countdown.h"



// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Lemming
{

public:
	Lemming() {};
	Lemming(const glm::vec2 &initialPosition);
	void update(int deltaTime);
	void render();
	void changeJob(Job *nextJob);
	bool isWalkingRight();
	void setWalkingRight(bool value);
	glm::vec2 &getPosition();
	bool dead();
	bool saved();
	Job *getJob();

	void writeDestiny();

private:
	Job *job;
	Sprite *sprite;
	Countdown *countdown;
	ShaderProgram *shaderProgram;
	bool walkingRight = true; // is marked true when the lemmings walks in right direction
	bool alive;
	bool isSaved;
	glm::vec2 position;

	bool outOfMap();

};

#endif // _LEMMING_INCLUDE

