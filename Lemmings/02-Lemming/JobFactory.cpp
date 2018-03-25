#include <iostream>
#include "JobFactory.h"
#include "Walker.h"
#include "Digger.h"





Job* JobFactory::createWalkerJob()
{
	Walker *walkerJob = new Walker();
	return walkerJob;
}

Job* JobFactory::createDiggerJob()
{
	Digger *diggerJob = new Digger();
	return diggerJob;
}
