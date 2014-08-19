#include "AtpCompanyChuse.h"

#include "ui/uiAtpCompanyChuse.h"
#include "AtpSqlQuery.h"
#include "AtpSettings.h"
#include <QMessageBox>

#include <QSqlTableModel>

AtpCompanyChuse::AtpCompanyChuse(QWidget *parent) :	QDialog(parent), ui(new Ui::AtpCompanyChuse){
	ui->setupUi(this);

	model = new QSqlTableModel(this, AtpSqlQuery::getDbConnection("main"));
	updateDatabase();

	connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onButtonOkClicked()));
	connect(ui->buttonEdit, SIGNAL(clicked()), this, SLOT(onButtonEditClicked()));
	connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(onButtonCancelClicked()));
	connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onTableViewDoubleClicked()));
	connect(ui->editSearch, SIGNAL(textChanged(QString)), this, SLOT(onEditSearchTextChanged(QString)));
}

AtpCompanyChuse::~AtpCompanyChuse(){
	delete ui;
}

void AtpCompanyChuse::onButtonOkClicked(){
	if (acceptCompany()){
		this->accept();
	} else {
		QMessageBox::critical(0, "Company not available ",
		"Unable to find the specified Company please try again", QMessageBox::Ok);
	}
}

void AtpCompanyChuse::onButtonEditClicked(){
	emit startEditCompany();
	this->reject();
}

void AtpCompanyChuse::onButtonCancelClicked(){
	reject();
}

void AtpCompanyChuse::updateDatabase(){
	model->clear();
	model->setTable("m_company_t");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->setHeaderData(0, Qt::Horizontal,"Id");
	model->setHeaderData(1, Qt::Horizontal,"Name");
	model->setHeaderData(2, Qt::Horizontal,"Address");
	model->setHeaderData(3, Qt::Horizontal,"Website");
	model->setHeaderData(4, Qt::Horizontal,"Director");
	model->setHeaderData(5, Qt::Horizontal,"Telephone");
	model->setHeaderData(6, Qt::Horizontal,"Mobile");
	model->setHeaderData(7, Qt::Horizontal,"E-mail");
	proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(model);
	proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	ui->tableView->setModel(proxyModel);
	ui->tableView->setSortingEnabled(true);
	ui->tableView->setColumnHidden(0, true);
	ui->tableView->setColumnWidth(1, 100);
	ui->tableView->setColumnWidth(2, 250);
	ui->tableView->setColumnWidth(3, 150);
	ui->tableView->setColumnWidth(4, 150);
	ui->tableView->setColumnWidth(5, 150);
	ui->tableView->setColumnWidth(6, 150);
	ui->tableView->setColumnWidth(7, 150);
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableView->setAlternatingRowColors(true);
	model->select();
}

bool AtpCompanyChuse::acceptCompany(){
	int rand = ui->tableView->selectionModel()->currentIndex().row();
	int compId = ui->tableView->model()->data(ui->tableView->model()->index(rand, 0)).toInt();
	QString compName = ui->tableView->model()->data(ui->tableView->model()->index(rand, 1)).toString();
	QString compPath = ui->tableView->model()->data(ui->tableView->model()->index(rand, 8)).toString();
	if (compId > 0 ){
		AtpSettings::setValue("Company/Id", compId);
		AtpSettings::setValue("Company/Name", compName);
		AtpSettings::setValue("Company/Path", compPath);
		return true;
	}
	return false;
}

void AtpCompanyChuse::onTableViewDoubleClicked(){
	onButtonOkClicked();
}

void AtpCompanyChuse::onEditSearchTextChanged(const QString &arg1){
	int columnToSort = proxyModel->sortColumn();
	if (columnToSort < 1) {
		columnToSort = 1;
	}
	proxyModel->setFilterKeyColumn(columnToSort);
	proxyModel->setFilterFixedString(arg1);
}
