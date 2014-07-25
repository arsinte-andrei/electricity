#include "AtpEditCompany.h"
#include "ui_AtpEditCompany.h"

AtpEditCompany::AtpEditCompany(QWidget *parent, Qt::WindowFlags flags) : QMdiSubWindow(parent), ui(new Ui::AtpEditCompany){
	ui->setupUi(this);

	data = new QMap<QString, QVariant>;
	model = new QSqlTableModel;
	updateDb(model);

	this->setFixedSize(735, 525);
	diesableAll();
	ui->editButton->setEnabled(false);
	ui->deleteButton->setEnabled(false);
}

AtpEditCompany::~AtpEditCompany(){
	delete ui;
}

void AtpEditCompany::updateDb() {
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
	ui->companyTableView->setModel(proxyModel);
	ui->companyTableView->setSortingEnabled(true);
	ui->companyTableView->setColumnHidden(0, true);
	ui->companyTableView->setColumnWidth(1, 100);
	ui->companyTableView->setColumnWidth(2, 250);
	ui->companyTableView->setColumnWidth(3, 150);
	ui->companyTableView->setColumnWidth(4, 150);
	ui->companyTableView->setColumnWidth(5, 150);
	ui->companyTableView->setColumnWidth(6, 150);
	ui->companyTableView->setColumnWidth(7, 150);
	ui->companyTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->companyTableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->companyTableView->setAlternatingRowColors(true);
	model->select();
	//ui->companyTableView->verticalHeader()->setStyleSheet("QHeaderView::section:checked {"
//	" background-color: black; }"
//	" background-image: url(imgs/arrow.png)"
//	);
}

void AtpEditCompany::on_editSearch_textEdited(const QString &arg1){
	int columnToSort = proxyModel->sortColumn();
	if (columnToSort < 1) {
		columnToSort = 1;
	}
	proxyModel->setFilterKeyColumn(columnToSort);
	proxyModel->setFilterFixedString(arg1);
}

void AtpEditCompany::on_buttonOk_clicked(){
	accept();
}

void AtpEditCompany::on_buttonEdit_clicked(){
	QString buttonName;
	buttonName = ui->editButton->text();
	if ( buttonName == "Edit"){
		ui->editButton->setText("Save");
		ui->deleteButton->setEnabled(false);
		ui->newButton->setEnabled(false);
		ui->searchBox->setEnabled(false);
		enableAll();
	} else {
		data->clear();
		data->insert(":comp_name", ui->companyEdit->text());
		data->insert(":comp_addres", ui->addressEdit->document()->toPlainText());
		data->insert(":comp_www", ui->webEdit->text());
		data->insert(":comp_director", ui->directorEdit->text());
		data->insert(":comp_tel", ui->telEdit->text());
		data->insert(":comp_mob", ui->mobEdit->text());
		data->insert(":comp_email", ui->emailEdit->text());
		data->insert(":comp_id", compId);
		db->atpUpdate("company_tbl", data, "comp_id = :comp_id");

		diesableAll();
		ui->editButton->setText("Edit");
		ui->deleteButton->setEnabled(true);
		ui->newButton->setEnabled(true);
		ui->searchBox->setEnabled(true);
		updateDb(model);
	}
}

void AtpEditCompany::on_buttonNew_clicked(){
	QString buttonName;
	buttonName = ui->newButton->text();
	if ( buttonName == "New"){
		ui->newButton->setText("Save");
		ui->deleteButton->setEnabled(false);
		ui->editButton->setEnabled(false);
		ui->searchBox->setEnabled(false);
		enableAll();
		ui->companyEdit->clear();
		ui->directorEdit->clear();
		ui->addressEdit->clear();
		ui->webEdit->clear();
		ui->emailEdit->clear();
		ui->mobEdit->clear();
		ui->telEdit->clear();
	} else {
		data->clear();
		data->insert(":comp_name", ui->companyEdit->text());
		data->insert(":comp_addres", ui->addressEdit->document()->toPlainText());
		data->insert(":comp_www", ui->webEdit->text());
		data->insert(":comp_director", ui->directorEdit->text());
		data->insert(":comp_tel", ui->telEdit->text());
		data->insert(":comp_mob", ui->mobEdit->text());
		data->insert(":comp_email", ui->emailEdit->text());
		db->atpInsert("company_tbl", data);

		diesableAll();
		ui->newButton->setText("New");
		ui->deleteButton->setEnabled(true);
		ui->editButton->setEnabled(true);
		ui->searchBox->setEnabled(true);
		updateDb(model);
	}
}

void AtpEditCompany::on_buttonDelete_clicked(){
	QMessageBox msgBox;
	msgBox.setText("Delete a Company.");
	msgBox.setInformativeText("Are you shure you whant to delete company?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	int ret = msgBox.exec();
//	qDebug() << ret;
	switch (ret) {
		case QMessageBox::No:
			diesableAll();
			break;
		case QMessageBox::Yes:{
			QString whereTo = QString("comp_id = %1").arg(compId);
			db->atpDelete("company_tbl", whereTo);
			updateDb(model);
			diesableAll();
			ui->editButton->setEnabled(false);
			ui->deleteButton->setEnabled(false); }
			break;
		default:
			break;
	}
}

void AtpEditCompany::on_tableViewCompanyEditor_clicked(const QModelIndex &index){
	int rand = index.row();
	QString comp_id = ui->companyTableView->model()->data(ui->companyTableView->model()->index(rand,0)).toString();
	QString comp_name = ui->companyTableView->model()->data(ui->companyTableView->model()->index(rand,1)).toString();
	QString comp_dir = ui->companyTableView->model()->data(ui->companyTableView->model()->index(rand,4)).toString();
	QString comp_address = ui->companyTableView->model()->data(ui->companyTableView->model()->index(rand,2)).toString();
	QString comp_web = ui->companyTableView->model()->data(ui->companyTableView->model()->index(rand,3)).toString();
	QString comp_tel = ui->companyTableView->model()->data(ui->companyTableView->model()->index(rand,5)).toString();
	QString comp_mob = ui->companyTableView->model()->data(ui->companyTableView->model()->index(rand,6)).toString();
	QString comp_email = ui->companyTableView->model()->data(ui->companyTableView->model()->index(rand,7)).toString();

	QTextDocument *compAddress= new QTextDocument(ui->addressEdit);
	compAddress->setPlainText(comp_address);
	QPlainTextDocumentLayout *layout = new QPlainTextDocumentLayout(compAddress);
	compAddress->setDocumentLayout(layout);

	ui->companyEdit->setText(comp_name);
	ui->directorEdit->setText(comp_dir);
	ui->addressEdit->setDocument(compAddress);
	ui->webEdit->setText(comp_web);
	ui->emailEdit->setText(comp_email);
	ui->mobEdit->setText(comp_mob);
	ui->telEdit->setText(comp_tel);
	compId = comp_id.toInt();
	if (compId > 0) {
		ui->editButton->setEnabled(true);
		ui->deleteButton->setEnabled(true);
	} else {
		ui->editButton->setEnabled(false);
		ui->deleteButton->setEnabled(false);
	}
//	qDebug() << index.column();
}

void AtpEditCompany::on_buttonCancel_clicked(){
	reject();
}
