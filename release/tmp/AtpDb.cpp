#include "AtpDb.h"

#include <QtSql>
#include <QFile>
#include <QMessageBox>
#include <QApplication>

QSqlDatabase AtpDb::mydb;
bool AtpDb::openStatus = false;
QString AtpDb::dbPath = "";
QString AtpDb::dbType = "";

bool AtpDb::readIniFile(){
	dbPath = AtpSettings::getStringValue("Db/Path", "");
	dbType = AtpSettings::getStringValue("Db/Type", "QSQLITE");
	if (dbFileExist(dbPath) && isDriverAvailable(dbType)){
		return true;
	} else {
		return false;
	}
}

bool AtpDb::dbFileExist(QString cale){
	QFile db_file(cale);
	if (!db_file.exists()) {
		QMessageBox::critical(0, qApp->tr("Cannot open database"),
		qApp->tr("Database file not found. Create or import one in Tools Settings!"), QMessageBox::Ok);
		return false;
	} else {
		return true;
	}
}

bool AtpDb::isDriverAvailable(QString tip){
	if(!QSqlDatabase::isDriverAvailable(tip)){
		QMessageBox::critical(0, qApp->tr("Driver is not available"),
		qApp->tr("Unable to establish a database connection.\n"
		"DataBase driver is not available! Check Database settings"), QMessageBox::Cancel);
		return false;
	}
	return true;
}

bool AtpDb::setNewConnection(){
	mydb = QSqlDatabase::addDatabase(dbType);
	mydb.setDatabaseName(dbPath);
	if (!mydb.open()){
		qCritical() << "couldn't connect to database Error[" << mydb.lastError().text() << "]"  << dbPath;
		return false;
	} else {
		qDebug() << "succsessfully connected to database " << dbPath;
		openStatus = true;
		return true;
	}
}

bool AtpDb::isOpen(){
	return mydb.isOpen();
}

void AtpDb::setDataBasePath(QString newPath){
	dbPath = newPath;
	uninit();
}

void AtpDb::setDataBaseType(QString newType){
	dbType = newType;
	uninit();
}

QSqlQuery AtpDb::atpCreateView(QString sqlQuerry){
	QSqlQuery myQuerry = QSqlQuery(getDataBase());
	myQuerry.prepare(sqlQuerry);
	myQuerry.exec();
	return myQuerry;
}

QSqlQuery AtpDb::atpDeleteView(QString viewName){
	QSqlQuery myQuerry = QSqlQuery(getDataBase());
	myQuerry.prepare("DROP VIEW " + viewName);
	myQuerry.exec();
	return myQuerry;
}

QSqlQuery AtpDb::atpSelect(QString sqlQuerry, QMap<QString, QVariant> *myArray ) {
	QSqlQuery myQuerry = QSqlQuery(getDataBase());
	myQuerry.prepare(sqlQuerry);
//	qDebug() << myArray;
	if (myArray && !myArray->isEmpty()){
		QMap<QString, QVariant>::const_iterator i;
		for (i = myArray->constBegin(); i != myArray->constEnd(); ++i) {
			myQuerry.bindValue(i.key(), i.value());
			//myQuerry.bindValue(i.key().toUtf8().data(), i.value().toString().toUtf8().data());
		}
	}
//	qDebug() << myQuerry.boundValues();
	myQuerry.exec();
//	qDebug() <<  myQuerry.lastQuery() <<myQuerry.lastError();
	return myQuerry;
}

QSqlQuery AtpDb::atpInsert(QString tableName, QMap<QString, QVariant> *data ) {
	QString fieldNames, fieldValues, temp;
	QMap<QString, QVariant>::const_iterator i1;
	for (i1 = data->constBegin(); i1 != data->constEnd(); ++i1) {
		temp = i1.key();
		fieldValues += temp + ", ";
		fieldNames += temp.remove(0,1) + ", ";
	}
	fieldNames.remove(fieldNames.lastIndexOf(","),1);
	fieldValues.remove(fieldValues.lastIndexOf(","),1);
//	qDebug() << fieldNames << "** - **" << fieldValues;

	QSqlQuery myQuerry = QSqlQuery(getDataBase());
	myQuerry.prepare("INSERT INTO " + tableName + " ( " + fieldNames + ") VALUES ( " + fieldValues + ")");
//	qDebug() << data;
	QMap<QString, QVariant>::const_iterator i;
	for (i = data->constBegin(); i != data->constEnd(); ++i) {
		myQuerry.bindValue(i.key(), i.value());
		//myQuerry.bindValue(i.key().toUtf8().data(), i.value().toString().toUtf8().data());
	}
//	qDebug() << myQuerry.boundValues();
	myQuerry.exec();
//	qDebug() <<  myQuerry.lastQuery() <<myQuerry.lastError();
	return myQuerry;
}

