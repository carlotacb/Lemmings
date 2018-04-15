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


	
};


#endif // _JOBFACTORY_INCLUDE

