#ifndef ATPSQLQUERY_H
#define ATPSQLQUERY_H

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>
#include <QMap>
#include <QVariant>

#include "atpcore_global.h"

class ATPCORE_EXPORT AtpSqlQuery {
	public:
		static QSqlDatabase getDbConnection(QString connectionName);

		static QSqlQuery atpCreateView(QString dbName, QString sqlQuerry);
		static QSqlQuery atpDeleteView(QString dbName, QString viewName);

		static QSqlQuery quotationDetailView(QString dbName, int qId);
		static QSqlQuery quotationView(QString dbName);

		static QSqlQuery atpSelect(QString dbName, QString sqlQuerry, QMap<QString, QVariant> *myArray = NULL);
		static QSqlQuery atpInsert(QString dbName, QString tableName, QMap<QString, QVariant> *data);
		static QSqlQuery atpUpdate(QString dbName, QString tableName, QMap<QString, QVariant> *data, QString whereTo);
		static QSqlQuery atpDelete(QString dbName, QString tableName, QString whereTo);

};

#endif // ATPSQLQUERY_H
