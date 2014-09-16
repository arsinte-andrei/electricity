#include "AtpClientSyncPoints.h"
#include "ui/uiAtpClientSyncPoints.h"
#include "AtpSqlQuery.h"

#include <QDebug>
#include <QStandardItem>

AtpClientSyncPoints::AtpClientSyncPoints(QString clientName, QWidget *parent) :	QDialog(parent), ui(new Ui::AtpClientSyncPoints){
	this->clientName = clientName;
	ui->setupUi(this);

	modelPointComp = new QSqlTableModel(this, AtpSqlQuery::getDbConnection("comp"));

	updateDb();

	connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onButtonOkClicked()));
	connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(onButtonCancelClicked()));
	connect(ui->checkAllCompany, SIGNAL(stateChanged(int)), this, SLOT(onCheckAllComp(int)));
	connect(ui->editSearchCompPoints, SIGNAL(textChanged(QString)), this, SLOT(onEditSearchCompPoint(QString)));
	connectAllCompCheck();
}

AtpClientSyncPoints::~AtpClientSyncPoints(){
	delete ui;
}

void AtpClientSyncPoints::updateDb() {
	modelPointComp->clear();
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
		QModelIndex newIndexData = ui->tableCompPoint->model()->index(i,1);
		QCheckBox *unulNou = new QCheckBox;
		mapCheckComp.insert(newIndexData.data().toString(), unulNou);
		mapAllComp.insert(newIndexData.data().toString(), false);
//		ui->tableCompPoint->setIndexWidget(newIndex, unulNou);
	}
	updateCheckBoxPosition();
}

void AtpClientSyncPoints::onButtonOkClicked(){
	onButtonFromCompanyClicked();
	this->accept();
}

void AtpClientSyncPoints::onButtonCancelClicked(){
	this->reject();
}

void AtpClientSyncPoints::onButtonFromCompanyClicked(){
	for (int var = 0; var < rowsCompPoint; ++var) {
		QString id = modelPointComp->index(var, 1).data().toString();
		QString pointName = modelPointComp->index(var, 2).data().toString();
		QString pointPrice1 = modelPointComp->index(var, 3).data().toString();
		QString pointPrice2 = modelPointComp->index(var, 4).data().toString();
		if(mapAllComp.value(id)){
			QMap<QString, QVariant> *data = new QMap<QString, QVariant>;;
			data->clear();
			data->insert(":punct_id", id);
			data->insert(":punct_name", pointName);
			data->insert(":punct_price1", pointPrice1);
			data->insert(":punct_price2", pointPrice2);
			QString selectQuery = QString("SELECT punct_id FROM cl_point_price_t WHERE punct_id = %1").arg(id);
			QSqlQuery exista = AtpSqlQuery::atpSelect(clientName, selectQuery);
			if(exista.next()){
				AtpSqlQuery::atpUpdate(clientName, "cl_point_price_t", data, "punct_id = :punct_id");
			} else {
				AtpSqlQuery::atpInsert(clientName, "cl_point_price_t", data);
			}
		}
	}
}

void AtpClientSyncPoints::onCheckAllComp(int status){
	if(!mapCheckComp.empty()){
		if(status == 2){
			QMapIterator<QString, QCheckBox *> i(mapCheckComp);
			while (i.hasNext()){
				i.next();
				i.value()->setCheckState(Qt::Checked);
			}
		} else if(status == 0){
			QMapIterator<QString, QCheckBox *> i(mapCheckComp);
			while (i.hasNext()){
				i.next();
				i.value()->setCheckState(Qt::Unchecked);
			}
		}
	}
}

void AtpClientSyncPoints::onCheckButtonCompPressed(){
	int allChecked = 0;
	QMapIterator<QString, QCheckBox *> i(mapCheckComp);
	while (i.hasNext()){
		i.next();
		if (i.value()->checkState() == Qt::Checked){
			mapAllComp[i.key()] = true;
		} else {
			mapAllComp[i.key()] = false;
		}
	}
	int on0 = 0;
	int on1 = 0;
	QMapIterator<QString, bool> ii(mapAllComp);
	while (ii.hasNext()) {
		ii.next();
		if(ii.value()){
			on1++;
		} else {
			on0++;
		}
	}
	if (on0 >= 0 && on1 == 0){
		allChecked = 0;
	} else if (on0 > 0 && on1 > 0){
		allChecked = 1;
	} else if(on0 == 0 && on1 > 0){
		allChecked = 2;
	}

	ui->checkAllCompany->disconnect();

	if(allChecked == 0){
		ui->checkAllCompany->setCheckState(Qt::Unchecked);
	} else if(allChecked == 1){
		ui->checkAllCompany->setCheckState(Qt::PartiallyChecked);
	} else if(allChecked == 2){
		ui->checkAllCompany->setCheckState(Qt::Checked);
	}

	connect(ui->checkAllCompany, SIGNAL(stateChanged(int)), this, SLOT(onCheckAllComp(int)));
}

void AtpClientSyncPoints::connectAllCompCheck(){
	QMapIterator<QString, QCheckBox *> i(mapCheckComp);
	while (i.hasNext()){
		i.next();
		connect(i.value(), SIGNAL(clicked()), this, SLOT(onCheckButtonCompPressed()));
	}
}

void AtpClientSyncPoints::disconnectAllCompCheck(){
	QMapIterator<QString, QCheckBox *> i(mapCheckComp);
	while (i.hasNext()){
		i.next();
		i.value()->disconnect();
	}
}

void AtpClientSyncPoints::onEditSearchCompPoint(const QString &arg1){
	proxyPointComp->setFilterKeyColumn(2);
	proxyPointComp->setFilterFixedString(arg1);
/*
	for (int i = 0; i < proxyPointComp->rowCount(); ++i) {
		QModelIndex newIndex = ui->tableCompPoint->model()->index(i,0);
		QModelIndex newIndexData = ui->tableCompPoint->model()->index(i,1);
		ui->tableCompPoint->setIndexWidget(newIndex, mapCheckComp.value(newIndexData.data().toString()));
	}
	*/
	updateCheckBoxPosition();
}

void AtpClientSyncPoints::updateCheckBoxPosition(){
	for (int i = 0; i < proxyPointComp->rowCount(); ++i) {
		QModelIndex newIndex = ui->tableCompPoint->model()->index(i,0);
		QModelIndex newIndexData = ui->tableCompPoint->model()->index(i,1);
		QCheckBox *unulNou = new QCheckBox;
//		mapCheckComp.insert(newIndexData.data().toString(), unulNou);
//		mapAllComp.insert(newIndexData.data().toString(), false);
		ui->tableCompPoint->setIndexWidget(newIndex, unulNou);
	}
}
