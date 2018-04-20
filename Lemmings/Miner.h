#ifndef _MINER_INCLUDE
#define _MINER_INCLUDE


#include "Job.h"



class Miner : public Job
{
public:
	void initAnims(ShaderProgram &shaderProgram);
	void updateStateMachine(int deltaTime);
	void setWalkingRight(bool value);
	string getName();

private:
	void printMine();
	
	void mineRight();
	bool canMineRight();

	void mineLeft();
	bool canMineLeft();

private:
	enum MinerState
	{
		MINER_RIGHT_STATE, MINER_LEFT_STATE
	};


private:
	MinerState state;
};


#endif // _MINER_INCLUDE