QSqlQuery AtpDb::atpUpdate(QString tableName, QMap<QString, QVariant> *data, QString whereTo) {
	QString fieldDetails, fieldNames, fieldValues, temp;
	QMap<QString, QVariant>::const_iterator i1;
	for (i1 = data->constBegin(); i1 != data->constEnd(); ++i1) {
		temp = i1.key();
		fieldValues = temp;
		fieldNames = temp.remove(0,1);
		fieldDetails += fieldNames + " = " + fieldValues + ", ";
	}
	fieldDetails.remove(fieldDetails.lastIndexOf(","),1);
	QSqlQuery myQuerry = QSqlQuery(getDataBase());
	myQuerry.prepare("UPDATE " + tableName + " SET " + fieldDetails + " WHERE " + whereTo);
	QMap<QString, QVariant>::const_iterator i;
	for (i = data->constBegin(); i != data->constEnd(); ++i) {
		myQuerry.bindValue(i.key(), i.value());
	}
	myQuerry.exec();
//	qDebug() <<  myQuerry.lastQuery() <<myQuerry.lastError();
	return myQuerry;
}

QSqlQuery AtpDb::atpDelete(QString tableName, QString whereTo){
	QSqlQuery myQuerry = QSqlQuery(getDataBase());
	myQuerry.prepare("DELETE FROM " + tableName + " WHERE " + whereTo);
	myQuerry.exec();
//	qDebug() <<  myQuerry.lastQuery() <<myQuerry.lastError();
	return myQuerry;
}

bool AtpDb::createSQLiteDb(QString dbNewPath, QString dbNewType) {
	uninit();
	QSqlDatabase myNewdb;
	if (!isDriverAvailable(dbNewType)){
		return false;
	}
	myNewdb = QSqlDatabase::addDatabase(dbNewType);
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
	tables.append("CREATE TABLE client_list_tbl(client_id integer	PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, client_name text, client_address text, client_tel text, client_mob text, client_email text);");
	tables.append("CREATE TABLE company_tbl (comp_id INTEGER		PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, comp_name text, comp_addres text, comp_www text, comp_director text, comp_tel text, comp_mob text, comp_email text);");
	tables.append("CREATE TABLE for_tbl (for_id integer				PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, for_name text);");
	tables.append("CREATE TABLE group_tbl (group_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, group_place text);");
	tables.append("CREATE TABLE invoice_tbl (inv_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, inv_quote_id  integer,	inv_date date, inv_for_id integer, inv_value real);");
	tables.append("CREATE TABLE login_tbl (login_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, login_username  text, login_password  text);");
	tables.append("CREATE TABLE materiale_tbl ( mat_id integer		PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, mat_name text, mat_price1 real, mat_price2 real, mat_supplier_id  integer);");
	tables.append("CREATE TABLE plata_tbl (plata_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, plata_detalii  text);");
	tables.append("CREATE TABLE punct_price ( punct_id integer		PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, punct_name    text, punct_price1  real,  punct_price2  real);");
	tables.append("CREATE TABLE quotation_detail_tbl (qd_id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, qd_q_id	integer, qd_item_place integer, qd_price_id	integer, qd_quantity1 integer, qd_quantity2 integer, qd_note text);");
	tables.append("CREATE TABLE quotation_tbl (q_id integer			PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, q_client_id integer, q_company_id integer, q_data date, q_price1 real, q_price2 real, q_price3 real, q_mytotal real);");
	tables.append("CREATE TABLE receipt (re_id integer				PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, re_inv_id integer, re_total real, re_client_id integer, re_comp_id integer);");
	tables.append("CREATE TABLE receipt_detail_tbl (red_id integer	PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, red_re_id integer, red_data date, red_amount real, red_detail integer, red_note text);");
	tables.append("CREATE TABLE supplier_tbl (supplier_id integer	PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, supplier_name text, supplier_addres text, supplier_telephon text, supplier_mob text, supplier_email text, supplier_web text);");
	QSqlQuery myquerry = QSqlQuery(myNewdb);
	for (int i = 0; i < tables.size(); ++i) {
		myquerry.exec(tables[i]);
		qDebug() << myquerry.lastQuery();
		qDebug() << myquerry.lastError();
	}
	mydb = myNewdb;
	return true;
}

