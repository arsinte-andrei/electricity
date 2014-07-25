#include "AtpMainWindow.h"

#include <QtGui>
#include <QMenuBar>
#include <QMdiArea>
#include <QStatusBar>
#include <QTabBar>

#include "AtpSettings.h"
#include "AtpSingleApplication.h"
#include "AtpChuseCompany.h"
#include "AtpEditCompany.h"
#include "AtpToolsSettings.h"
#include "AtpDb.h"

AtpMainWindow::AtpMainWindow(QWidget *parent) : QMainWindow(parent){

	mdiArea = new QMdiArea;
	mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	mdiArea->setObjectName("MdiArea");
	mdiArea->setViewMode(QMdiArea::TabbedView);
	setCentralWidget(mdiArea);

//	connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateMenus()));

	setWindowTitle("@atp@");

	AtpSingleApplication *singleApp = qobject_cast<AtpSingleApplication *> (qApp);
	if (singleApp!=NULL) {
		singleApp->setActivationWindow(this);
	}

	toolBarComp = new QToolBar(tr("Company"), this);
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
	updateMenus();

	readSettings();
	restartDatabase();

	qDebug() << AtpDb::isOpen();
}

AtpMainWindow::~AtpMainWindow(){
	qDebug()<<"Exit AtpMainWindow";
//	AtpDb::uninit();
}

void AtpMainWindow::quit() {
	emit closeRequested();
	QMainWindow::close();
}

//event on close mainWindow
void AtpMainWindow::closeEvent(QCloseEvent *event) {
	qDebug()<<"Start closeEvent";
	mdiArea->closeAllSubWindows();
	if (mdiArea->currentSubWindow()) {
		event->ignore();
	} else {
		writeSettings();
		AtpDb::uninit();
		event->accept();
		//QApplication::quit();
	}
}

//save any unsaved data
bool AtpMainWindow::maybeSave(){
	return true;
}

