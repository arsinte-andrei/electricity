#ifndef ATPDBCLIENT_H
#define ATPDBCLIENT_H

#include <QSqlDatabase>

#include "atpcore_global.h"

class ATPCORE_EXPORT AtpDbClient {

	private:
		static QSqlDatabase clientDB;
		static QString dbPath, dbType;

	public:
		static QSqlDatabase getDataBase();
		static bool uninit();

		static bool readIniFile();
		static bool readIniDbPath();
		static bool readIniDbType();
		static bool dbFileExist(QString cale);
		static bool createClientStructure(QString dbNewPath, QString dbNewFileName, QString dbNewType = "QSQLITE");

		static bool setNewConnection();
		static bool isOpen();
		static bool isDriverAvailable(QString tip);
		static void setDataBasePath(QString newPath);
		static void setDataBaseType(QString newType);

};

#endif // ATPDBCLIENT_H
