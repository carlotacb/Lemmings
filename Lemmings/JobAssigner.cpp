#include "JobAssigner.h"
#include "JobFactory.h"
#include "Scene.h"

void JobAssigner::deleteJobToAssign()
{
	delete jobToAssign;
	jobToAssign = NULL;
	lastOfferedJob = NONE;

}

void JobAssigner::offerJob(JobNames jobName)
{

	deleteJobToAssign();

	switch (jobName) {
		case JobAssigner::BASHER:
			jobToAssign = JobFactory::instance().createBasherJob();
			break;
		case JobAssigner::BLOCKER:
			jobToAssign = JobFactory::instance().createBlockerJob();
			break;
		case JobAssigner::BOMBER:
			jobToAssign = JobFactory::instance().createExploderJob();
			break;
		case JobAssigner::BUILDER:
			jobToAssign = JobFactory::instance().createBuilderJob();
			break;
		case JobAssigner::CLIMBER:
			jobToAssign = JobFactory::instance().createClimberJob();
			break;
		case JobAssigner::DIGGER:
			jobToAssign = JobFactory::instance().createDiggerJob();
			break;
		case JobAssigner::FALLER:
			jobToAssign = JobFactory::instance().createBasherJob();
			break;
		case JobAssigner::FLOATER:
			jobToAssign = JobFactory::instance().createFloaterJob();
			break;
		case JobAssigner::MINER:
			jobToAssign = JobFactory::instance().createMinerJob();
			break;
		case JobAssigner::WALKER:
			jobToAssign = JobFactory::instance().createWalkerJob();
			break;
		default:
			break;
	} 

	lastOfferedJob = jobName;
}

bool JobAssigner::hasJobToAssign()
{
	return lastOfferedJob != NONE;
}

void JobAssigner::assigJobLemming(int lemmingIndex)
{
	if (lemmingIndex != -1) {
		Scene::getInstance().assignJob(lemmingIndex, jobToAssign);
		jobToAssign = NULL;
		offerJob(lastOfferedJob);
	}
}

