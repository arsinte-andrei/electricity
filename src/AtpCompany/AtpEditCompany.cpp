#include "AtpEditCompany.h"
#include "ui_AtpEditCompany.h"

#include <QMessageBox>

AtpEditCompany::AtpEditCompany(QWidget *parent) : QMdiSubWindow(parent), ui(new Ui::AtpEditCompany){
	ui->setupUi(this);

	data = new QMap<QString, QVariant>;
	model = new QSqlTableModel;
	updateDb();

	this->setFixedSize(735, 525);
}

AtpEditCompany::~AtpEditCompany(){
	delete ui;
}

void AtpEditCompany::on_buttonOk_clicked(){
	close();
}

void AtpEditCompany::on_buttonNew_clicked(){
	QString buttonName;
	buttonName = ui->buttonNew->text();
	if ( buttonName == "New"){
		enableAndDisable("new");
	} else {
		data->clear();
		data->insert(":comp_name", ui->editCompany->text());
		data->insert(":comp_addres", ui->editAddress->document()->toPlainText());
		data->insert(":comp_www", ui->editWebsite->text());
		data->insert(":comp_director", ui->editDirector->text());
		data->insert(":comp_tel", ui->editTel->text());
		data->insert(":comp_mob", ui->editMob->text());
		data->insert(":comp_email", ui->editMail->text());
//		db->atpInsert("company_tbl", data);
//TODO sa stie utilizatorul in caz ca nu a intrat in baza de date si sa se scrie un log
		updateDb();
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
			enableAndDisable("reset");
			break;
		case QMessageBox::Yes:{
			QString whereTo = QString("comp_id = %1").arg(compId);
//			db->atpDelete("company_tbl", whereTo);
			updateDb();
		}
			break;
		default:
			break;
	}
}

void AtpEditCompany::on_buttonEdit_clicked(){
	QString buttonName;
	buttonName = ui->buttonEdit->text();
	if ( buttonName == "Edit"){
		enableAndDisable("edit");
	} else {
		data->clear();
		data->insert(":comp_name", ui->editCompany->text());
		data->insert(":comp_addres", ui->editAddress->document()->toPlainText());
		data->insert(":comp_www", ui->editWebsite->text());
		data->insert(":comp_director", ui->editDirector->text());
		data->insert(":comp_tel", ui->editTel->text());
		data->insert(":comp_mob", ui->editMob->text());
		data->insert(":comp_email", ui->editMail->text());
		data->insert(":comp_id", compId);
//		db->atpUpdate("company_tbl", data, "comp_id = :comp_id");
		updateDb();
	}
}

void AtpEditCompany::on_buttonCancel_clicked(){
	this->close();
}

void AtpEditCompany::on_editSearch_textEdited(const QString &arg1){
	int columnToSort = proxyModel->sortColumn();
	if (columnToSort < 1) {
		columnToSort = 1;
	}
	proxyModel->setFilterKeyColumn(columnToSort);
	proxyModel->setFilterFixedString(arg1);
}

void AtpEditCompany::on_tableViewCompany_clicked(const QModelIndex &index){
	int rand = index.row();
	QString comp_id = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,0)).toString();
	QString comp_name = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,1)).toString();
	QString comp_dir = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,4)).toString();
	QString comp_address = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,2)).toString();
	QString comp_web = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,3)).toString();
	QString comp_tel = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,5)).toString();
	QString comp_mob = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,6)).toString();
	QString comp_email = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,7)).toString();

	QTextDocument *compAddress= new QTextDocument(ui->editAddress);
	compAddress->setPlainText(comp_address);
	QPlainTextDocumentLayout *layout = new QPlainTextDocumentLayout(compAddress);
	compAddress->setDocumentLayout(layout);

	ui->editCompany->setText(comp_name);
	ui->editDirector->setText(comp_dir);
	ui->editAddress->setDocument(compAddress);
	ui->editWebsite->setText(comp_web);
	ui->editMail->setText(comp_email);
	ui->editMob->setText(comp_mob);
	ui->editTel->setText(comp_tel);
	compId = comp_id.toInt();
	if (compId > 0) {
		ui->buttonEdit->setEnabled(true);
		ui->buttonDelete->setEnabled(true);
	} else {
		ui->buttonEdit->setEnabled(false);
		ui->buttonDelete->setEnabled(false);
	}
//	qDebug() << index.column();
}

void AtpEditCompany::updateDb() {
	enableAndDisable("reset");
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

	ui->tableViewCompany->setModel(proxyModel);
	ui->tableViewCompany->setSortingEnabled(true);
	ui->tableViewCompany->setColumnHidden(0, true);
	ui->tableViewCompany->setColumnWidth(1, 100);
	ui->tableViewCompany->setColumnWidth(2, 250);
	ui->tableViewCompany->setColumnWidth(3, 150);
	ui->tableViewCompany->setColumnWidth(4, 150);
	ui->tableViewCompany->setColumnWidth(5, 150);
	ui->tableViewCompany->setColumnWidth(6, 150);
	ui->tableViewCompany->setColumnWidth(7, 150);
	ui->tableViewCompany->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableViewCompany->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableViewCompany->setAlternatingRowColors(true);
	model->select();
	//ui->companyTableView->verticalHeader()->setStyleSheet("QHeaderView::section:checked {"
//	" background-color: black; }"
//	" background-image: url(imgs/arrow.png)"
//	);
}

void AtpEditCompany::enableAndDisable(QString condition){
	if (condition == "reset"){
		enableAndDisable("resetButtons");
		enableAndDisable("disableFields");
		enableAndDisable("clearFields");
	} else if (condition == "resetButtons"){
		ui->buttonNew->setText("New");
		ui->buttonNew->setEnabled(true);
		ui->buttonEdit->setText("Edit");
		ui->buttonEdit->setEnabled(false);
		ui->buttonDelete->setEnabled(false);
	} else if (condition == "disableFields"){
		ui->editAddress->setEnabled(false);
		ui->editCompany->setEnabled(false);
		ui->editDirector->setEnabled(false);
		ui->editMail->setEnabled(false);
		ui->editMob->setEnabled(false);
		ui->editTel->setEnabled(false);
		ui->editWebsite->setEnabled(false);
		ui->editSearch->setEnabled(true);
		ui->editSearch->clear();
		ui->tableViewCompany->setEnabled(true);
	} else if (condition == "enableFields"){
		ui->editAddress->setEnabled(true);
		ui->editCompany->setEnabled(true);
		ui->editDirector->setEnabled(true);
		ui->editMail->setEnabled(true);
		ui->editMob->setEnabled(true);
		ui->editTel->setEnabled(true);
		ui->editWebsite->setEnabled(true);
		ui->editSearch->setEnabled(false);
		ui->tableViewCompany->setEnabled(false);
	} else if (condition == "clearFields"){
		ui->editAddress->clear();
		ui->editCompany->clear();
		ui->editDirector->clear();
		ui->editMail->clear();
		ui->editMob->clear();
		ui->editTel->clear();
		ui->editWebsite->clear();
		ui->editSearch->clear();
	} else if (condition == "edit"){
		ui->buttonEdit->setText("Save");
		ui->buttonDelete->setEnabled(false);
		ui->buttonNew->setEnabled(false);
		enableAndDisable("enableFields");
	} else if (condition == "new") {
		ui->buttonNew->setText("Save");
		ui->buttonDelete->setEnabled(false);
		ui->buttonEdit->setEnabled(false);
		ui->editSearch->setEnabled(false);
		enableAndDisable("clearFields");
		enableAndDisable("enableFields");
	}
}
