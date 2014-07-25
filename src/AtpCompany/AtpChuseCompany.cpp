#include "AtpChuseCompany.h"

#include "ui_AtpChuseCompany.h"
#include "AtpDb.h"
#include "AtpSettings.h"
#include <QMessageBox>

#include <QSqlTableModel>

AtpChuseCompany::AtpChuseCompany(QWidget *parent) :	QDialog(parent), ui(new Ui::AtpChuseCompany){
	ui->setupUi(this);
	setFixedSize(500, 360);

//	this->setFixedSize(480, 315);
	ui->buttonOk->setDefault(true);

	ui->editSearch->setClearButtonEnabled(true);
	ui->editSearch->setPlaceholderText("Search for a company here...");

	model = new QSqlTableModel(this);
	updateDatabase();

}

AtpChuseCompany::~AtpChuseCompany(){
	delete ui;
}

void AtpChuseCompany::on_buttonOk_clicked(){
	int rand = ui->tableView->selectionModel()->currentIndex().row();
	int compId = ui->tableView->model()->data(ui->tableView->model()->index(rand,0)).toInt();
	QString compName = ui->tableView->model()->data(ui->tableView->model()->index(rand,1)).toString();
	if (compId > 0 ){
		AtpSettings::setValue("Company/Id", compId);
		AtpSettings::setValue("Company/Name", compName);
		this->accept();
	} else {
		QMessageBox::critical(0, qApp->tr("Company not available "),
		qApp->tr("Unable to find the specified Company please try again"), QMessageBox::Ok);
	}
}

void AtpChuseCompany::on_buttonEdit_clicked(){
	/*file_edit_company *fileEditCompany = new file_edit_company(this);
	fileEditCompany->setModal(true);
	fileEditCompany->exec();
	updateDb(); */
//client_list_tbl
/*	QSqlTableModel *model = new QSqlTableModel(this);
	model->setTable("company_tbl");
	model->select();
	ui->tableView->setModel(model); */
}

void AtpChuseCompany::on_buttonCancel_clicked(){
	reject();
}

void AtpChuseCompany::on_editSearch_textEdited(const QString &arg1){
	int columnToSort = proxyModel->sortColumn();
	if (columnToSort < 1) {
		columnToSort = 1;
	}
	proxyModel->setFilterKeyColumn(columnToSort);
	proxyModel->setFilterFixedString(arg1);
}

void AtpChuseCompany::updateDatabase(){
	model->clear();
	model->setTable("company_tbl");
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
