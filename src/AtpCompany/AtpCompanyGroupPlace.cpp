#include "AtpCompanyGroupPlace.h"
#include "ui/uiAtpCompanyGroupPlace.h"
#include "AtpSqlQuery.h"

#include <QDebug>

#include <QMessageBox>

AtpCompanyGroupPlace::AtpCompanyGroupPlace(QWidget *parent) : QWidget(parent), ui(new Ui::AtpCompanyGroupPlace){
	ui->setupUi(this);

	myModel = new QStandardItemModel(this);
	updateDb();

	connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onButtonOkClicked()));
	connect(ui->buttonNew, SIGNAL(clicked()), this, SLOT(onButtonNewClicked()));
	connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(onButtonDeleteClicked()));
	connect(ui->buttonEdit, SIGNAL(clicked()), this, SLOT(onButtonEditClicked()));
	connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(onButtonCancelClicked()));
	connect(ui->tableGroup, SIGNAL(clicked(QModelIndex)), this, SLOT(onTableGroupClicked()));
}

AtpCompanyGroupPlace::~AtpCompanyGroupPlace(){
	delete ui;
}

void AtpCompanyGroupPlace::resetVars(){
	CgrupParent = 0;
	CgrupId = 0;
	grupId = 0;
	grupParent = 0;

	seEediteaza = false;
	eNou = false;
	eVechi = false;
}

void AtpCompanyGroupPlace::onButtonOkClicked(){
	if (seEediteaza){
		QString mainWindowTitle = "Save new Comapny ";
		QString infoText = "The form is in the middle of edditing process do you want to save and exit?";
		QMessageBox msgBox;
		msgBox.setWindowTitle(mainWindowTitle);
		msgBox.setText("Save this new Company");
		msgBox.setInformativeText(infoText);
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);
		int ret = msgBox.exec();
		if (ret == QMessageBox::Yes){
			if (eNou){
				onButtonNewClicked();
				close();
				emit exitSignal();
			} else if (eVechi){
				onButtonEditClicked();
				close();
				emit exitSignal();
			}
		}
	} else {
		close();
		emit exitSignal();
	}
}

void AtpCompanyGroupPlace::onButtonNewClicked(){
	QString btnNane = ui->buttonNew->text();
	if (btnNane == "New"){
		disconnect(ui->comboParent,SIGNAL(currentIndexChanged(int)),this,SLOT(onMycomboCurrentIndexChanged()));
		ui->enableAndDisable("new");
		connect(ui->comboParent, SIGNAL(currentIndexChanged(int)), this, SLOT(onMycomboCurrentIndexChanged()));
		seEediteaza = true;
		eNou = true;
	}else{
		if (!ui->editName->text().isEmpty()){
			addNewRecord();
			updateDb();
		} else {
			QMessageBox msgBox;
			msgBox.setText("Add a new a goup.");
			QString mesaj = "You can not add an empty group place";
			msgBox.setInformativeText(mesaj);
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.setDefaultButton(QMessageBox::Ok);
			msgBox.exec();
		}
	}
}

void AtpCompanyGroupPlace::onButtonDeleteClicked(){
	QMessageBox msgBox;
	msgBox.setText("Delete a goup.");
	QString mesaj = QString("Are you shure you whant to delete %1 group?").arg(grupName);
	msgBox.setInformativeText(mesaj);
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	int ret = msgBox.exec();
	switch (ret) {
		case QMessageBox::No:
			disconnect(ui->comboParent,SIGNAL(currentIndexChanged(int)),this,SLOT(onMycomboCurrentIndexChanged()));
			ui->enableAndDisable("reset");
			connect(ui->comboParent, SIGNAL(currentIndexChanged(int)), this, SLOT(onMycomboCurrentIndexChanged()));
			break;
		case QMessageBox::Yes:{
			deleteRecord(grupId);
			updateDb();}
			break;
		default:
			break;
	}
}

