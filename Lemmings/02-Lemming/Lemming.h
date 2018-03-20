#ifndef _LEMMING_INCLUDE
#define _LEMMING_INCLUDE


#include "Sprite.h"
#include "VariableTexture.h"


// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.


class Lemming
{

public:
	void init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setMapMask(VariableTexture *mapMask);
	
protected:
	virtual void initAnims(ShaderProgram &shaderProgram);
	virtual void updateStateMachine();
	virtual int collisionFloor(int maxFall);
	virtual bool collision();
	
private:
	enum LemmingState
	{
		WALKING_LEFT_STATE, WALKING_RIGHT_STATE, FALLING_LEFT_STATE, FALLING_RIGHT_STATE
	};

protected:
	Texture spritesheet;
	Sprite *sprite;
	VariableTexture *mask;

private:
	LemmingState state;
};




#endif // _LEMMING_INCLUDE


