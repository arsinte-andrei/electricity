#include "AtpDbClient.h"
#include "AtpSettings.h"

#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

QSqlDatabase AtpDbClient::clientDB;

QMap<QString, QSqlDatabase> AtpDbClient::clientConnections;

QString AtpDbClient::dbPath = "";
QString AtpDbClient::dbType = "";

bool AtpDbClient::readIniFile(QString connectionName){
	if (readIniDbPath(connectionName) && readIniDbType()){
		return true;
	} else {
		return false;
	}
}

bool AtpDbClient::readIniDbPath(QString connectionName){
	dbPath.clear();
	QString compPath = AtpSettings::getStringValue("Company/Path", "");
	QString mainCompPath = AtpSettings::getCompanyPath(compPath);
	dbPath = mainCompPath + "/" + connectionName.append(".atpdb");
	if (dbFileExist(dbPath)){
		return true;
	} else {
		qCritical() << "Invalid Database Path";
		//TODO a class for saving errors in a file here a big error
		return false;
	}
}

bool AtpDbClient::readIniDbType(){
	dbType = AtpSettings::getStringValue("Db/Type", "QSQLITE");
	if (isDriverAvailable(dbType)){
		return true;
	} else {
		qCritical() << "Invalid Database Type";
		//TODO a class for saving errors in a file here a big error
		return false;
	}
}

bool AtpDbClient::dbFileExist(QString cale){
	qDebug() <<cale;
	QFile db_file(cale);
	if (!db_file.exists()) {
		QMessageBox::critical(0, "Cannot open Client database",
		"Client Database file not found. Try to restore a backup", QMessageBox::Ok);
		return false;
	} else {
		db_file.open(QIODevice::ReadOnly);
		char buf[15];
		db_file.read(buf, sizeof(buf));
		QString sBuf = QString::fromLocal8Bit(buf);
		db_file.close();
		if(sBuf == "SQLite format 3"){
			return true;
		} else {
			QMessageBox::critical(0, "Cannot open Client database",
			"Client Database file found but is not valid. Try to restore one from an early backup!", QMessageBox::Ok);
			return false;
		}
	}
	return false;
}

bool AtpDbClient::isDriverAvailable(QString tip){
	if(!QSqlDatabase::isDriverAvailable(tip)){
		QMessageBox::critical(0, "Driver is not available",
		"Unable to establish a database connection.\n"
		"DataBase driver is not available! Check Database settings", QMessageBox::Cancel);
		return false;
	}
	return true;
}

bool AtpDbClient::setNewConnection(QString connectionName){
	clientDB = QSqlDatabase::addDatabase(dbType, connectionName);
	clientDB.setDatabaseName(dbPath);
	if (!clientDB.open()){
		qCritical() << "couldn't connect to database Error[" << clientDB.lastError().text() << "]"  << dbPath;
		return false;
	} else {
		qDebug() << "succsessfully connected to database " << dbPath;
		return true;
	}
}

bool AtpDbClient::isOpen(QString connectionName){
	if(clientConnections.contains(connectionName)){
		clientDB = clientConnections.value(connectionName);
		return clientDB.isOpen();
	}
	return false;
}

void AtpDbClient::setDataBasePath(QString newPath){
	dbPath = newPath;
	uninit();
}

void AtpDbClient::setDataBaseType(QString newType){
	dbType = newType;
	uninit();
}

QSqlDatabase AtpDbClient::getDataBase(QString connectionName){
	if(clientConnections.contains(connectionName)){
		clientDB = clientConnections.value(connectionName);
		if (!clientDB.isOpen()){
			if(readIniFile(connectionName)){
				setNewConnection(connectionName);
			}
		}
		return clientDB;
	} else {
		if(readIniFile(connectionName)){
			setNewConnection(connectionName);
			clientConnections.insert(connectionName, clientDB);
		}
	}
	return clientDB;
}

bool AtpDbClient::uninit() {
	//TODO se poate sa trebuiasca sa se parcurga tot qmap - de verificat
	clientDB.close();
	QSqlDatabase::removeDatabase(clientDB.connectionName());
	clientConnections.clear();
	if(clientDB.isOpen()){
		return false;
	} else {
		return true;
	}
}

bool AtpDbClient::createClientStructure(QString dbNewPath, QString dbNewFileName, QString dbNewType){
	QSqlDatabase myNewdb;
	if (!isDriverAvailable(dbNewType)){
		return false;
	}
	dbNewPath = dbNewPath + "/" + dbNewFileName.append(".atpdb");
	myNewdb = QSqlDatabase::addDatabase(dbNewType, "clientDbConnection");
	myNewdb.setDatabaseName(dbNewPath);
	if (!myNewdb.open()){
		qCritical() << "couldn't connect to database Error[" << myNewdb.lastError().text() << "]"  << dbPath;
		return false;
	} else {
		qDebug() << "succsessfully connected to database " << dbPath;
	}
	QVector<QString> tables(0);

//	tables.append("CREATE TABLE cl_for_tbl (for_id integer				PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, for_name text);");
//	tables.append("CREATE TABLE cl_group_tbl (group_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, group_place text);");
//	tables.append("CREATE TABLE cl_invoice_tbl (inv_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, inv_quote_id  integer,	inv_date date, inv_for_id integer, inv_value real);");
	tables.append("CREATE TABLE cl_materiale_t ( mat_id integer		PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, mat_name text, mat_price1 real, mat_price2 real, mat_supplier_id  integer);");
//	tables.append("CREATE TABLE cl_plata_tbl (plata_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, plata_detalii  text);");
	tables.append("CREATE TABLE cl_point_price_t ( punct_id integer		PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, punct_name    text, punct_price1  real,  punct_price2  real);");
	tables.append("CREATE TABLE cl_quotation_detail_t (qd_id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, qd_q_id	integer, qd_item_place integer, qd_price_id	integer, qd_quantity1 integer, qd_quantity2 integer, qd_note text);");
//	tables.append("CREATE TABLE cl_quotation_t (q_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, q_client_id integer, q_company_id integer, q_data date, q_price1 real, q_price2 real, q_price3 real, q_mytotal real);");
//	tables.append("CREATE TABLE cl_receipt_t (re_id integer				PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, re_inv_id integer, re_total real, re_client_id integer, re_comp_id integer);");
	tables.append("CREATE TABLE cl_receipt_detail_t (red_id integer	PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, red_re_id integer, red_data date, red_amount real, red_detail integer, red_note text);");

	QSqlQuery myquerry = QSqlQuery(myNewdb);
	for (int i = 0; i < tables.size(); ++i) {
		myquerry.exec(tables[i]);
		qDebug() << myquerry.lastQuery();
		qDebug() << myquerry.lastError();
	}
	clientDB = myNewdb;
	return true;
}
