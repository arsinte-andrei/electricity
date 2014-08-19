#include "AtpClientEditList.h"
#include "ui/uiAtpClientEditList.h"
#include "AtpSettings.h"
#include "AtpSqlQuery.h"
#include "AtpDbClient.h"

#include <QMessageBox>
#include <QSqlQuery>

AtpClientEditList::AtpClientEditList(QWidget *parent) : QWidget(parent), ui(new Ui::AtpClientEditList){
	ui->setupUi(this);

	data = new QMap<QString, QVariant>;
	model = new QSqlTableModel(this, AtpSqlQuery::getDbConnection("comp"));
	updateDb();

	connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onButtonOkClicked()));
	connect(ui->buttonNew, SIGNAL(clicked()), this, SLOT(onButtonNewClicked()));
	connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(onButtonDeleteClicked()));
	connect(ui->buttonEdit, SIGNAL(clicked()), this, SLOT(onButtonEditClicked()));
	connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(onButtonCancelClicked()));
	connect(ui->tableClientList, SIGNAL(clicked(QModelIndex)), this, SLOT(onTableClientListClicked(QModelIndex)));
	connect(ui->editSearch, SIGNAL(textChanged(QString)), this, SLOT(onEditSearchTextEdited(QString)));
}

AtpClientEditList::~AtpClientEditList(){
	delete ui;
}

void AtpClientEditList::updateDb() {
	resetVars();
	ui->enableAndDisable("reset");
	model->setTable("comp_client_list_t");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->setHeaderData(0, Qt::Horizontal,"Id");
	model->setHeaderData(1, Qt::Horizontal,"Name");
	model->setHeaderData(2, Qt::Horizontal,"Address");
	model->setHeaderData(3, Qt::Horizontal,"Landline");
	model->setHeaderData(4, Qt::Horizontal,"Mobile");
	model->setHeaderData(5, Qt::Horizontal,"Mobile");
	model->setHeaderData(7, Qt::Horizontal,"File");

	proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(model);
	proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

	ui->tableClientList->setModel(proxyModel);
	ui->tableClientList->setSortingEnabled(true);
	ui->tableClientList->setColumnHidden(0, true);
	ui->tableClientList->setColumnWidth(1, 100);
	ui->tableClientList->setColumnWidth(2, 250);
	ui->tableClientList->setColumnWidth(3, 150);
	ui->tableClientList->setColumnWidth(4, 150);
	ui->tableClientList->setColumnWidth(5, 150);
	ui->tableClientList->setColumnWidth(6, 150);
	ui->tableClientList->setColumnWidth(7, 150);
	ui->tableClientList->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableClientList->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableClientList->setAlternatingRowColors(true);
	ui->tableClientList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	model->select();
	//ui->companyTableView->verticalHeader()->setStyleSheet("QHeaderView::section:checked {"
//	" background-color: black; }"
//	" background-image: url(imgs/arrow.png)"
//	);
}

void AtpClientEditList::resetVars(){
	clientId = 0;
	clientName.clear();
	clientFileName.clear();
	seEediteaza = false;
	eNou = false;
	eVechi = false;
}

