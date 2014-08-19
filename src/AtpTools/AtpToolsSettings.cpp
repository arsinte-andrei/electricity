#include "AtpToolsSettings.h"
#include "ui_AtpToolsSettings.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>

#include "AtpSettings.h"
#include "AtpDbMain.h"


AtpToolsSettings::AtpToolsSettings(QWidget *parent) : QDialog(parent), ui(new Ui::AtpToolsSettings){
	ui->setupUi(this);
	qDebug() << "o noua instanta de tools settings";
	restartDb = false;
	resetAll();
	connect(this, SIGNAL(settingsChanged()), this, SLOT(onSettingsChanged()));

	connect(this, SIGNAL(accepted()), this, SLOT(onCloseDialog()));
	connect(this, SIGNAL(rejected()), this, SLOT(onCloseDialog()));
	connect(this, SIGNAL(dialogIsClosing()), this, SLOT(onCloseDialog()));
}

AtpToolsSettings::~AtpToolsSettings(){
	delete ui;
}

void AtpToolsSettings::processChanged(){
	if(changed){
		if(changedDbFilePath){
			AtpSettings::setValue("Db/Path", ui->editPathOpen->text());
			restartDb = true;
		}
		if(changedDiscountSuffix){
			AtpSettings::setValue("Discount/Sufix", ui->editDiscountSuffix->text());
		}
		if(changedDiscountPrefix){
			AtpSettings::setValue("Discount/Prefix", ui->editDiscountPrefix->text());
		}
		if(changedCurrancySuffix){
			AtpSettings::setValue("Currancy/Sufix", ui->editCurrencySuffix->text());
		}
		if(changedCurrancyPrefix){
			AtpSettings::setValue("Currancy/Prefix", ui->editCurrencyPrefix->text());
		}
		if(changedAutoLoadCompany){
			AtpSettings::setValue("Company/Autoload", ui->checkBoxAutoLoadCompany->checkState());
		}
	}
	resetAll();
}

void AtpToolsSettings::resetAll(){
//TAB 1
	ui->editPathOpen->setText(AtpSettings::getStringValue("Db/Path", ""));
//TAB 2
	ui->editCurrencyPrefix->setText(AtpSettings::getStringValue("Currancy/Prefix", ""));
	ui->editCurrencySuffix->setText(AtpSettings::getStringValue("Currancy/Sufix", ""));
	ui->editDiscountPrefix->setText(AtpSettings::getStringValue("Discount/Prefix", ""));
	ui->editDiscountSuffix->setText(AtpSettings::getStringValue("Discount/Sufix", ""));
//TAB 3
	int autoloadCompStatus = AtpSettings::getIntValue("Company/Autoload", 0);
	switch (autoloadCompStatus) {
		case 0:
			ui->checkBoxAutoLoadCompany->setCheckState(Qt::Unchecked);
			break;
		case 1:
			ui->checkBoxAutoLoadCompany->setCheckState(Qt::PartiallyChecked);
			break;
		case 2:
			ui->checkBoxAutoLoadCompany->setCheckState(Qt::Checked);
			break;
		default:
			break;
	}

//ALL TABS
	changed = false;
	ui->buttonApply->setEnabled(false);
//TAB 1
	changedDbFilePath = false;
//TAB 2
	changedDiscountSuffix =false;
	changedDiscountPrefix = false;
	changedCurrancySuffix = false;
	changedCurrancyPrefix = false;
//TAB 3
	changedAutoLoadCompany = false;
}

void AtpToolsSettings::closeEvent(QCloseEvent *event){
	emit dialogIsClosing();
	event->accept();
}

void AtpToolsSettings::onCloseDialog(){
	if (restartDb){
		emit restartDatabase();
	}
}

//APPLY BUTTON
void AtpToolsSettings::on_buttonApply_clicked(){
	if(changed){
		processChanged();
	}
}

//CANCEL BUTTON
void AtpToolsSettings::on_buttonCancel_clicked(){
	this->reject();
}

//Ok BUTTON
void AtpToolsSettings::on_buttonOk_clicked(){
	if(changed){
		processChanged();
	}
	this->accept();
}

void AtpToolsSettings::on_tabMainSettings_currentChanged(int index){
	qDebug() << index;
	if(changed){
		QMessageBox msgBox;
		msgBox.setText("Save changes?");
		msgBox.setInformativeText("The form has been modified? would you like to save the changes?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::Yes);
		int ret = msgBox.exec();
		switch (ret) {
			case QMessageBox::No:
				resetAll();
				break;
			case QMessageBox::Yes:
					processChanged();
				break;
			default:
				break;
		}
	}
}

//TAB 1
void AtpToolsSettings::on_buttonOpenFile_clicked(){
	QString oldPath = ui->editPathOpen->text();
	QString dbFileName = QFileDialog::getOpenFileName(this,
							   tr("Find dataBase file"),
								AtpSettings::getDataBasePath(),
								tr("atp dataBase(*.main.atpdb)"));

	if (!dbFileName.isEmpty() && oldPath != dbFileName) {
		ui->editPathOpen->setText(dbFileName);
		emit settingsChanged();
		changedDbFilePath = true;
		qDebug() << "nu e gol si e diferit";
	}
}

void AtpToolsSettings::on_editPathOpen_textEdited(const QString &arg1){
	Q_UNUSED(arg1);
	emit settingsChanged();
	changedDbFilePath = true;
}

void AtpToolsSettings::onSettingsChanged(){
	changed = true;
	ui->buttonApply->setEnabled(true);
}

void AtpToolsSettings::on_buttonCreateDataBase_clicked(){
	QString dbFileName = QFileDialog::getSaveFileName(this,
							   tr("Create new atp dataBase file"),
								AtpSettings::getDataBasePath(),
								tr("atp dataBase(*.main.atpdb)"));
	if (!dbFileName.isEmpty()){
		if (!dbFileName.endsWith(".main.atpdb")){
			dbFileName.append(".main.atpdb");
		}

		if (AtpDbMain::createMainSQLiteDb(dbFileName)) {
			ui->editPathOpen->setText(dbFileName);
			AtpSettings::setValue("Db/Path", dbFileName);
			restartDb = true;
		}
	}
}

//TAB 2
void AtpToolsSettings::on_editCurrencyPrefix_textEdited(){
	emit settingsChanged();
	changedCurrancyPrefix = true;
}

void AtpToolsSettings::on_editCurrencySuffix_textEdited(){
	emit settingsChanged();
	changedCurrancySuffix = true;
}

void AtpToolsSettings::on_editDiscountPrefix_textEdited(){
	emit settingsChanged();
	changedDiscountPrefix = true;
}

void AtpToolsSettings::on_editDiscountSuffix_textEdited(){
	emit settingsChanged();
	changedDiscountSuffix = true;
}

//TAB 3
void AtpToolsSettings::on_checkBoxAutoLoadCompany_stateChanged(){
	emit settingsChanged();
	changedAutoLoadCompany = true;
}
