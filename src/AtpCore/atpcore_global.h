#ifndef ATPCORE_GLOBAL_H
#define ATPCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ATP_LIBRARY)
#	if defined(ATPCORE_LIBRARY)
#		define ATPCORE_EXPORT Q_DECL_EXPORT
#	else
#		define ATPCORE_EXPORT Q_DECL_IMPORT
#	endif
#else
#	define ATPCORE_EXPORT
#endif

#endif // ATPCORE_GLOBAL_H
