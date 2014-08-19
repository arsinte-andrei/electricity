#include "AtpDbComp.h"
#include "AtpSettings.h"

#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

QSqlDatabase AtpDbComp::companyDb;

QString AtpDbComp::dbPath = "";
QString AtpDbComp::dbType = "";

bool AtpDbComp::readIniFile(){
	if (readIniDbPath() && readIniDbType()){
		return true;
	} else {
		return false;
	}
}

bool AtpDbComp::readIniDbPath(){
	dbPath.clear();
	QString compPath = AtpSettings::getStringValue("Company/Path", "");
	QString mainCompPath = AtpSettings::getCompanyPath(compPath);
	dbPath = mainCompPath + "/" + compPath.append(".atpdb");
	if (dbFileExist(dbPath)){
		return true;
	} else {
		qCritical() << "Invalid Database Path";
		//TODO a class for saving errors in a file here a big error
		return false;
	}
}

bool AtpDbComp::readIniDbType(){
	dbType = AtpSettings::getStringValue("Db/Type", "QSQLITE");
	if (isDriverAvailable(dbType)){
		return true;
	} else {
		qCritical() << "Invalid Database Type";
		//TODO a class for saving errors in a file here a big error
		return false;
	}
}

bool AtpDbComp::dbFileExist(QString cale){
	qDebug() <<cale;
	QFile db_file(cale);
	if (!db_file.exists()) {
		QMessageBox::critical(0, "Cannot open Company database",
		"Company Database file not found. Restore from an early backup!", QMessageBox::Ok);
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
			QMessageBox::critical(0, "Cannot open Company database",
			"Company Database file found but is not valid. Restore from an early backup!", QMessageBox::Ok);
			return false;
		}
	}
	return false;
}

bool AtpDbComp::isDriverAvailable(QString tip){
	if(!QSqlDatabase::isDriverAvailable(tip)){
		QMessageBox::critical(0, "Driver is not available",
		"Unable to establish a database connection.\n"
		"DataBase driver is not available! Check Database settings", QMessageBox::Cancel);
		return false;
	}
	return true;
}

bool AtpDbComp::setNewConnection(){
	companyDb = QSqlDatabase::addDatabase(dbType, "compDbConnection");
	companyDb.setDatabaseName(dbPath);
	if (!companyDb.open()){
		qCritical() << "couldn't connect to database Error[" << companyDb.lastError().text() << "]"  << dbPath;
		return false;
	} else {
		qDebug() << "succsessfully connected to database " << dbPath;
		return true;
	}
}

bool AtpDbComp::isOpen(){
	return companyDb.isOpen();
}

void AtpDbComp::setDataBasePath(QString newPath){
	dbPath = newPath;
	uninit();
}

void AtpDbComp::setDataBaseType(QString newType){
	dbType = newType;
	uninit();
}

QSqlDatabase AtpDbComp::getDataBase(){
	if (!companyDb.isOpen()){
		if(readIniFile()){
			setNewConnection();
		}
	}
	return companyDb;
}

bool AtpDbComp::uninit() {
	companyDb.close();
	QSqlDatabase::removeDatabase(companyDb.connectionName());
	if(companyDb.isOpen()){
		return false;
	} else {
		return true;
	}
}

bool AtpDbComp::createCompanyStructure(QString dbNewPath, QString dbNewFileName, QString dbNewType){
	QSqlDatabase myNewdb;
	if (!isDriverAvailable(dbNewType)){
		return false;
	}
	dbNewPath = dbNewPath + "/" + dbNewFileName.append(".atpdb");
	myNewdb = QSqlDatabase::addDatabase(dbNewType, "compDbConnection");
	myNewdb.setDatabaseName(dbNewPath);
	if (!myNewdb.open()){
		qCritical() << "couldn't connect to database Error[" << myNewdb.lastError().text() << "]"  << dbPath;
		return false;
	} else {
		qDebug() << "succsessfully connected to database " << dbPath;
	}
	QVector<QString> tables(0);

	tables.append("CREATE TABLE comp_client_list_t(client_id integer	PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, client_name text, client_address text, client_tel text, client_mob text, client_email text, client_file text);");
//	tables.append("CREATE TABLE comp_for_t (for_id integer				PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, for_name text);");
//	tables.append("CREATE TABLE comp_group_t (group_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, group_place text);");
//	tables.append("CREATE TABLE comp_invoice_t (inv_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, inv_quote_id  integer,	inv_date date, inv_for_id integer, inv_value real);");
	tables.append("CREATE TABLE comp_materiale_t ( mat_id integer		PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, mat_name text, mat_price1 real, mat_price2 real, mat_supplier_id  integer);");
//	tables.append("CREATE TABLE comp_plata_t (plata_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, plata_detalii  text);");
	tables.append("CREATE TABLE comp_point_price_t ( punct_id integer		PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, punct_name    text, punct_price1  real,  punct_price2  real);");
//	tables.append("CREATE TABLE comp_quotation_detail_t (qd_id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, qd_q_id	integer, qd_item_place integer, qd_price_id	integer, qd_quantity1 integer, qd_quantity2 integer, qd_note text);");
//	tables.append("CREATE TABLE comp_quotation_t (q_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, q_client_id integer, q_company_id integer, q_data date, q_price1 real, q_price2 real, q_price3 real, q_mytotal real);");
//	tables.append("CREATE TABLE comp_receipt_t (re_id integer				PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, re_inv_id integer, re_total real, re_client_id integer, re_comp_id integer);");
//	tables.append("CREATE TABLE comp_receipt_detail_t (red_id integer	PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, red_re_id integer, red_data date, red_amount real, red_detail integer, red_note text);");
	tables.append("CREATE TABLE comp_supplier_t (supplier_id integer	PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, supplier_name text, supplier_addres text, supplier_telephon text, supplier_mob text, supplier_email text, supplier_web text);");
	QSqlQuery myquerry = QSqlQuery(myNewdb);
	for (int i = 0; i < tables.size(); ++i) {
		myquerry.exec(tables[i]);
		qDebug() << myquerry.lastQuery();
		qDebug() << myquerry.lastError();
	}
	companyDb = myNewdb;
	return true;
}

