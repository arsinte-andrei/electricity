#ifndef ATPCOMPANY_GLOBAL_H
#define ATPCOMPANY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ATP_LIBRARY)
#	if defined(ATPCOMPANY_LIBRARY)
#		define ATPCOMPANY_EXPORT Q_DECL_EXPORT
#	else
#		define ATPCOMPANY_EXPORT Q_DECL_IMPORT
#	endif
#else
#	define ATPCOMPANY_EXPORT
#endif

#endif // ATPCOMPANY_GLOBAL_H
