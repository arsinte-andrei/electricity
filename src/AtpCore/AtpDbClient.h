#ifndef ATPDBCLIENT_H
#define ATPDBCLIENT_H

#include <QSqlDatabase>
#include <QMap>

#include "atpcore_global.h"

class ATPCORE_EXPORT AtpDbClient {

	private:
		static QSqlDatabase clientDB;
		static QString dbPath, dbType;
		static QMap<QString, QSqlDatabase> clientConnections;

	public:
		static QSqlDatabase getDataBase(QString connectionName);
		static bool uninit();

		static bool readIniFile(QString connectionName);
		static bool readIniDbPath(QString connectionName);
		static bool readIniDbType();
		static bool dbFileExist(QString cale);
		static bool createClientStructure(QString dbNewPath, QString dbNewFileName, QString dbNewType = "QSQLITE");

		static bool setNewConnection(QString connectionName);
		static bool isOpen(QString connectionName);
		static bool isDriverAvailable(QString tip);
		static void setDataBasePath(QString newPath);
		static void setDataBaseType(QString newType);

};

#endif // ATPDBCLIENT_H
