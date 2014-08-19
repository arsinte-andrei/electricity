#ifndef ATPDBMAIN_H
#define ATPDBMAIN_H

#include "atpcore_global.h"

#include <QSqlDatabase>

class ATPCORE_EXPORT AtpDbMain {

	private:
		static QSqlDatabase mydb;
		static QString dbPath, dbType;

	public:
		static QSqlDatabase getDataBase();
		static bool uninit();

		static bool readIniFile();
		static bool readIniDbPath();
		static bool readIniDbType();
		static bool dbFileExist(QString cale);
		static bool createMainSQLiteDb(QString dbNewPath, QString dbNewType = "QSQLITE");

		static bool setNewConnection();
		static bool isOpen();
		static bool isDriverAvailable(QString tip);
		static void setDataBasePath(QString newPath);
		static void setDataBaseType(QString newType);
};

#endif // ATP_DB_H