void AtpCompanyGroupPlace::onButtonEditClicked(){
	QString buttonName;
	buttonName = ui->buttonEdit->text();
	if ( buttonName == "Edit"){
		disconnect(ui->comboParent,SIGNAL(currentIndexChanged(int)),this,SLOT(onMycomboCurrentIndexChanged()));
		ui->enableAndDisable("edit");
		connect(ui->comboParent, SIGNAL(currentIndexChanged(int)), this, SLOT(onMycomboCurrentIndexChanged()));
		seEediteaza = true;
		eVechi = true;
	} else {
		QMap<QString, QVariant> *data = new QMap<QString, QVariant>;
		data->insert(":group_id", grupId);
		data->insert(":group_place", ui->editName->text());
		data->insert(":group_parent", CgrupId);
		AtpSqlQuery::atpUpdate("main", "m_group_place_t", data, "group_id = :group_id");
		updateDb();
	}
}

void AtpCompanyGroupPlace::onButtonCancelClicked(){
	if (seEediteaza){
		disconnect(ui->comboParent,SIGNAL(currentIndexChanged(int)),this,SLOT(onMycomboCurrentIndexChanged()));
		ui->enableAndDisable("reset");
		connect(ui->comboParent, SIGNAL(currentIndexChanged(int)), this, SLOT(onMycomboCurrentIndexChanged()));
		resetVars();
	} else {
		this->close();
		emit exitSignal();
	}
}

void AtpCompanyGroupPlace::onTableGroupClicked(){
	disconnect(ui->comboParent,SIGNAL(currentIndexChanged(int)),this,SLOT(onMycomboCurrentIndexChanged()));
	QModelIndexList mySelection = ui->tableGroup->selectionModel()->selectedIndexes();
	grupName = mySelection[0].data(Qt::DisplayRole).toString();
	grupId = mySelection[1].data(Qt::DisplayRole).toInt();
	grupParent = mySelection[2].data(Qt::DisplayRole).toInt();
	ui->editName->setText(grupName);
	if (grupId > 0){
		ui->buttonDelete->setEnabled(true);
		ui->buttonEdit->setEnabled(true);
		CgrupId = grupParent;
	}
	QModelIndex myIndex, pIndex;
	myIndex = mySelection[0];
	pIndex = myIndex.parent();
	ui->comboParent->setRootModelIndex(pIndex.parent());
	ui->comboParent->setModelColumn(myIndex.column());
	ui->comboParent->setCurrentIndex(pIndex.row());
	connect(ui->comboParent, SIGNAL(currentIndexChanged(int)), this, SLOT(onMycomboCurrentIndexChanged()));
}

void AtpCompanyGroupPlace::onMycomboCurrentIndexChanged(){
	QModelIndexList mySelection = ui->comboParent->view()->selectionModel()->selectedIndexes();
//	QString name = mySelection[0].data(Qt::DisplayRole).toString();
	CgrupId = mySelection[1].data(Qt::DisplayRole).toInt();
	CgrupParent = mySelection[2].data(Qt::DisplayRole).toInt();
}

