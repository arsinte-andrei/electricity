#ifndef ATPTOOLS_GLOBAL_H
#define ATPTOOLS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ATP_LIBRARY)
#	if defined(ATPTOOLS_LIBRARY)
#		define ATPTOOLS_EXPORT Q_DECL_EXPORT
#	else
#		define ATPTOOLS_EXPORT Q_DECL_IMPORT
#	endif
#else
#	define ATPTOOLS_EXPORT
#endif

#endif // ATPTOOLS_GLOBAL_H
