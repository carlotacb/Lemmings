#include <iostream>
#include "JobFactory.h"
#include "Walker.h"
#include "Digger.h"
#include "Escaper.h"
#include "Exploder.h"
#include "Miner.h"
#include "Floater.h"
#include "Basher.h"
#include "Blocker.h"
#include "Faller.h"

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

Job* JobFactory::createEscaperJob()
{
	Escaper *escaperJob = new Escaper();
	return escaperJob;
}

Job* JobFactory::createExploderJob()
{
	Exploder *exploderJob = new Exploder();
	return exploderJob;
}

Job* JobFactory::createMinerJob()
{
	Miner *minerJob = new Miner();
	return minerJob;
}

Job* JobFactory::createFloaterJob()
{
	Floater *floaterJob = new Floater();
	return floaterJob;
}

Job* JobFactory::createBasherJob()
{
	Basher *basherJob = new Basher();
	return basherJob;
}

Job* JobFactory::createBlockerJob()
{
	Blocker *blockerJob = new Blocker();
	return blockerJob;
}

Job* JobFactory::createFallerJob()
{
	Faller *fallerJob = new Faller();
	return fallerJob;
}

