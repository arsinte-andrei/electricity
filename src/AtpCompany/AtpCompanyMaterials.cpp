#include "AtpCompanyMaterials.h"
#include "ui/uiAtpCompanyMaterials.h"
#include "AtpSqlQuery.h"

#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include <QMessageBox>

AtpCompanyMaterials::AtpCompanyMaterials(QWidget *parent) :	QWidget(parent), ui(new Ui::AtpCompanyMaterials) {
	ui->setupUi(this);

	data = new QMap<QString, QVariant>;
	model = new QSqlRelationalTableModel(this, AtpSqlQuery::getDbConnection("comp"));
	modelCombo = new QSqlTableModel(this, AtpSqlQuery::getDbConnection("comp"));
	proxyModelCombo = new QSortFilterProxyModel(this);
	myCompletear = new QCompleter(this);
	updateDb();

	connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onButtonOkClicked()));
	connect(ui->buttonNew, SIGNAL(clicked()), this, SLOT(onButtonNewClicked()));
	connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(onButtonDeleteClicked()));
	connect(ui->buttonEdit, SIGNAL(clicked()), this, SLOT(onButtonEditClicked()));
	connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(onButtonCancelClicked()));
	connect(ui->tableMaterials, SIGNAL(clicked(QModelIndex)), this, SLOT(onTableMaterialsClicked(QModelIndex)));
	connect(ui->editSearch, SIGNAL(textChanged(QString)), this, SLOT(onEditSearchTextChanged(QString)));
	connect(ui->comboSupplier, SIGNAL(currentTextChanged(QString)), this, SLOT(onComboSupplierCurrentTextChanged(QString)));
}

AtpCompanyMaterials::~AtpCompanyMaterials() {
	delete ui;
}

void AtpCompanyMaterials::updateDb() {
	ui->enableAndDisable("reset");
	resetVars();

	model->setTable("comp_materiale_t");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->setRelation(4, QSqlRelation("comp_supplier_t", "supplier_id", "supplier_name"));
	model->setHeaderData(0, Qt::Horizontal,"Id");
	model->setHeaderData(1, Qt::Horizontal,"Name");
	model->setHeaderData(2, Qt::Horizontal,"Buy");
	model->setHeaderData(3, Qt::Horizontal,"Sale");
	model->setHeaderData(4, Qt::Horizontal,"Supplier");
	model->select();

	proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(model);
	proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	ui->tableMaterials->setModel(proxyModel);
	ui->tableMaterials->setSortingEnabled(true);
	ui->tableMaterials->setItemDelegate(new QSqlRelationalDelegate(ui->tableMaterials));
	ui->tableMaterials->setColumnHidden(0, true);
	ui->tableMaterials->setColumnWidth(1, 300);
	ui->tableMaterials->setColumnWidth(2, 100);
	ui->tableMaterials->setColumnWidth(3, 100);
	ui->tableMaterials->setColumnWidth(4, 150);

	modelCombo = model->relationModel(4);
	ui->comboSupplier->setModel(modelCombo);
	ui->comboSupplier->setModelColumn(1);
	ui->comboSupplier->setDuplicatesEnabled(false);
	ui->comboSupplier->setCurrentIndex(-1);
	ui->comboSupplier->setEditable(true);

	proxyModelCombo->setSourceModel(modelCombo);
	proxyModelCombo->setFilterCaseSensitivity(Qt::CaseInsensitive);
	proxyModelCombo->setFilterKeyColumn(1);

	myCompletear->setCaseSensitivity(Qt::CaseInsensitive);
	myCompletear->setModel(proxyModelCombo);
	myCompletear->setCompletionColumn(1);
	myCompletear->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
	ui->comboSupplier->setCompleter(myCompletear);
}

