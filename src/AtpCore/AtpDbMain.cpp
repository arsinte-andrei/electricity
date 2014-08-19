#include "AtpDbMain.h"
#include "AtpSettings.h"

#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

QSqlDatabase AtpDbMain::mydb;

QString AtpDbMain::dbPath = "";
QString AtpDbMain::dbType = "";

bool AtpDbMain::readIniFile(){
	if (readIniDbPath() && readIniDbType()){
		return true;
	} else {
		return false;
	}
}

bool AtpDbMain::readIniDbPath(){
	dbPath = AtpSettings::getStringValue("Db/Path", "");
	if (dbFileExist(dbPath)){
		return true;
	} else {
		qCritical() << "Invalid Database Path";
		//TODO a class for saving errors in a file here a big error
		return false;
	}
}

bool AtpDbMain::readIniDbType(){
	dbType = AtpSettings::getStringValue("Db/Type", "QSQLITE");
	if (isDriverAvailable(dbType)){
		return true;
	} else {
		qCritical() << "Invalid Database Type";
		//TODO a class for saving errors in a file here a big error
		return false;
	}
}

bool AtpDbMain::dbFileExist(QString cale){
	qDebug() <<cale;
	QFile db_file(cale);
	if (!db_file.exists()) {
		QMessageBox::critical(0, "Cannot open Main database",
		"Main Database file not found. Create or import one in Tools Settings!", QMessageBox::Ok);
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
			QMessageBox::critical(0, "Cannot open Main database",
			"Main Database file found but is not valid. Create or import one in Tools Settings!", QMessageBox::Ok);
			return false;
		}
	}
	return false;
}

bool AtpDbMain::isDriverAvailable(QString tip){
	if(!QSqlDatabase::isDriverAvailable(tip)){
		QMessageBox::critical(0, "Driver is not available",
		"Unable to establish a database connection.\n"
		"DataBase driver is not available! Check Database settings", QMessageBox::Cancel);
		return false;
	}
	return true;
}

bool AtpDbMain::setNewConnection(){
	mydb = QSqlDatabase::addDatabase(dbType, "mainDbConnection");
	mydb.setDatabaseName(dbPath);
	if (!mydb.open()){
		qCritical() << "couldn't connect to database Error[" << mydb.lastError().text() << "]"  << dbPath;
		return false;
	} else {
		qDebug() << "succsessfully connected to database " << dbPath;
		return true;
	}
}

bool AtpDbMain::isOpen(){
	return mydb.isOpen();
}

void AtpDbMain::setDataBasePath(QString newPath){
	dbPath = newPath;
	uninit();
}

void AtpDbMain::setDataBaseType(QString newType){
	dbType = newType;
	uninit();
}

bool AtpDbMain::createMainSQLiteDb(QString dbNewPath, QString dbNewType) {
	uninit();
	QSqlDatabase myNewdb;
	if (!isDriverAvailable(dbNewType)){
		return false;
	}
	myNewdb = QSqlDatabase::addDatabase(dbNewType, "mainDbConnection");
	qDebug() << dbNewType;
	myNewdb.setDatabaseName(dbNewPath);
	if (!myNewdb.open()){
		qCritical() << "couldn't connect to database Error[" << myNewdb.lastError().text() << "]"  << dbPath;
		return false;
	} else {
		qDebug() << "succsessfully connected to database " << dbPath;
	}
	qDebug() << "DB 1";
	QVector<QString> tables(0);
	tables.append("CREATE TABLE m_login_t (login_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, login_username  text, login_password  text);");
	tables.append("CREATE TABLE m_company_t (comp_id INTEGER		PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, comp_name text, comp_addres text, comp_www text, comp_director text, comp_tel text, comp_mob text, comp_email text, comp_file text);");
//	tables.append("CREATE TABLE m_client_list_tbl(client_id integer	PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, client_name text, client_address text, client_tel text, client_mob text, client_email text, client_file text);");
//	tables.append("CREATE TABLE m_for_tbl (for_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, for_name text);");
	tables.append("CREATE TABLE m_group_place_t (group_id integer	PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, group_place text, group_parent integer);");
//	tables.append("CREATE TABLE m_invoice_tbl (inv_id integer		PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, inv_quote_id  integer,	inv_date date, inv_for_id integer, inv_value real);");
//	tables.append("CREATE TABLE m_materiale_tbl ( mat_id integer	PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, mat_name text, mat_price1 real, mat_price2 real, mat_supplier_id  integer);");
//	tables.append("CREATE TABLE m_plata_tbl (plata_id integer		PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, plata_detalii  text);");
//	tables.append("CREATE TABLE m_punct_price ( punct_id integer	PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, punct_name    text, punct_price1  real,  punct_price2  real);");
//	tables.append("CREATE TABLE m_quotation_detail_tbl (qd_id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, qd_q_id	integer, qd_item_place integer, qd_price_id	integer, qd_quantity1 integer, qd_quantity2 integer, qd_note text);");
//	tables.append("CREATE TABLE m_quotation_tbl (q_id integer		PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, q_client_id integer, q_company_id integer, q_data date, q_price1 real, q_price2 real, q_price3 real, q_mytotal real);");
//	tables.append("CREATE TABLE m_receipt (re_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, re_inv_id integer, re_total real, re_client_id integer, re_comp_id integer);");
//	tables.append("CREATE TABLE m_receipt_detail_tbl (red_id integer	PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, red_re_id integer, red_data date, red_amount real, red_detail integer, red_note text);");
//	tables.append("CREATE TABLE m_supplier_tbl (supplier_id integer	PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, supplier_name text, supplier_addres text, supplier_telephon text, supplier_mob text, supplier_email text, supplier_web text);");
	QSqlQuery myquerry = QSqlQuery(myNewdb);
	for (int i = 0; i < tables.size(); ++i) {
		myquerry.exec(tables[i]);
		qDebug() << myquerry.lastQuery();
		qDebug() << myquerry.lastError();
	}
	mydb = myNewdb;
	return true;
}

QSqlDatabase AtpDbMain::getDataBase(){
	if (!mydb.isOpen()){
		if(readIniFile()){
			setNewConnection();
		}
	}
	return mydb;
}

bool AtpDbMain::uninit() {
	mydb.close();
	QSqlDatabase::removeDatabase(mydb.connectionName());
	if(mydb.isOpen()){
		return false;
	} else {
		return true;
	}
}
