#include "AtpClientSyncPoints.h"
#include "ui/uiAtpClientSyncPoints.h"
#include "AtpSqlQuery.h"

#include <QDebug>
#include <QStandardItem>

AtpClientSyncPoints::AtpClientSyncPoints(QWidget *parent) :	QDialog(parent), ui(new Ui::AtpClientSyncPoints){
	ui->setupUi(this);

	modelPointComp = new QSqlTableModel(this, AtpSqlQuery::getDbConnection("comp"));
	modelPointClient = new QSqlTableModel(this, AtpSqlQuery::getDbConnection("client"));

	updateDb();

	connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onButtonOkClicked()));
	connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(onButtonCancelClicked()));
	connect(ui->buttonFromCompany, SIGNAL(clicked()), this, SLOT(onButtonFromCompanyClicked()));
	connect(ui->buttonFromClient, SIGNAL(clicked()), this, SLOT(onButtonFromClientClicked()));
	connect(ui->checkAllCompany, SIGNAL(stateChanged(int)), this, SLOT(onCheckAllComp(int)));
	connect(ui->checkAllClient, SIGNAL(stateChanged(int)), this, SLOT(onCheckAllClient(int)));
}

AtpClientSyncPoints::~AtpClientSyncPoints(){
	delete ui;
}

void AtpClientSyncPoints::updateDb() {
	modelPointComp->setTable("comp_point_price_t");
	modelPointComp->select();
	modelPointComp->setEditStrategy(QSqlTableModel::OnManualSubmit);
	modelPointComp->insertColumn(0);
	modelPointComp->setHeaderData(0, Qt::Horizontal,"Sync");
	modelPointComp->setHeaderData(1, Qt::Horizontal,"Id");
	modelPointComp->setHeaderData(2, Qt::Horizontal,"Name");
	modelPointComp->setHeaderData(3, Qt::Horizontal,"Client price");
	modelPointComp->setHeaderData(4, Qt::Horizontal,"My Price");
	rowsCompPoint = modelPointComp->rowCount();

	proxyPointComp = new QSortFilterProxyModel(this);
	proxyPointComp->setSourceModel(modelPointComp);
	proxyPointComp->setFilterCaseSensitivity(Qt::CaseInsensitive);
	ui->tableCompPoint->setModel(proxyPointComp);
	ui->tableCompPoint->setSortingEnabled(true);
	ui->tableCompPoint->setColumnHidden(1, true);
	ui->tableCompPoint->setColumnWidth(0, 15);
//	ui->tableCompPoint->setColumnWidth(2, 100);
//	ui->tableCompPoint->setColumnWidth(3, 100);

	ui->tableCompPoint->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableCompPoint->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableCompPoint->setAlternatingRowColors(true);

	for (int i = 0; i < rowsCompPoint; ++i) {
		QModelIndex newIndex = ui->tableCompPoint->model()->index(i,0);
		qDebug() <<newIndex;
		QCheckBox *unulNou = new QCheckBox;
		ui->tableCompPoint->setIndexWidget(newIndex, unulNou);
	}

	modelPointClient->setTable("cl_point_price_t");
	modelPointClient->setEditStrategy(QSqlTableModel::OnManualSubmit);
	modelPointClient->setHeaderData(0, Qt::Horizontal,"Id");
	modelPointClient->setHeaderData(1, Qt::Horizontal,"Name");
	modelPointClient->setHeaderData(2, Qt::Horizontal,"Client price");
	modelPointClient->setHeaderData(3, Qt::Horizontal,"My Price");
	modelPointClient->select();

	proxyPointclient = new QSortFilterProxyModel(this);
	proxyPointclient->setSourceModel(modelPointClient);
	proxyPointclient->setFilterCaseSensitivity(Qt::CaseInsensitive);
	ui->tableClientPoint->setModel(proxyPointclient);
	ui->tableClientPoint->setSortingEnabled(true);
	ui->tableClientPoint->setColumnHidden(0, true);
	ui->tableClientPoint->setColumnWidth(1, 300);
	ui->tableClientPoint->setColumnWidth(2, 100);
	ui->tableClientPoint->setColumnWidth(3, 100);

	ui->tableCompPoint->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableCompPoint->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableClientPoint->setAlternatingRowColors(true);
}

void AtpClientSyncPoints::onButtonOkClicked(){
 this->accept();
}

void AtpClientSyncPoints::onButtonCancelClicked(){
	this->reject();
}

void AtpClientSyncPoints::onButtonFromCompanyClicked(){
	for (int i = 0; i < rowsCompPoint; ++i) {
		QModelIndex newIndex = ui->tableCompPoint->model()->index(i,0);
		QCheckBox *tempCheck;
		tempCheck = qobject_cast<QCheckBox *>(ui->tableCompPoint->indexWidget(newIndex));
		qDebug() << tempCheck->checkState();

	}
}

void AtpClientSyncPoints::onButtonFromClientClicked(){

}

void AtpClientSyncPoints::onCheckAllComp(int status){
	if(status == 2){
		for (int i = 0; i < rowsCompPoint; ++i) {
			QModelIndex newIndex = ui->tableCompPoint->model()->index(i,0);
			QCheckBox *tempCheck;
			tempCheck = qobject_cast<QCheckBox *>(ui->tableCompPoint->indexWidget(newIndex));
			qDebug() << tempCheck->checkState();
			tempCheck->setCheckState(Qt::Checked);
		}
	} else if(status == 0){
		for (int i = 0; i < rowsCompPoint; ++i) {
			QModelIndex newIndex = ui->tableCompPoint->model()->index(i,0);
			QCheckBox *tempCheck;
			tempCheck = qobject_cast<QCheckBox *>(ui->tableCompPoint->indexWidget(newIndex));
			qDebug() << tempCheck->checkState();
			tempCheck->setCheckState(Qt::Unchecked);
		}
	}
}

void AtpClientSyncPoints::onCheckAllClient(int status){
	if(status == 2){
		for (int i = 0; i < rowsCompPoint; ++i) {
			QModelIndex newIndex = ui->tableClientPoint->model()->index(i,0);
			QCheckBox *tempCheck;
			tempCheck = qobject_cast<QCheckBox *>(ui->tableClientPoint->indexWidget(newIndex));
			qDebug() << tempCheck->checkState();
			tempCheck->setCheckState(Qt::Checked);
		}
	} else if(status == 0){
		for (int i = 0; i < rowsCompPoint; ++i) {
			QModelIndex newIndex = ui->tableClientPoint->model()->index(i,0);
			QCheckBox *tempCheck;
			tempCheck = qobject_cast<QCheckBox *>(ui->tableClientPoint->indexWidget(newIndex));
			qDebug() << tempCheck->checkState();
			tempCheck->setCheckState(Qt::Unchecked);
		}
	}
}
