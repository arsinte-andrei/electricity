#include "AtpClientPoints.h"
#include "ui/uiAtpClientPoints.h"
#include "AtpClientSyncPoints.h"
#include "AtpSqlQuery.h"

#include <QDebug>
#include <QMessageBox>

AtpClientPoints::AtpClientPoints(QString clientName, QWidget *parent) : QWidget(parent), ui(new Ui::AtpClientPoints){
	this->clientName = clientName;
	ui->setupUi(this);
	clientName.clear();
	data = new QMap<QString, QVariant>;
	model = new QSqlTableModel(this, AtpSqlQuery::getDbConnection(this->clientName));
	updateDb();

	connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onButtonOkClicked()));
	connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(onButtonDeleteClicked()));
	connect(ui->buttonEdit, SIGNAL(clicked()), this, SLOT(onButtonEditClicked()));
	connect(ui->buttonSync, SIGNAL(clicked()), this, SLOT(onButtonSyncClicked()));
	connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(onButtonCancelClicked()));
	connect(ui->tablePoint, SIGNAL(clicked(QModelIndex)), this, SLOT(onTablePointsClicked(QModelIndex)));
	connect(ui->editSearch, SIGNAL(textChanged(QString)), this, SLOT(onEditSearchTextChanged(QString)));
}

AtpClientPoints::~AtpClientPoints(){
	delete ui;
}

void AtpClientPoints::updateDb() {
	ui->enableAndDisable("reset");
	resetVars();

	model->setTable("cl_point_price_t");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->setHeaderData(0, Qt::Horizontal,"Id");
	model->setHeaderData(1, Qt::Horizontal,"Name");
	model->setHeaderData(2, Qt::Horizontal,"Client price");
	model->setHeaderData(3, Qt::Horizontal,"My Price");
	model->select();

	proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(model);
	proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	ui->tablePoint->setModel(proxyModel);
	ui->tablePoint->setSortingEnabled(true);
	ui->tablePoint->setColumnHidden(0, true);
	ui->tablePoint->setColumnWidth(1, 300);
	ui->tablePoint->setColumnWidth(2, 100);
	ui->tablePoint->setColumnWidth(3, 100);

	ui->tablePoint->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tablePoint->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tablePoint->setAlternatingRowColors(true);
}

void AtpClientPoints::onTablePointsClicked(const QModelIndex &index){
	int rand = index.row();
	QString punct_id = ui->tablePoint->model()->data(ui->tablePoint->model()->index(rand,0)).toString();
	QString punct_name = ui->tablePoint->model()->data(ui->tablePoint->model()->index(rand,1)).toString();
	QString comp_point_price_t1 = ui->tablePoint->model()->data(ui->tablePoint->model()->index(rand,2)).toString();
	QString comp_point_price_t2 = ui->tablePoint->model()->data(ui->tablePoint->model()->index(rand,3)).toString();

	ui->editName->setText(punct_name);
	ui->editPrice1->setText(comp_point_price_t1);
	ui->editPrice2->setText(comp_point_price_t2);

	punctId = punct_id.toInt();
	if (punctId > 0) {
		ui->buttonEdit->setEnabled(true);
		ui->buttonDelete->setEnabled(true);
	} else {
		ui->buttonEdit->setEnabled(false);
		ui->buttonDelete->setEnabled(false);
	}
}

void AtpClientPoints::onEditSearchTextChanged(const QString &arg1){
int columnToSort = proxyModel->sortColumn();
	if (columnToSort < 1) {
		columnToSort = 1;
	}
	proxyModel->setFilterKeyColumn(columnToSort);
	proxyModel->setFilterFixedString(arg1);
}

void AtpClientPoints::onButtonCancelClicked(){
	if (seEediteaza){
			ui->enableAndDisable("reset");
			resetVars();
		} else {
			this->close();
			emit exitSignal();
		}
}

void AtpClientPoints::onButtonEditClicked(){
	QString buttonName;
	buttonName = ui->buttonEdit->text();
	if ( buttonName == "Edit"){
		ui->enableAndDisable("edit");
		seEediteaza = true;
		eVechi = true;
	} else {
		data->clear();
		data->insert(":punct_id", punctId);
		data->insert(":punct_name", ui->editName->text());
		data->insert(":punct_price1", ui->editPrice1->text());
		data->insert(":punct_price2", ui->editPrice2->text());
		AtpSqlQuery::atpUpdate(clientName, "cl_point_price_t", data, "punct_id = :punct_id");
		updateDb();
	}
}

void AtpClientPoints::onButtonDeleteClicked(){
	QMessageBox msgBox;
	msgBox.setText("Delete a Company.");
	msgBox.setInformativeText("Are you shure you whant to delete company?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	int ret = msgBox.exec();
	switch (ret) {
		case QMessageBox::No:
			ui->enableAndDisable("reset");
			resetVars();
			break;
		case QMessageBox::Yes:{
			QString whereTo = QString("punct_id = %1").arg(punctId);
			AtpSqlQuery::atpDelete(clientName, "cl_point_price_t", whereTo);
			updateDb(); }
			break;
		default:
			break;
	}
}

void AtpClientPoints::onButtonOkClicked(){
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
				if (eVechi){
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

void AtpClientPoints::onButtonSyncClicked(){
	AtpClientSyncPoints *syncPoints = new AtpClientSyncPoints(this->clientName);
	syncPoints->setModal(true);
	syncPoints->exec();
	qDebug()<< "dupa exec";
	updateDb();
}

void AtpClientPoints::resetVars(){
	seEediteaza = false;
	eVechi = false;
	punctId = 0;
}
