#include "AtpCompanySuppliers.h"
#include "ui/uiAtpCompanySuppliers.h"
#include "AtpSqlQuery.h"
#include <QMessageBox>

AtpCompanySuppliers::AtpCompanySuppliers(QWidget *parent) : QWidget(parent), ui(new Ui::AtpCompanySuppliers){
	ui->setupUi(this);

	data = new QMap<QString, QVariant>;
	model = new QSqlTableModel(this, AtpSqlQuery::getDbConnection("comp"));

	updateDb();

	connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onButtonOkClicked()));
	connect(ui->buttonNew, SIGNAL(clicked()), this, SLOT(onButtonNewClicked()));
	connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(onButtonDeleteClicked()));
	connect(ui->buttonEdit, SIGNAL(clicked()), this, SLOT(onButtonEditClicked()));
	connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(onButtonCancelClicked()));
	connect(ui->tabeSuppliers, SIGNAL(clicked(QModelIndex)), this, SLOT(onTableSuppliersClicked(QModelIndex)));
	connect(ui->editSearch, SIGNAL(textChanged(QString)), this, SLOT(onEditSearchTextEdited(QString)));
}

AtpCompanySuppliers::~AtpCompanySuppliers(){
	delete ui;
}

void AtpCompanySuppliers::updateDb() {
	ui->enableAndDisable("reset");
	resetVars();

	model->setTable("comp_supplier_t");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->setHeaderData(0, Qt::Horizontal,"Id");
	model->setHeaderData(1, Qt::Horizontal,"Supplier");
	model->setHeaderData(2, Qt::Horizontal,"Address");
	model->setHeaderData(3, Qt::Horizontal,"Telephone");
	model->setHeaderData(4, Qt::Horizontal,"Mobile");
	model->setHeaderData(5, Qt::Horizontal,"E-mail");
	model->setHeaderData(6, Qt::Horizontal,"Website");
	proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(model);
	proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	ui->tabeSuppliers->setModel(proxyModel);
	ui->tabeSuppliers->setSortingEnabled(true);
	ui->tabeSuppliers->setColumnHidden(0, true);
	ui->tabeSuppliers->setColumnWidth(1, 100);
	ui->tabeSuppliers->setColumnWidth(2, 250);
	ui->tabeSuppliers->setColumnWidth(3, 150);
	ui->tabeSuppliers->setColumnWidth(4, 150);
	ui->tabeSuppliers->setColumnWidth(5, 150);
	ui->tabeSuppliers->setColumnWidth(6, 150);
	ui->tabeSuppliers->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tabeSuppliers->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tabeSuppliers->setAlternatingRowColors(true);
	model->select();
}

void AtpCompanySuppliers::onButtonOkClicked(){
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

void AtpCompanySuppliers::onButtonNewClicked(){
	QString buttonName = ui->buttonNew->text();
	if ( buttonName == "New"){
		seEediteaza = true;
		eNou = true;
		ui->enableAndDisable("new");
	} else {
		data->clear();
		data->insert(":supplier_name", ui->editName->text());
		data->insert(":supplier_addres", ui->editAddress->document()->toPlainText());
		data->insert(":supplier_telephon", ui->editTel->text());
		data->insert(":supplier_mob", ui->editMob->text());
		data->insert(":supplier_email", ui->editMail->text());
		data->insert(":supplier_web", ui->editWeb->text());
		AtpSqlQuery::atpInsert("comp", "comp_supplier_t", data);
		updateDb();
	}
}

void AtpCompanySuppliers::onButtonDeleteClicked(){
	QMessageBox msgBox;
	msgBox.setText("Delete a Company.");
	msgBox.setInformativeText("Are you shure you whant to delete company?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	int ret = msgBox.exec();
	switch (ret) {
		case QMessageBox::No:
			ui->enableAndDisable("reset");
			break;
		case QMessageBox::Yes:{
			QString whereTo = QString("supplier_id = %1").arg(supplierId);
			AtpSqlQuery::atpDelete("comp", "comp_supplier_t", whereTo);
			updateDb();}
			break;
		default:
			break;
	}
}

void AtpCompanySuppliers::onButtonEditClicked(){
	QString buttonName = ui->buttonEdit->text();
	if ( buttonName == "Edit"){
		seEediteaza = true;
		eVechi = true;
		ui->enableAndDisable("edit");
	} else {
		data->clear();
		data->insert(":supplier_id", supplierId);
		data->insert(":supplier_name", ui->editName->text());
		data->insert(":supplier_addres", ui->editAddress->document()->toPlainText());
		data->insert(":supplier_telephon", ui->editTel->text());
		data->insert(":supplier_mob", ui->editMob->text());
		data->insert(":supplier_email", ui->editMail->text());
		data->insert(":supplier_web", ui->editWeb->text());
		AtpSqlQuery::atpUpdate("comp", "comp_supplier_t", data, "supplier_id = :supplier_id");
		updateDb();
	}
}

void AtpCompanySuppliers::onButtonCancelClicked(){
	if (seEediteaza){
		ui->enableAndDisable("reset");
		resetVars();
	} else {
		this->close();
		emit exitSignal();
	}
}

void AtpCompanySuppliers::onEditSearchTextEdited(const QString &arg1){
	int columnToSort = proxyModel->sortColumn();
	if (columnToSort < 1) {
		columnToSort = 1;
	}
	proxyModel->setFilterKeyColumn(columnToSort);
	proxyModel->setFilterFixedString(arg1);
}

void AtpCompanySuppliers::onTableSuppliersClicked(const QModelIndex &index){
	int rand = index.row();
	QString supplier_id = ui->tabeSuppliers->model()->data(ui->tabeSuppliers->model()->index(rand,0)).toString();
	QString supplier_name = ui->tabeSuppliers->model()->data(ui->tabeSuppliers->model()->index(rand,1)).toString();
	QString supplier_addres = ui->tabeSuppliers->model()->data(ui->tabeSuppliers->model()->index(rand,2)).toString();
	QString supplier_telephon = ui->tabeSuppliers->model()->data(ui->tabeSuppliers->model()->index(rand,3)).toString();
	QString supplier_mob = ui->tabeSuppliers->model()->data(ui->tabeSuppliers->model()->index(rand,4)).toString();
	QString supplier_email = ui->tabeSuppliers->model()->data(ui->tabeSuppliers->model()->index(rand,5)).toString();
	QString supplier_web = ui->tabeSuppliers->model()->data(ui->tabeSuppliers->model()->index(rand,6)).toString();

	QTextDocument *supplierAddress= new QTextDocument(ui->editAddress);
	supplierAddress->setPlainText(supplier_addres);
	QPlainTextDocumentLayout *layout = new QPlainTextDocumentLayout(supplierAddress);
	supplierAddress->setDocumentLayout(layout);

	ui->editName->setText(supplier_name);
	ui->editMail->setText(supplier_email);
	ui->editAddress->setDocument(supplierAddress);
	ui->editTel->setText(supplier_telephon);
	ui->editMob->setText(supplier_mob);
	ui->editWeb->setText(supplier_web);

	supplierId = supplier_id.toInt();
	if (supplierId > 0) {
		ui->buttonEdit->setEnabled(true);
		ui->buttonDelete->setEnabled(true);
	} else {
		ui->buttonEdit->setEnabled(false);
		ui->buttonDelete->setEnabled(false);
	}
}

void AtpCompanySuppliers::resetVars(){
	supplierId = 0;
	seEediteaza = false;
	eNou = false;
	eVechi = false;
}
