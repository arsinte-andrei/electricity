#include "AtpClientChuse.h"

#include "ui/uiAtpClientChuse.h"
#include "AtpSqlQuery.h"
#include "AtpSettings.h"
#include <QMessageBox>

#include <QSqlTableModel>

AtpClientChuse::AtpClientChuse(QWidget *parent) :	QDialog(parent), ui(new Ui::AtpClientChuse){
	ui->setupUi(this);

	model = new QSqlTableModel(this, AtpSqlQuery::getDbConnection("comp"));
	updateDatabase();

	connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onButtonOkClicked()));
	connect(ui->buttonEdit, SIGNAL(clicked()), this, SLOT(onButtonEditClicked()));
	connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(onButtonCancelClicked()));
	connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onTableViewDoubleClicked()));
	connect(ui->editSearch, SIGNAL(textChanged(QString)), this, SLOT(onEditSearchTextChanged(QString)));
}

AtpClientChuse::~AtpClientChuse(){
	delete ui;
}

void AtpClientChuse::onButtonOkClicked(){
	if (acceptClient()){
		this->accept();
	} else {
		QMessageBox::critical(0, "Client not available ",
		"Unable to find the specified Client please try again", QMessageBox::Ok);
	}
}

void AtpClientChuse::onButtonEditClicked(){
	emit startEditClient();
	this->reject();
}

void AtpClientChuse::onButtonCancelClicked(){
	this->reject();
}

void AtpClientChuse::updateDatabase(){
	model->clear();
	model->setTable("comp_client_list_t");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->setHeaderData(0, Qt::Horizontal,"Id");
	model->setHeaderData(1, Qt::Horizontal,"Name");
	model->setHeaderData(2, Qt::Horizontal,"Address");
	model->setHeaderData(3, Qt::Horizontal,"Telephone");
	model->setHeaderData(4, Qt::Horizontal,"Mobile");
	model->setHeaderData(5, Qt::Horizontal,"E-mail");
	model->setHeaderData(6, Qt::Horizontal,"File Name");
	proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(model);
	proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	ui->tableView->setModel(proxyModel);
	ui->tableView->setSortingEnabled(true);
	ui->tableView->setColumnHidden(0, true);
	ui->tableView->setColumnHidden(6, true);
	ui->tableView->setColumnWidth(1, 100);
	ui->tableView->setColumnWidth(2, 250);
	ui->tableView->setColumnWidth(3, 150);
	ui->tableView->setColumnWidth(4, 150);
	ui->tableView->setColumnWidth(5, 150);
	ui->tableView->setColumnWidth(6, 150);
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableView->setAlternatingRowColors(true);
	model->select();
}

bool AtpClientChuse::acceptClient(){
	if(ui->checkBoxAllClients->checkState() == Qt::Checked){
		AtpSettings::setValue("Client/Id", 0);
		AtpSettings::setValue("Client/Name", "");
		AtpSettings::setValue("Client/Path", "");
		return true;
	} else {
		int rand = ui->tableView->selectionModel()->currentIndex().row();
		int clientId = ui->tableView->model()->data(ui->tableView->model()->index(rand, 0)).toInt();
		QString clientName = ui->tableView->model()->data(ui->tableView->model()->index(rand, 1)).toString();
		QString clientPath = ui->tableView->model()->data(ui->tableView->model()->index(rand, 6)).toString();
		if (clientId > 0 ){
			AtpSettings::setValue("Client/Id", clientId);
			AtpSettings::setValue("Client/Name", clientName);
			AtpSettings::setValue("Client/Path", clientPath);
			return true;
		}
	}
	return false;
}

void AtpClientChuse::onTableViewDoubleClicked(){
	onButtonOkClicked();
}

void AtpClientChuse::onEditSearchTextChanged(const QString &arg1){
	int columnToSort = proxyModel->sortColumn();
	if (columnToSort < 1) {
		columnToSort = 1;
	}
	proxyModel->setFilterKeyColumn(columnToSort);
	proxyModel->setFilterFixedString(arg1);
}
