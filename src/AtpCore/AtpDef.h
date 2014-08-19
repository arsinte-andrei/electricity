#ifndef ATPDEF_H
#define ATPDEF_H

#include "atpcore_global.h"

class ATPCORE_EXPORT AtpDef {
	public:

		enum mainWindowLoadingStatus {
			allLoadedOk,
			noDataBaseLoaded,
			noCompanyLoaded,
			noClientLoaded
		};

};

#endif // ATPDEF_H