void AtpCompanyMaterials::onButtonOkClicked(){
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

void AtpCompanyMaterials::resetVars(){
	matId = 0;
	seEediteaza = false;
	eNou = false;
	eVechi = false;
}

void AtpCompanyMaterials::onButtonNewClicked(){
	QString buttonName;
	buttonName = ui->buttonNew->text();
	if ( buttonName == "New"){
		ui->enableAndDisable("new");
		seEediteaza = true;
		eNou = true;
	} else {
		int combo_Id = ui->comboSupplier->currentIndex();
		data->clear();
		data->insert(":mat_name", ui->editName->text());
		data->insert(":mat_price1", ui->editBuy->text());
		data->insert(":mat_price2", ui->editSale->text());
		data->insert(":mat_supplier_id", modelCombo->record(combo_Id).value(0).toString());
		AtpSqlQuery::atpInsert("comp", "comp_materiale_t", data);
		updateDb();
	}
}

void AtpCompanyMaterials::onButtonDeleteClicked(){
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
			QString whereTo = QString("mat_id = %1").arg(matId);
			AtpSqlQuery::atpDelete("comp", "comp_materiale_t", whereTo);
			updateDb();}
			break;
		default:
			break;
	}
}

void AtpCompanyMaterials::onButtonEditClicked(){
	QString buttonName;
	buttonName = ui->buttonEdit->text();
	if ( buttonName == "Edit"){
		ui->enableAndDisable("edit");
		seEediteaza = true;
		eVechi = true;
	} else {
		int combo_Id = ui->comboSupplier->currentIndex();
		data->clear();
		data->insert(":mat_id", matId);
		data->insert(":mat_name", ui->editName->text());
		data->insert(":mat_price1", ui->editBuy->text());
		data->insert(":mat_price2", ui->editSale->text());
		data->insert(":mat_supplier_id", modelCombo->record(combo_Id).value(0).toString());
		AtpSqlQuery::atpUpdate("comp", "comp_materiale_t", data, "mat_id = :mat_id");

		updateDb();
	}
}

void AtpCompanyMaterials::onButtonCancelClicked(){
	if (seEediteaza){
		ui->enableAndDisable("reset");
		resetVars();
	} else {
		this->close();
		emit exitSignal();
	}
}

void AtpCompanyMaterials::onEditSearchTextChanged(const QString &arg1){
	int columnToSort = proxyModel->sortColumn();
	if (columnToSort < 1) {
		columnToSort = 1;
	}
	proxyModel->setFilterKeyColumn(columnToSort);
	proxyModel->setFilterFixedString(arg1);
}

void AtpCompanyMaterials::onTableMaterialsClicked(const QModelIndex &index){
	int rand = index.row();
	QString mat_id = ui->tableMaterials->model()->data(ui->tableMaterials->model()->index(rand,0)).toString();
	QString mat_name = ui->tableMaterials->model()->data(ui->tableMaterials->model()->index(rand,1)).toString();
	QString mat_price1 = ui->tableMaterials->model()->data(ui->tableMaterials->model()->index(rand,2)).toString();
	QString mat_price2 = ui->tableMaterials->model()->data(ui->tableMaterials->model()->index(rand,3)).toString();
	QString mat_supplier_id = ui->tableMaterials->model()->data(ui->tableMaterials->model()->index(rand,4)).toString();

	ui->editName->setText(mat_name);
	ui->editBuy->setText(mat_price1);
	ui->editSale->setText(mat_price2);

	int i = ui->comboSupplier->findText(mat_supplier_id);
	ui->comboSupplier->setCurrentIndex(i);

	matId = mat_id.toInt();
	if (matId > 0) {
		ui->buttonEdit->setEnabled(true);
		ui->buttonDelete->setEnabled(true);
	} else {
		ui->buttonEdit->setEnabled(false);
		ui->buttonDelete->setEnabled(false);
	}
}

void AtpCompanyMaterials::onComboSupplierCurrentTextChanged(const QString &arg1){
	if ( !arg1.isEmpty()) {
		proxyModelCombo->setFilterFixedString(arg1);
	}
}