QSqlDatabase AtpDb::getDataBase(){
	if (!mydb.isOpen()){
		if(readIniFile()){
			setNewConnection();
		}
	}
	return mydb;
}

QSqlQuery AtpDb::quotationDetailView(int qId){
	QString viewTableStr = QString (" "
		"CREATE VIEW IF NOT EXISTS quotation_detail_view_%1 "
		"AS "
		"SELECT quotation_detail_tbl.qd_id, quotation_detail_tbl.qd_q_id, "
			"quotation_detail_tbl.qd_group_place, group_tbl.group_place, "
			"quotation_detail_tbl.qd_point_id, punct_price.punct_name, quotation_detail_tbl.qd_point_q1, quotation_detail_tbl.qd_point_q2, punct_price.punct_price1, punct_price.punct_price2, "
				"(quotation_detail_tbl.qd_point_q1 * punct_price.punct_price1) AS 'qd_p_total1', "
				"(quotation_detail_tbl.qd_point_q2 * punct_price.punct_price1) AS 'qd_p_total2', "
				"((quotation_detail_tbl.qd_point_q1 + quotation_detail_tbl.qd_point_q2) * punct_price.punct_price2) AS 'qd_p_total_my', "
			"quotation_detail_tbl.qd_mat_id, materiale_tbl.mat_name, quotation_detail_tbl.qd_mat_q1, quotation_detail_tbl.qd_mat_q2, materiale_tbl.mat_price1, materiale_tbl.mat_price2, "
				"(quotation_detail_tbl.qd_mat_q1 * materiale_tbl.mat_price1) AS 'qd_m_total1', "
				"(quotation_detail_tbl.qd_mat_q2 * materiale_tbl.mat_price1) AS 'qd_m_total2', "
				"((quotation_detail_tbl.qd_mat_q1 + quotation_detail_tbl.qd_mat_q2) * materiale_tbl.mat_price2) AS 'qd_m_total_my', "
			"quotation_detail_tbl.qd_discount, quotation_detail_tbl.qd_notes  "
		"FROM quotation_detail_tbl "
			"LEFT OUTER JOIN punct_price ON quotation_detail_tbl.qd_point_id = punct_price.punct_id "
			"LEFT OUTER JOIN group_tbl ON quotation_detail_tbl.qd_group_place = group_tbl.group_id "
			"LEFT OUTER JOIN materiale_tbl ON quotation_detail_tbl.qd_mat_id = materiale_tbl.mat_id "
		"WHERE quotation_detail_tbl.qd_q_id = %1 ").arg(qId) ;
	return atpCreateView(viewTableStr);
}

QSqlQuery AtpDb::quotationView(){
	QString viewTableStr = " "
		"CREATE VIEW IF NOT EXISTS quotation_view "
		"AS "
		"SELECT quotation_tbl.q_id, company_tbl.comp_name, client_list_tbl.client_name, quotation_tbl.q_data, quotation_tbl.q_price1, quotation_tbl.q_price2, quotation_tbl.q_price3, quotation_tbl.q_mytotal "
		"FROM quotation_tbl "
			 "LEFT OUTER JOIN company_tbl "
				  "ON quotation_tbl.q_company_id = company_tbl.comp_id "
			 "LEFT OUTER JOIN client_list_tbl "
				  "ON quotation_tbl.q_client_id = client_list_tbl.client_id;";
	return atpCreateView(viewTableStr);
}

void AtpDb::uninit() {
	if (mydb.isOpen()) {
		mydb.close();
	}
}
