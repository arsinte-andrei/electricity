#include "AtpClientMaterials.h"
#include "ui/uiAtpClientMaterials.h"
#include "AtpSqlQuery.h"

#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDebug>

AtpClientMaterials::AtpClientMaterials(QString clientName, QWidget *parent) :	QWidget(parent), ui(new Ui::AtpClientMaterials) {
	this->clientName = clientName;
	ui->setupUi(this);

	data = new QMap<QString, QVariant>;
	model = new QSqlTableModel(this, AtpSqlQuery::getDbConnection(this->clientName));
	proxyModel = new QSortFilterProxyModel(this);
	modelCombo = new QSqlRelationalTableModel(this, AtpSqlQuery::getDbConnection("comp"));
	proxyModelCombo = new QSortFilterProxyModel;
	myCompletear = new QCompleter;
	tableViewCombo = new QTableView;
	updateDb();

	connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onButtonOkClicked()));
	connect(ui->buttonNew, SIGNAL(clicked()), this, SLOT(onButtonNewClicked()));
	connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(onButtonDeleteClicked()));
	connect(ui->buttonEdit, SIGNAL(clicked()), this, SLOT(onButtonEditClicked()));
	connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(onButtonCancelClicked()));
	connect(ui->tableMaterials, SIGNAL(clicked(QModelIndex)), this, SLOT(onTableMaterialsClicked(QModelIndex)));
	connect(ui->editSearch, SIGNAL(textChanged(QString)), this, SLOT(onEditSearchTextChanged(QString)));
	connect(ui->comboMaterial, SIGNAL(currentTextChanged(QString)), this, SLOT(onComboSupplierCurrentTextChanged(QString)));
	connect(ui->comboMaterial, SIGNAL(currentIndexChanged(QString)), this, SLOT(onComboSupplierIndexChanged(QString)));
}

AtpClientMaterials::~AtpClientMaterials() {
	delete ui;
//	delete data, modelCombo, model, proxyModelCombo, proxyModel, myCompletear, tableViewCombo;
}

void AtpClientMaterials::updateDb() {
	ui->enableAndDisable("reset");
	resetVars();

	model->setTable("cl_materiale_t");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->setHeaderData(0, Qt::Horizontal,"Id");
	model->setHeaderData(1, Qt::Horizontal,"Material");
	model->setHeaderData(2, Qt::Horizontal,"Quantity");
	model->setHeaderData(3, Qt::Horizontal,"Buy");
	model->setHeaderData(4, Qt::Horizontal,"Sale");
	model->setHeaderData(5, Qt::Horizontal,"Supplier");
	model->select();


	proxyModel->setSourceModel(model);
	proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	ui->tableMaterials->setModel(proxyModel);
	ui->tableMaterials->setSortingEnabled(true);
	ui->tableMaterials->setColumnHidden(0, true);
//	ui->tableMaterials->setColumnWidth(1, 300);
//	ui->tableMaterials->setColumnWidth(2, 100);
//	ui->tableMaterials->setColumnWidth(3, 100);
//	ui->tableMaterials->setColumnWidth(4, 150);

	modelCombo->setTable("comp_materiale_t");
	modelCombo->setEditStrategy(QSqlTableModel::OnManualSubmit);
	modelCombo->setRelation(4, QSqlRelation("comp_supplier_t", "supplier_id", "supplier_name"));
//	modelCombo->setHeaderData(0, Qt::Horizontal,"Id");
	modelCombo->setHeaderData(1, Qt::Horizontal,"Material");
//	modelCombo->setHeaderData(2, Qt::Horizontal,"Buy");
//	modelCombo->setHeaderData(3, Qt::Horizontal,"Sale");
	modelCombo->setHeaderData(4, Qt::Horizontal,"Supplier");
	modelCombo->select();
	tableViewCombo->setModel(modelCombo);
	tableViewCombo->setColumnHidden(0, true);
	tableViewCombo->setColumnHidden(2, true);
	tableViewCombo->setColumnHidden(3, true);
	tableViewCombo->setColumnWidth(1,190);
	ui->comboMaterial->setModel(modelCombo);
	tableViewCombo->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableViewCombo->setSelectionMode(QAbstractItemView::SingleSelection);
	tableViewCombo->setAlternatingRowColors(true);
	ui->comboMaterial->setView(tableViewCombo);
	ui->comboMaterial->view()->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->comboMaterial->view()->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->comboMaterial->view()->setAlternatingRowColors(true);
	ui->comboMaterial->setModelColumn(1);
	ui->comboMaterial->setCurrentIndex(-1);
	ui->comboMaterial->setEditable(true);

	proxyModelCombo->setSourceModel(modelCombo);
	proxyModelCombo->setFilterCaseSensitivity(Qt::CaseInsensitive);
	proxyModelCombo->setFilterKeyColumn(1);

	myCompletear->setCaseSensitivity(Qt::CaseInsensitive);
	myCompletear->setModel(proxyModelCombo);
	myCompletear->setCompletionColumn(1);
	myCompletear->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
	ui->comboMaterial->setCompleter(myCompletear);
}

