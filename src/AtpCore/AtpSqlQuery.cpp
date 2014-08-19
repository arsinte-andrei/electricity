#include "AtpSqlQuery.h"
#include "AtpDbMain.h"
#include "AtpDbComp.h"
#include"AtpDbClient.h"

#include <QDebug>
#include <QSqlError>

QSqlDatabase AtpSqlQuery::getDbConnection(QString connectionName){
	if (connectionName.startsWith("main")){
		return AtpDbMain::getDataBase();
	} else if (connectionName.startsWith("comp")) {
		return AtpDbComp::getDataBase();
	} else if(connectionName.startsWith("client")) {
		return AtpDbClient::getDataBase(connectionName.mid(7));
	}
	return QSqlDatabase::addDatabase("","noConnection");
}

QSqlQuery AtpSqlQuery::atpCreateView(QString dbName, QString sqlQuerry){
	QSqlQuery myQuerry = QSqlQuery(getDbConnection(dbName));
	myQuerry.prepare(sqlQuerry);
	myQuerry.exec();
	return myQuerry;
}

QSqlQuery AtpSqlQuery::atpDeleteView(QString dbName, QString viewName){
	QSqlQuery myQuerry = QSqlQuery(getDbConnection(dbName));
	myQuerry.prepare("DROP VIEW " + viewName);
	myQuerry.exec();
	return myQuerry;
}

QSqlQuery AtpSqlQuery::quotationDetailView(QString dbName, int qId){
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
	return atpCreateView(viewTableStr, dbName);
}

QSqlQuery AtpSqlQuery::quotationView(QString dbName){
	QString viewTableStr = " "
		"CREATE VIEW IF NOT EXISTS quotation_view "
		"AS "
		"SELECT quotation_tbl.q_id, company_tbl.comp_name, client_list_tbl.client_name, quotation_tbl.q_data, quotation_tbl.q_price1, quotation_tbl.q_price2, quotation_tbl.q_price3, quotation_tbl.q_mytotal "
		"FROM quotation_tbl "
			 "LEFT OUTER JOIN company_tbl "
				  "ON quotation_tbl.q_company_id = company_tbl.comp_id "
			 "LEFT OUTER JOIN client_list_tbl "
				  "ON quotation_tbl.q_client_id = client_list_tbl.client_id;";
	return atpCreateView(viewTableStr, dbName);
}

QSqlQuery AtpSqlQuery::atpSelect(QString dbName, QString sqlQuerry, QMap<QString, QVariant> *myArray) {
	QSqlQuery myQuerry = QSqlQuery(getDbConnection(dbName));
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

QSqlQuery AtpSqlQuery::atpInsert(QString dbName, QString tableName, QMap<QString, QVariant> *data) {
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

	QSqlQuery myQuerry = QSqlQuery(getDbConnection(dbName));
	myQuerry.prepare("INSERT INTO " + tableName + " ( " + fieldNames + ") VALUES ( " + fieldValues + ")");
//	qDebug() << data;
	QMap<QString, QVariant>::const_iterator i;
	for (i = data->constBegin(); i != data->constEnd(); ++i) {
		myQuerry.bindValue(i.key(), i.value());
		//myQuerry.bindValue(i.key().toUtf8().data(), i.value().toString().toUtf8().data());
	}
//	qDebug() << myQuerry.boundValues();
	myQuerry.exec();
	qDebug() <<  myQuerry.lastQuery() <<myQuerry.lastError();
	return myQuerry;
}

QSqlQuery AtpSqlQuery::atpUpdate(QString dbName, QString tableName, QMap<QString, QVariant> *data, QString whereTo) {
	QString fieldDetails, fieldNames, fieldValues, temp;
	QMap<QString, QVariant>::const_iterator i1;
	for (i1 = data->constBegin(); i1 != data->constEnd(); ++i1) {
		temp = i1.key();
		fieldValues = temp;
		fieldNames = temp.remove(0,1);
		fieldDetails += fieldNames + " = " + fieldValues + ", ";
	}
	fieldDetails.remove(fieldDetails.lastIndexOf(","),1);
	QSqlQuery myQuerry = QSqlQuery(getDbConnection(dbName));
	myQuerry.prepare("UPDATE " + tableName + " SET " + fieldDetails + " WHERE " + whereTo);
	QMap<QString, QVariant>::const_iterator i;
	for (i = data->constBegin(); i != data->constEnd(); ++i) {
		myQuerry.bindValue(i.key(), i.value());
	}
	myQuerry.exec();
//	qDebug() <<  myQuerry.lastQuery() <<myQuerry.lastError();
	return myQuerry;
}

QSqlQuery AtpSqlQuery::atpDelete(QString dbName, QString tableName, QString whereTo){
	QSqlQuery myQuerry = QSqlQuery(getDbConnection(dbName));
	myQuerry.prepare("DELETE FROM " + tableName + " WHERE " + whereTo);
	myQuerry.exec();
//	qDebug() <<  myQuerry.lastQuery() <<myQuerry.lastError();
	return myQuerry;
}

