#ifndef ATPDBSTRUCTURE_H
#define ATPDBSTRUCTURE_H

#include "atpcore_global.h"

#include <QStringList>

class ATPCORE_EXPORT AtpDbStructure{
	public:
		static QStringList getAllDatabases();
		static QString getDbName(QString dbName);
		static QStringList getTableList(QString dbName);
		static QString getTableName(QString );

		struct db_t{
				QStringList dbNames;
				struct dbMain_t{
						QStringList tableNames;
						QString dbName;
				}dbMainStructure;
		} AtpdbStructure;
};

#endif // ATPDBSTRUCTURE_H


/*
db[main] = table[] =
		 = table[] =
db[comp] = table[] =
		 = table[] =
db[client] = table[] =
*/