void AtpClientMaterials::onButtonOkClicked(){
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

void AtpClientMaterials::resetVars(){
	matId = 0;
	seEediteaza = false;
	eNou = false;
	eVechi = false;
}

void AtpClientMaterials::onButtonNewClicked(){
	QString buttonName;
	buttonName = ui->buttonNew->text();
	if ( buttonName == "New"){
		ui->enableAndDisable("new");
		seEediteaza = true;
		eNou = true;
	} else {
		int comboRow = ui->comboMaterial->currentIndex();
		data->clear();
		data->insert(":mat_name", modelCombo->record(comboRow).value("mat_name").toString());
		data->insert(":mat_price1", ui->editBuy->text());
		data->insert(":mat_price2", ui->editSale->text());
		data->insert(":mat_quantity", ui->editQuantity->text());
		data->insert(":mat_supplier_name", modelCombo->record(comboRow).value("supplier_name").toString());
		AtpSqlQuery::atpInsert(this->clientName, "cl_materiale_t", data);
		model->select();
		ui->enableAndDisable("reset");
		resetVars();
		qDebug() << modelCombo->record(comboRow).value("supplier_name").toString();
	}
}

void AtpClientMaterials::onButtonDeleteClicked(){
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
			AtpSqlQuery::atpDelete(this->clientName, "cl_materiale_t", whereTo);
			model->select();
			ui->enableAndDisable("reset");
			resetVars();}
			break;
		default:
			break;
	}
}

void AtpClientMaterials::onButtonEditClicked(){
	QString buttonName;
	buttonName = ui->buttonEdit->text();
	if ( buttonName == "Edit"){
		ui->enableAndDisable("edit");
		seEediteaza = true;
		eVechi = true;
	} else {
		int combo_Id = ui->comboMaterial->currentIndex();
		data->clear();
		data->insert(":mat_id", matId);
		data->insert(":mat_name", modelCombo->record(combo_Id).value("mat_name").toString());
		data->insert(":mat_price1", ui->editBuy->text());
		data->insert(":mat_price2", ui->editSale->text());
		data->insert(":mat_quantity", ui->editQuantity->text());
		data->insert(":mat_supplier_id", modelCombo->record(combo_Id).value(0).toString());
		AtpSqlQuery::atpUpdate(this->clientName, "cl_materiale_t", data, "mat_id = :mat_id");
		model->select();
		ui->enableAndDisable("reset");
		resetVars();
	}
}

void AtpClientMaterials::onButtonCancelClicked(){
	if (seEediteaza){
		ui->enableAndDisable("reset");
		resetVars();
	} else {
		this->close();
		emit exitSignal();
	}
}

void AtpClientMaterials::onEditSearchTextChanged(const QString &arg1){
	int columnToSort = proxyModel->sortColumn();
	if (columnToSort < 1) {
		columnToSort = 1;
	}
	proxyModel->setFilterKeyColumn(columnToSort);
	proxyModel->setFilterFixedString(arg1);
}

void AtpClientMaterials::onTableMaterialsClicked(const QModelIndex &index){
	int rand = index.row();
	QString mat_id = ui->tableMaterials->model()->data(ui->tableMaterials->model()->index(rand,0)).toString();
	QString mat_price1 = ui->tableMaterials->model()->data(ui->tableMaterials->model()->index(rand,2)).toString();
	QString mat_price2 = ui->tableMaterials->model()->data(ui->tableMaterials->model()->index(rand,3)).toString();
	QString mat_supplier_id = ui->tableMaterials->model()->data(ui->tableMaterials->model()->index(rand,4)).toString();

//	ui->editBuy->setText(mat_price1);
//	ui->editSale->setText(mat_price2);

	int i = ui->comboMaterial->findText(mat_supplier_id);
	ui->comboMaterial->setCurrentIndex(i);

	matId = mat_id.toInt();
	if (matId > 0) {
		ui->buttonEdit->setEnabled(true);
		ui->buttonDelete->setEnabled(true);
	} else {
		ui->buttonEdit->setEnabled(false);
		ui->buttonDelete->setEnabled(false);
	}
}

void AtpClientMaterials::onComboSupplierCurrentTextChanged(const QString &arg1){
	if ( !arg1.isEmpty()) {
		proxyModelCombo->setFilterFixedString(arg1);
	}
}

void AtpClientMaterials::onComboSupplierIndexChanged(const QString &arg1){
	bool passBy = true;
	int rand = 0;
	QModelIndexList mySelection = ui->comboMaterial->view()->selectionModel()->selectedIndexes();
	//FIXME cand se selecteaa din prima using search function programul da eroare

	qDebug() << arg1;
	qDebug() <<mySelection[0].data(Qt::DisplayRole).toString();
	qDebug() << mySelection;

	if (mySelection[0].data(Qt::DisplayRole).toString() != arg1){
		passBy = false;
		while (passBy == false /*|| rand < ui->comboMaterial->model()->rowCount()*/) {

			qDebug() << "in while";
			qDebug() <<ui->comboMaterial->model()->data(ui->comboMaterial->model()->index(rand,1)).toString();
			qDebug () <<arg1;

			if(ui->comboMaterial->model()->data(ui->comboMaterial->model()->index(rand,1)).toString() == arg1){
				passBy = true;
				ui->comboMaterial->setCurrentIndex(rand);
				qDebug () <<"BREAK";
				//break;
			} else {
				qDebug() << "RAND:" <<rand;
				rand++;
			}
		}
	} else {
		qDebug() << "ELSE";
		QModelIndex currentIndex = mySelection[0];
		qDebug()<< mySelection[0].data(Qt::DisplayRole).toString();
		rand = currentIndex.row();
	}
	qDebug() << rand;

	qDebug()<< ui->comboMaterial->model()->data(ui->comboMaterial->model()->index(rand,0)).toString();//id
	QString matName = ui->comboMaterial->model()->data(ui->comboMaterial->model()->index(rand,1)).toString();//name
	double matBuy = ui->comboMaterial->model()->data(ui->comboMaterial->model()->index(rand,2)).toDouble();//buy
	double matSale = ui->comboMaterial->model()->data(ui->comboMaterial->model()->index(rand,3)).toDouble();//sale
	matSupplier = ui->comboMaterial->model()->data(ui->comboMaterial->model()->index(rand,4)).toString();//supplier

	ui->editBuy->setValue(matBuy);
	ui->editSale->setValue(matSale);
}