void AtpMainWindow::createActions(){
//File
	//exit App
	actFileExit = new QAction(QIcon(":/exit.png"), tr("E&xit"), this);
	actFileExit->setShortcuts(QKeySequence::Quit);
	actFileExit->setStatusTip(tr("Exit the application"));
	connect(actFileExit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
//Company
	//chuse Company
	actCompChuse = new QAction(QIcon(":/select_comp.png"), tr("Ch&use Company"), this);
	actCompChuse->setStatusTip(tr("Chuse a Company from a list of companyes available"));
	connect(actCompChuse, SIGNAL(triggered()), this, SLOT(onActCompChuseCompany()));
	//edit Company
	actCompEdit = new QAction(QIcon(":/edit_comp.png"), tr("&Edit Company list"), this);
	actCompEdit->setStatusTip(tr("Edit the list of companyes"));
	connect(actCompEdit, SIGNAL(triggered()), this, SLOT(onActCompEditCompany()));
	//edit suppliers
	actCompSuppliers = new QAction(QIcon(":/suppliers.png"), tr("Edit &suppliers list"), this);
	actCompSuppliers->setStatusTip(tr("Edit the list of suppliers"));
	//edit client list
	actCompClients = new QAction(QIcon(":/clients.png"), tr("Edit &clients list"), this);
	actCompClients->setStatusTip(tr("Edit the list of clients"));
//Module
	//invoices
	actModulesInvoices = new QAction(QIcon(":/invoice.png"), tr("Invoices"), this);
	actModulesInvoices->setStatusTip(tr("Manage the invoices"));
	//receipt
	actModulesReceipt = new QAction(QIcon(":/receipt.png"), tr("Receipts"), this);
	actModulesReceipt->setStatusTip(tr("Manage the receipts"));
	//quotes
	actModulesQuotes = new QAction(QIcon(":/quotes.png"), tr("Quotes"), this);
	actModulesQuotes->setStatusTip(tr("Manage the quotes"));
	//group place
	actModulesGroupPlace = new QAction(QIcon(":/place.png"), tr("Group place"), this);
	actModulesGroupPlace->setStatusTip(tr("Manage the item place"));
	//points
	actModulesPoints = new QAction(QIcon(":/points.png"), tr("Points"), this);
	actModulesPoints->setStatusTip(tr("Manage the points price"));
	//materials
	actModulesMaterials = new QAction(QIcon(":/materials.png"), tr("Materials"), this);
	actModulesMaterials->setStatusTip(tr("Manage the materials used on jobs"));
//Tools
	//Users
	actToolsUsers = new QAction(QIcon(":/users.png"), tr("Users"), this);
	actToolsUsers->setStatusTip(tr("Manage the users of this application"));
	//Settings
	actToolsSettings = new QAction(QIcon(":/settings.png"), tr("Settings"), this);
	actToolsSettings->setStatusTip(tr("Settings management"));
	connect(actToolsSettings, SIGNAL(triggered()), this, SLOT(onActToolsSettings()));
//Reports
	//Reports
	actReportsReports = new QAction(QIcon(":/reports.png"), tr("Reports"), this);
	actReportsReports->setStatusTip(tr("Reports and printing system"));
	//Templates
	actReportsTemplates = new QAction(QIcon(":/template.png"), tr("Templates"), this);
	actReportsTemplates->setStatusTip(tr("Templates used for reports"));
//Help
	//Register
	actHelpRegister= new QAction(QIcon(":/register.png"), tr("Register..."), this);
	actHelpRegister->setStatusTip(tr("Register this app for full features..."));
	//Updates
	actHelpUpdates = new QAction(QIcon(":/update.png"), tr("Updates..."), this);
	actHelpUpdates->setStatusTip(tr("Check for last version or module updates"));
	//Help
	actHelpHelp = new QAction(QIcon(":/help.png"), tr("Help"), this);
	actHelpHelp->setStatusTip(tr("Show the main help"));
	//About
	actHelpAbout = new QAction(QIcon(":/info.png"), tr("&About"), this);
	actHelpAbout->setStatusTip(tr("Show the application's About box"));
//	connect(actHelpAbout, SIGNAL(triggered()), this, SLOT(about()));

//Separator
	separatorAct = new QAction(this);
	separatorAct->setSeparator(true);

}

void AtpMainWindow::createMenus(){
//File Menu
	menuFile = menuBar()->addMenu(tr("&File"));
//	fileMenu->addSeparator();
	menuFile->addAction(actFileExit);
//Company Menu
	menuCompany = menuBar()->addMenu(tr("&Company"));
	menuCompany->addAction(actCompChuse);
	menuCompany->addAction(actCompEdit);
	menuCompany->addSeparator();
	menuCompany->addAction(actCompClients);
	menuCompany->addSeparator();
	menuCompany->addAction(actCompSuppliers);
//Modules Menu
	menuModules = menuBar()->addMenu(tr("&Modules"));
	menuModules->addAction(actModulesInvoices);
	menuModules->addAction(actModulesReceipt);
	menuModules->addAction(actModulesQuotes);
	menuModules->addSeparator();
	menuModules->addAction(actModulesGroupPlace);
	menuModules->addAction(actModulesPoints);
	menuModules->addAction(actModulesMaterials);
//Tools Menu
	menuTools = menuBar()->addMenu(tr("&Tools"));
	menuTools->addAction(actToolsUsers);
	menuTools->addSeparator();
	menuTools->addAction(actToolsSettings);
//Reporting Menu
	menuReporting = menuBar()->addMenu(tr("&Reports"));
	menuReporting->addAction(actReportsReports);
	menuReporting->addAction(actReportsTemplates);
//a separator
	menuBar()->addSeparator();
//Help
	menuHelp = menuBar()->addMenu(tr("&Help"));
	menuHelp->addAction(actHelpRegister);
	menuHelp->addAction(actHelpUpdates);
	menuHelp->addSeparator();
	menuHelp->addAction(actHelpHelp);
	menuHelp->addSeparator();
	menuHelp->addAction(actHelpAbout);
}

void AtpMainWindow::createToolBars(){

//	toolBarComp = addToolBar(tr("Company"));
	addToolBar(toolBarComp);
	toolBarComp->addAction(actCompChuse);
	toolBarComp->addAction(actCompEdit);
}

void AtpMainWindow::createStatusBar(){
	statusBar()->showMessage(tr("Ready"));
}

void AtpMainWindow::updateMenus(){
//	bool hasMdiChild = true; //(activeMdiChild() != 0);
//	closeAct->setEnabled(hasMdiChild);
//	closeAllAct->setEnabled(hasMdiChild);
	//	separatorAct->setVisible(hasMdiChild);
}

void AtpMainWindow::onActCompChuseCompany(){
	AtpChuseCompany *compChuseCompany = new AtpChuseCompany(this);
	compChuseCompany->setModal(true);
	if (compChuseCompany->exec() == QDialog::Accepted){
		//updateWindowTitle(true);
	}
}

void AtpMainWindow::onActCompEditCompany(){
	AtpEditCompany *companyEditor = new AtpEditCompany();
	mdiArea->addSubWindow(companyEditor);
	companyEditor->show();
	companyEditor->activateWindow();
	/*
	Or you can say a QWidget to work as a QDialog :)

	QWidget *yourWidget = new QWidget(this, Qt::Popup | Qt:: Dialog);

	//create your widget ....

	yourWidget ->setWindowModality(Qt::WindowModal);
	yourWidget ->show();*/
}

void AtpMainWindow::onActToolsSettings(){
	AtpToolsSettings *toolsSettings = new AtpToolsSettings(this);
	toolsSettings->setModal(true);
	connect(toolsSettings, SIGNAL(restartDatabase()), this, SLOT(restartDatabase()));
	toolsSettings->exec();
	delete toolsSettings;
}

void AtpMainWindow::restartDatabase(){
	qDebug() << "RESTART DATABASE!";
	AtpDb::uninit();
	AtpDb::getDataBase();
}

//Restores the application window settings (size, position, ...).
void AtpMainWindow::readSettings() {
	qDebug()<<"readSettings";
	QPoint windowPos = AtpSettings::getPointValue("App/Position", QPoint(100, 100));
	QSize windowSize = AtpSettings::getSizeValue("App/Size", QSize(400, 300));
	resize(windowSize);
	move(windowPos);
}

// Stores the application window settings (size, position, ...).
void AtpMainWindow::writeSettings() {
	qDebug()<<"writeSettings";
	AtpSettings::setValue("App/Position", pos());
	AtpSettings::setValue("App/Size", size());
	qDebug() << "C" << AtpSettings::getMySettings()->fileName();
}
