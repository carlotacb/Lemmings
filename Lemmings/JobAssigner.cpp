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
		if (Scene::getInstance().assignJob(lemmingIndex, jobToAssign)) {
			jobToAssign = NULL;

			decreaseOfferedJobCount();

			if (getJobCount(lastOfferedJob) > 0) {
				offerJob(lastOfferedJob);
			}
			else {
				lastOfferedJob = NONE;

			}
		}
	}
}

void JobAssigner::decreaseOfferedJobCount() 
{

	--Level::currentLevel().getLevelAttributes()->jobCount[jobNameToIndex(lastOfferedJob)];
	
}

int JobAssigner::getJobCount(JobNames jobName)
{
	
	return Level::currentLevel().getLevelAttributes()->jobCount[jobNameToIndex(jobName)];

}

int JobAssigner::jobNameToIndex(JobNames jobName)
{
	int index;
	switch (jobName)
	{
		case JobAssigner::BASHER:
			index = 5;
			break;
		case JobAssigner::BLOCKER:
			index = 3;
			break;
		case JobAssigner::BOMBER:
			index = 2;
			break;
		case JobAssigner::BUILDER:
			index = 4;
			break;
		case JobAssigner::CLIMBER:
			index = 0;
			break;
		case JobAssigner::DIGGER:
			index = 7;
			break;
		case JobAssigner::FLOATER:
			index = 1;
			break;
		case JobAssigner::MINER:
			index = 6;
			break;
		case JobAssigner::NONE:
			index = -1;
			break;
	}

	return index;
}