void AtpCompanyGroupPlace::updateDb() {
	disconnect(ui->comboParent,SIGNAL(currentIndexChanged(int)),this,SLOT(onMycomboCurrentIndexChanged()));
	ui->enableAndDisable("reset");
	resetVars();
	if (ckDbIntegrity()){
		QSqlQuery q;
		q = AtpSqlQuery::atpSelect("main", "SELECT * FROM m_group_place_t");
		myModel->clear();
		myModel->setColumnCount(3);
		myModel->setHeaderData(0, Qt::Horizontal,"Name");
		myModel->setHeaderData(1, Qt::Horizontal,"ID");
		myModel->setHeaderData(2, Qt::Horizontal,"Parent");

		QStandardItem *parent;
		while(q.next()) {

			int id = q.value(0).toInt();
			QString name = q.value(1).toString();
			int parentId = q.value(2).toInt();

			QStandardItem *pId = new QStandardItem(QString::number(id));
			QStandardItem *pName = new QStandardItem(name);
			QStandardItem *pParentId = new QStandardItem(QString::number(parentId));

			QList<QStandardItem *> row;
			row.append(pName);
			row.append(pId);
			row.append(pParentId);

			rowItemMap.insert(id, pName);

			if (parentId == 0 && id != 0) {
				myModel->appendRow(row);
			} else {
				parent = rowItemMap[parentId];
				parent->appendRow(row);
			}
		}

		ui->tableGroup->setModel(myModel);
		ui->tableGroup->hideColumn(1);
		ui->tableGroup->hideColumn(2);

		ui->comboParent->setModel(myModel);
		ui->comboParent->setMaxVisibleItems(10);
		ui->comboParent->setCurrentIndex(-1);
		ui->comboParent->setModelColumn(0);
	}
	connect(ui->comboParent, SIGNAL(currentIndexChanged(int)), this, SLOT(onMycomboCurrentIndexChanged()));
}

void AtpCompanyGroupPlace::addNewRecord(){
	QMap<QString, QVariant> *data = new QMap<QString, QVariant>;
	data->insert(":group_parent", CgrupId);
	data->insert(":group_place", ui->editName->text());
	AtpSqlQuery::atpInsert("main", "m_group_place_t",data);
}

void AtpCompanyGroupPlace::deleteRecord(int id){
	QString myQs = QString("SELECT * FROM m_group_place_t WHERE group_parent = %1").arg(id);
	QSqlQuery myQ = AtpSqlQuery::atpSelect("main", myQs);
	QString whereTo = QString("group_id = %1").arg(id);
	AtpSqlQuery::atpDelete("main", "m_group_place_t", whereTo);
	while (myQ.next()) {
		deleteRecord(myQ.value(0).toInt());
	}
}

bool AtpCompanyGroupPlace::ckDbIntegrity(){
	QSqlQuery q;
	bool execAgain = false;
	q = AtpSqlQuery::atpSelect("main", "SELECT * FROM m_group_place_t");
	while(q.next()) {
		int id = q.value(0).toInt();
		int parentId = q.value(2).toInt();
		if(parentId > id){
			restoreTreeStructure(id);
			execAgain = true;
			break;
		}
	}
	if (execAgain){
		ckDbIntegrity();
	}
	return true;
}

void AtpCompanyGroupPlace::restoreTreeStructure(int id){
	QSqlQuery selectQuerry, insertQuerry, updateQuerry;
//select
	QString selectString = QString("SELECT * FROM m_group_place_t WHERE group_id = %1").arg(id);
	selectQuerry = AtpSqlQuery::atpSelect("main", selectString);
	selectQuerry.first();
	int curentId = selectQuerry.value(0).toInt();
	QString curentName = selectQuerry.value(1).toString();
	int curentParent = selectQuerry.value(2).toInt();
//delete
	QString whereTo = QString("group_id = %1").arg(id);
	AtpSqlQuery::atpDelete("main", "m_group_place_t", whereTo);
//insert
	QMap<QString, QVariant> *data = new QMap<QString, QVariant>;
	data->insert(":group_parent", curentParent);
	data->insert(":group_place", curentName);
	insertQuerry = AtpSqlQuery::atpInsert("main", "m_group_place_t",data);
	int insertId = insertQuerry.lastInsertId().toInt();
//update other records
	QString updateString = QString("SELECT * FROM m_group_place_t WHERE group_parent = %1").arg(curentId);
	updateQuerry = AtpSqlQuery::atpSelect("main", updateString);
	while (updateQuerry.next()){
		QMap<QString, QVariant> *data = new QMap<QString, QVariant>;
		data->insert(":group_id", updateQuerry.value(0));
		data->insert(":group_place", updateQuerry.value(1));
		data->insert(":group_parent", insertId);
		AtpSqlQuery::atpUpdate("main", "m_group_place_t", data, "group_id = :group_id");
	}
}
