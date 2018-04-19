#ifndef _JOBFACTORY_INCLUDE
#define _JOBFACTORY_INCLUDE

#include "Job.h"


class JobFactory
{

public:

	static JobFactory &instance()
	{
		static JobFactory instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	};

	Job *createWalkerJob();
	Job *createDiggerJob();
	Job *createEscaperJob();
	Job *createExploderJob();
	Job *createMinerJob();
	Job *createFloaterJob();
	Job *createBasherJob();
	Job *createBlockerJob();
	Job *createFallerJob();
	Job *createClimberJob();
};


#endif // _JOBFACTORY_INCLUDE

