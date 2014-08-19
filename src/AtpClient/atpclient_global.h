#ifndef ATPCLIENT_GLOBAL_H
#define ATPCLIENT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ATP_LIBRARY)
#	if defined(ATPCLIENT_LIBRARY)
#		define ATPCLIENT_EXPORT Q_DECL_EXPORT
#	else
#		define ATPCLIENT_EXPORT Q_DECL_IMPORT
#	endif
#else
#	define ATPCLIENT_EXPORT
#endif

#endif // ATPCLIENT_GLOBAL_H
