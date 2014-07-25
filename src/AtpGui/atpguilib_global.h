#ifndef ATPGUILIB_GLOBAL_H
#define ATPGUILIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ATP_LIBRARY)
#	if defined(ATPGUI_LIBRARY)
#		define ATPGUILIB_EXPORT Q_DECL_EXPORT
#	else
#		define ATPGUILIB_EXPORT Q_DECL_IMPORT
#	endif
#else
#	define ATPGUILIB_EXPORT
#endif

#endif // ATPGUILIB_GLOBAL_H
