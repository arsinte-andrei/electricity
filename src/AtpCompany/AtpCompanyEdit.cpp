#include "AtpCompanyEdit.h"
#include "ui/uiAtpCompanyEdit.h"

#include "AtpDbComp.h"
#include "AtpSqlQuery.h"
#include "AtpSettings.h"

#include <QDir>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

AtpCompanyEdit::AtpCompanyEdit(QWidget *parent) : QWidget(parent), ui(new Ui::AtpCompanyEdit){
	ui->setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose);

	data = new QMap<QString, QVariant>;
	model = new QSqlTableModel(this, AtpSqlQuery::getDbConnection("main"));
	updateDb();

	connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onButtonOkClicked()));
	connect(ui->buttonNew, SIGNAL(clicked()), this, SLOT(onButtonNewClicked()));
	connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(onButtonDeleteClicked()));
	connect(ui->buttonEdit, SIGNAL(clicked()), this, SLOT(onButtonEditClicked()));
	connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(onButtonCancelClicked()));
	connect(ui->tableViewCompany, SIGNAL(clicked(QModelIndex)), this, SLOT(onTableViewCompanyClicked(QModelIndex)));
	connect(ui->editSearch, SIGNAL(textChanged(QString)), this, SLOT(onEditSearchTextChanged(QString)));
}

AtpCompanyEdit::~AtpCompanyEdit(){
	delete ui;
}

void AtpCompanyEdit::onButtonOkClicked(){
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

void AtpCompanyEdit::onButtonNewClicked(){
	QString buttonName;
	buttonName = ui->buttonNew->text();
	if ( buttonName == "New"){
		ui->enableAndDisable("new");
		seEediteaza = true;
		eNou = true;
	} else {
		data->clear();
		data->insert(":comp_name", ui->editCompany->text());
		data->insert(":comp_addres", ui->editAddress->document()->toPlainText());
		data->insert(":comp_www", ui->editWebsite->text());
		data->insert(":comp_director", ui->editDirector->text());
		data->insert(":comp_tel", ui->editTel->text());
		data->insert(":comp_mob", ui->editMob->text());
		data->insert(":comp_email", ui->editMail->text());
		QString companyFileName = ui->editCompany->text().remove(" ");
		if ( companyFileName.isNull() || companyFileName.isEmpty()){
			QString mainWindowTitle = "Create new Company";
			QString infoText = "Company name can not be empty!";
			QMessageBox msgBox;
			msgBox.setWindowTitle(mainWindowTitle);
			msgBox.setText("Company name is empty.");
			msgBox.setInformativeText(infoText);
			msgBox.setStandardButtons(QMessageBox::Yes);
			msgBox.setDefaultButton(QMessageBox::Yes);
			msgBox.exec();
			return;
		}
		data->insert(":comp_file", companyFileName);
		AtpSqlQuery::atpInsert("main", "m_company_t", data);
		QString newDbPath = AtpSettings::getCompanyPath(companyFileName, true);
		AtpDbComp::createCompanyStructure(newDbPath, companyFileName);

//TODO sa stie utilizatorul in caz ca nu a intrat in baza de date si sa se scrie un log
		updateDb();
	}
}

void AtpCompanyEdit::onButtonDeleteClicked(){
	QString mainWindowTitle = "Delete " + compName;
	QString infoText = "Are you shure you whant to delete the company: " + compName + "?";
	QString moreInfoText = "Make shure that you want to delete " + compName + " company, because after delete is not possible to bring it back except from back-up! \n Please note that this will also delete all the company details: invoices, quotations, and so on...";
	QMessageBox msgBox;
	msgBox.setWindowTitle(mainWindowTitle);
	msgBox.setText("Delete a Company.");
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
			QString whereTo = QString("comp_id = %1").arg(compId);
			QString delCompDbPath = AtpSettings::getCompanyPath(compPath);
			QDir delCompDir = QDir(delCompDbPath);
			if(delCompDir.removeRecursively()) {
				AtpSqlQuery::atpDelete("main", "m_company_t", whereTo);
			}
			updateDb();
		}
			break;
		default:
			break;
	}
}

void AtpCompanyEdit::onButtonEditClicked(){
	QString buttonName;
	buttonName = ui->buttonEdit->text();
	if ( buttonName == "Edit"){
		ui->enableAndDisable("edit");
		seEediteaza = true;
		eVechi = true;
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
		AtpSqlQuery::atpUpdate("main", "m_company_t", data, "comp_id = :comp_id");
		updateDb();
	}
}

void AtpCompanyEdit::onButtonCancelClicked(){
	if (seEediteaza){
		ui->enableAndDisable("reset");
		resetVars();
	} else {
		this->close();
		emit exitSignal();
	}
}

void AtpCompanyEdit::onTableViewCompanyClicked(const QModelIndex &index){
	int rand = index.row();
	QString comp_id = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,0)).toString();
	QString comp_name = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,1)).toString();
	QString comp_dir = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,4)).toString();
	QString comp_address = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,2)).toString();
	QString comp_web = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,3)).toString();
	QString comp_tel = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,5)).toString();
	QString comp_mob = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,6)).toString();
	QString comp_email = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,7)).toString();
	compPath = ui->tableViewCompany->model()->data(ui->tableViewCompany->model()->index(rand,8)).toString();

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
		compName = comp_name;
	} else {
		ui->buttonEdit->setEnabled(false);
		ui->buttonDelete->setEnabled(false);
	}
//	qDebug() << index.column();
}

void AtpCompanyEdit::updateDb() {
	ui->enableAndDisable("reset");
	resetVars();

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

void AtpCompanyEdit::resetVars(){
	compName.clear();
	compPath.clear();
	compId = 0;
	seEediteaza = false;
	eNou = false;
	eVechi = false;
}

void AtpCompanyEdit::onEditSearchTextChanged(const QString &arg1){
	int columnToSort = proxyModel->sortColumn();
	if (columnToSort < 1) {
		columnToSort = 1;
	}
	proxyModel->setFilterKeyColumn(columnToSort);
	proxyModel->setFilterFixedString(arg1);
}
