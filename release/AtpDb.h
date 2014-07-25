#ifndef ATPDB_H
#define ATPDB_H

#include <QMap>
#include <QVariant>
#include <QSqlDatabase>
#include <QObject>

#include "AtpSettings.h"

class ATPCORE_EXPORT AtpDb : public QSqlDatabase{
	private:
		static QSqlDatabase *mydb;
		static bool openStatus;
		static QString dbPath, dbType;

	public:
		static QSqlDatabase *getDataBase();
		static void uninit();

		static bool readIniFile();
		static bool dbFileExist(QString cale);
		static bool createSQLiteDb(QString dbNewPath, QString dbNewType = "QSQLITE");

		static QSqlQuery *atpCreateView(QString sqlQuerry);
		static QSqlQuery *atpDeleteView(QString viewName);

		static QSqlQuery *atpSelect(QString sqlQuerry, QMap<QString, QVariant> *myArray = NULL);
		static QSqlQuery *atpInsert(QString tableName, QMap<QString, QVariant> *data );
		static QSqlQuery *atpUpdate(QString tableName, QMap<QString, QVariant> *data, QString whereTo);
		static QSqlQuery *atpDelete(QString tableName, QString whereTo);

		static QSqlQuery *quotationDetailView(int qId);
		static QSqlQuery *quotationView();
		static bool setNewConnection();
		static bool isOpen();
		static bool isDriverAvailable(QString tip);
		static void setDataBasePath(QString newPath);
		static void setDataBaseType(QString newType);
};

#endif // ATP_DB_H