void AtpClientEditList::onButtonOkClicked(){
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

void AtpClientEditList::onButtonNewClicked(){
	QString buttonName;
	buttonName = ui->buttonNew->text();
	if ( buttonName == "New"){
		seEediteaza = true;
		eNou = true;
		ui->enableAndDisable("new");
	} else {
		data->clear();
		data->insert(":client_name", ui->editName->text());
		data->insert(":client_address", ui->editAddress->document()->toPlainText());
		data->insert(":client_tel", ui->editTel->text());
		data->insert(":client_mob", ui->editMob->text());
		data->insert(":client_email", ui->editMail->text());

		QString clientFileName = ui->editName->text().remove(" ");
		if (clientFileName.isNull() || clientFileName.isEmpty()){
			QString mainWindowTitle = "Add new Client";
			QString infoText = "Client name can not be empty!";
			QMessageBox msgBox;
			msgBox.setWindowTitle(mainWindowTitle);
			msgBox.setText("Client name is empty.");
			msgBox.setInformativeText(infoText);
			msgBox.setStandardButtons(QMessageBox::Yes);
			msgBox.setDefaultButton(QMessageBox::Yes);
			msgBox.exec();
			return;
		}
		data->insert(":client_file", clientFileName);
		AtpSqlQuery::atpInsert("comp", "comp_client_list_t", data);
		QString compPath = AtpSettings::getStringValue("Company/Path", "");
		QString newClientDbPath = AtpSettings::getCompanyPath(compPath);
		AtpDbClient::createClientStructure(newClientDbPath, clientFileName);

//TODO daca nu s-a putut adauga se ia eroaread
		updateDb();
	}
}

void AtpClientEditList::onButtonDeleteClicked(){
	QString mainWindowTitle = "Delete " + clientName;
	QString infoText = "Are you shure you whant to delete the client: " + clientName + "?";
	QString moreInfoText = "Make shure that you want to delete " + clientName + "'s records, because after delete is not possible to bring it back except from back-up! \n Please note that this will also delete all the client's details: invoices, quotations, and so on...";
	QMessageBox msgBox;
	msgBox.setWindowTitle(mainWindowTitle);
	msgBox.setText("Delete a Client.");
	msgBox.setInformativeText(infoText);
	msgBox.setDetailedText(moreInfoText);
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	int ret = msgBox.exec();
	switch (ret) {
		case QMessageBox::No:
			ui->enableAndDisable("reset");
			resetVars();
			break;
		case QMessageBox::Yes:{
			QString whereTo = QString("client_id = %1").arg(clientId);

			QString compPath = AtpSettings::getStringValue("Company/Path", "");
			QString newClientDbPath = AtpSettings::getCompanyPath(compPath);
			QString clientDbFilename = newClientDbPath + "/" + clientFileName.append(".atpdb");
			QFile delMe;
			delMe.setFileName(clientDbFilename);
			if(delMe.remove()) {
				AtpSqlQuery::atpDelete("comp", "comp_client_list_t", whereTo);
			}
			updateDb();
		}
			break;
		default:
			break;
	}
}

void AtpClientEditList::onButtonEditClicked(){
	QString buttonName = ui->buttonEdit->text();
	if ( buttonName == "Edit"){
		seEediteaza = true;
		eVechi = true;
		ui->enableAndDisable("edit");
	} else {
		data->clear();
		data->insert(":client_id", clientId);
		data->insert(":client_name", ui->editName->text());
		data->insert(":client_address", ui->editAddress->document()->toPlainText());
		data->insert(":client_tel", ui->editTel->text());
		data->insert(":client_mob", ui->editMob->text());
		data->insert(":client_email", ui->editMail->text());
		AtpSqlQuery::atpUpdate("comp", "comp_client_list_t", data, "client_id = :client_id");
		updateDb();
	}
}

void AtpClientEditList::onButtonCancelClicked(){
	if (seEediteaza){
		ui->enableAndDisable("reset");
		resetVars();
	} else {
		this->close();
		emit exitSignal();
	}
}

void AtpClientEditList::onTableClientListClicked(const QModelIndex &index){
	int rand = index.row();
	QString client_id = ui->tableClientList->model()->data(ui->tableClientList->model()->index(rand,0)).toString();
	QString client_name = ui->tableClientList->model()->data(ui->tableClientList->model()->index(rand,1)).toString();
	QString client_address = ui->tableClientList->model()->data(ui->tableClientList->model()->index(rand,2)).toString();
	QString client_tel = ui->tableClientList->model()->data(ui->tableClientList->model()->index(rand,3)).toString();
	QString client_mob = ui->tableClientList->model()->data(ui->tableClientList->model()->index(rand,4)).toString();
	QString client_email = ui->tableClientList->model()->data(ui->tableClientList->model()->index(rand,5)).toString();
	clientFileName = ui->tableClientList->model()->data(ui->tableClientList->model()->index(rand,6)).toString();

	QTextDocument *clientAddress= new QTextDocument(ui->editAddress);
	clientAddress->setPlainText(client_address);
	QPlainTextDocumentLayout *layout = new QPlainTextDocumentLayout(clientAddress);
	clientAddress->setDocumentLayout(layout);

	ui->editName->setText(client_name);
	ui->editMail->setText(client_email);
	ui->editAddress->setDocument(clientAddress);
	ui->editTel->setText(client_tel);
	ui->editMob->setText(client_mob);

	clientId = client_id.toInt();
	clientName = client_name;
	if (clientId > 0) {
		ui->buttonEdit->setEnabled(true);
		ui->buttonDelete->setEnabled(true);
	} else {
		ui->buttonEdit->setEnabled(false);
		ui->buttonDelete->setEnabled(false);
	}
//	qDebug() << index.column();
}

void AtpClientEditList::onEditSearchTextEdited(const QString &arg1){
	int columnToSort = proxyModel->sortColumn();
	if (columnToSort < 1) {
		columnToSort = 1;
	}
	proxyModel->setFilterKeyColumn(columnToSort);
	proxyModel->setFilterFixedString(arg1);
}
