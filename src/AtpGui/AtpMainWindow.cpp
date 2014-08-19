#include "AtpMainWindow.h"

#include <QtGui>
#include <QMenuBar>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QStatusBar>
#include <QTabBar>
#include <QSqlQuery>

#include "AtpSettings.h"
#include "AtpSingleApplication.h"
//company
#include "AtpCompanyChuse.h"
#include "AtpCompanyEdit.h"
#include "AtpCompanySuppliers.h"
#include "AtpCompanyMaterials.h"
#include "AtpCompanyPoints.h"
#include "AtpCompanyGroupPlace.h"
//clients
#include "AtpClientChuse.h"
#include "AtpClientEditList.h"
#include "AtpClientPoints.h"
//tools
#include "AtpToolsSettings.h"
//DB
#include "AtpDbMain.h"
#include "AtpDbComp.h"
#include "AtpDbClient.h"
#include "AtpSqlQuery.h"

AtpMainWindow::AtpMainWindow(QWidget *parent) : QMainWindow(parent){
	winTitleCompany.clear();
	winTitleClient.clear();
	appStatus = AtpDef::noDataBaseLoaded;

	mdiArea = new AtpMdiArea(this);
	mdiArea->setObjectName("MdiArea");
	setCentralWidget(mdiArea);

	connect(this, SIGNAL(windowResized(AtpDef::mainWindowLoadingStatus)), mdiArea, SLOT(setAtpBackground(AtpDef::mainWindowLoadingStatus)));
	connect(this, SIGNAL(dataBaseRestarted(AtpDef::mainWindowLoadingStatus)), mdiArea, SLOT(setAtpBackground(AtpDef::mainWindowLoadingStatus)));
	connect(this, SIGNAL(companyChanged(AtpDef::mainWindowLoadingStatus)), mdiArea, SLOT(setAtpBackground(AtpDef::mainWindowLoadingStatus)));
	connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateMenus()));

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
}

AtpMainWindow::~AtpMainWindow(){
	qDebug()<<"Exit AtpMainWindow";
}

void AtpMainWindow::quit() {
	emit closeRequested();
	QMainWindow::close();
}
/*
void AtpMainWindow::testSlot(bool closeThem){
	mdiArea->closeAllSubWindows();
}
*/
//event on close mainWindow
void AtpMainWindow::closeEvent(QCloseEvent *event) {
	qDebug()<<"Start closeEvent";
	mdiArea->closeAllSubWindows();
	if (mdiArea->currentSubWindow()) {
		event->ignore();
	} else {
		writeSettings();
		AtpDbClient::uninit();
		AtpDbComp::uninit();
		AtpDbMain::uninit();
		event->accept();
		//QApplication::quit();
	}
}

void AtpMainWindow::resizeEvent(QResizeEvent *event){
	QMainWindow::resizeEvent(event);
	emit windowResized(appStatus);
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
	//Close current open window
	actFileClose = new QAction(tr("Cl&ose"), this);
	actFileClose->setStatusTip(tr("Close the active window"));
	connect(actFileClose, SIGNAL(triggered()), mdiArea, SLOT(closeActiveSubWindow()));
	//Close all active windows
	actFileCloseAll = new QAction(tr("Close &All"), this);
	actFileCloseAll->setStatusTip(tr("Close all the windows"));
	connect(actFileCloseAll, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));
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
	connect(actCompSuppliers, SIGNAL(triggered()), this, SLOT(onActCompEditSuppliers()));

	//materials
	actCompMaterials = new QAction(QIcon(":/materials.png"), tr("Materials"), this);
	actCompMaterials->setStatusTip(tr("Manage the materials used on jobs"));
	connect(actCompMaterials, SIGNAL(triggered()), this, SLOT(onActCompMaterials()));

	//points
	actCompPoints = new QAction(QIcon(":/points.png"), tr("Points"), this);
	actCompPoints->setStatusTip(tr("Manage the points price"));
	connect(actCompPoints, SIGNAL(triggered()), this, SLOT(onActCompPoints()));

	//group place
	actCompPlace = new QAction(QIcon(":/place.png"), tr("Group place"), this);
	actCompPlace->setStatusTip(tr("Manage the item place"));
	connect(actCompPlace, SIGNAL(triggered()), this, SLOT(onActCompGroupPlace()));
//Client
	//chuse client or job
	actClientChuse = new QAction(QIcon(":/clients.png"), tr("Chuse &client"), this);
	actClientChuse->setStatusTip(tr("Edit the list of clients"));
	connect(actClientChuse, SIGNAL(triggered()), this, SLOT(onActClientChuseClient()));

	//edit client list
	actClientList = new QAction(QIcon(":/clients.png"), tr("Edit &clients list"), this);
	actClientList->setStatusTip(tr("Edit the list of clients"));
	connect(actClientList, SIGNAL(triggered()), this, SLOT(onActClientEditClientsList()));

	//invoices
	actClientInvoices = new QAction(QIcon(":/invoice.png"), tr("Invoices"), this);
	actClientInvoices->setStatusTip(tr("Manage the invoices"));
	//receipt
	actClientReceipt = new QAction(QIcon(":/receipt.png"), tr("Receipts"), this);
	actClientReceipt->setStatusTip(tr("Manage the receipts"));
	//quotes
	actClientQuotes = new QAction(QIcon(":/quotes.png"), tr("Quotes"), this);
	actClientQuotes->setStatusTip(tr("Manage the quotes"));

	//points
	actClientPoints = new QAction(QIcon(":/points.png"), tr("Points"), this);
	actClientPoints->setStatusTip(tr("Manage the points price"));
	connect(actClientPoints, SIGNAL(triggered()), this, SLOT(onActClientPoints()));

	//materials
	actClientMaterials = new QAction(QIcon(":/materials.png"), tr("Materials"), this);
	actClientMaterials->setStatusTip(tr("Manage the materials used on jobs"));
	connect(actClientMaterials, SIGNAL(triggered()), this, SLOT(onActCompMaterials()));
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
	menuCompany->addAction(actCompSuppliers);
	menuCompany->addAction(actCompMaterials);
	menuCompany->addSeparator();
	menuCompany->addAction(actCompPoints);
	menuCompany->addAction(actCompPlace);

//Modules Menu
	menuClients = menuBar()->addMenu(tr("C&lients"));
	menuClients->addAction(actClientChuse);
	menuClients->addAction(actClientList);
	menuClients->addSeparator();
	menuClients->addAction(actClientInvoices);
	menuClients->addAction(actClientReceipt);
	menuClients->addAction(actClientQuotes);
	menuClients->addSeparator();
	menuClients->addAction(actClientMaterials);
	menuClients->addAction(actClientPoints);

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
	//FIXME sa se faca update la meniu in functie de schimbarea tabului si de elementele deschise si incarcate precum baza de date si compania
	qDebug() << "Shimbat Tabul In mdi area";
//	bool hasMdiChild = true; //(activeMdiChild() != 0);
//	closeAct->setEnabled(hasMdiChild);
//	closeAllAct->setEnabled(hasMdiChild);
	//	separatorAct->setVisible(hasMdiChild);
}

/*
 * Company
*/

void AtpMainWindow::onActCompChuseCompany(){
	AtpCompanyChuse *compChuseCompany = new AtpCompanyChuse(this);
	compChuseCompany->setModal(true);
	connect(compChuseCompany, SIGNAL(startEditCompany()), this, SLOT(onActCompEditCompany()));
	if (compChuseCompany->exec() == QDialog::Accepted){
		checkForCompany();
	}
}

void AtpMainWindow::onActCompEditCompany(){
	//FIXME sa se deschida doar o singura fereastra si nu mai multe
/*
	AtpCompanyEdit *mdiChild;

	foreach (QMdiSubWindow *window, mdiArea->subWindowList()) {
		mdiChild = qobject_cast<AtpCompanyEdit *>(window->widget());

	}
	if(mdiChild){
		mdiArea->setActiveSubWindow(mdiChild);
	} else {
*/
	AtpCompanyEdit *companyEditor = new AtpCompanyEdit;
	companyEditor->setAttribute(Qt::WA_DeleteOnClose);
	//possible windows to close
	connect(companyEditor, SIGNAL(exitSignal()), actFileClose, SLOT(trigger()));
	mdiArea->addSubWindow(companyEditor);
	companyEditor->show();
	companyEditor->activateWindow();
//	}
}

void AtpMainWindow::onActCompEditSuppliers(){
	AtpCompanySuppliers *companySuppliers = new AtpCompanySuppliers;
	companySuppliers->setAttribute(Qt::WA_DeleteOnClose);
	//possible windows to close
	connect(companySuppliers, SIGNAL(exitSignal()), actFileClose, SLOT(trigger()));
	mdiArea->addSubWindow(companySuppliers);
	companySuppliers->show();
	companySuppliers->activateWindow();
}

void AtpMainWindow::onActCompMaterials(){
	AtpCompanyMaterials *myMaterials = new AtpCompanyMaterials;
	myMaterials->setAttribute(Qt::WA_DeleteOnClose);
	//possible windows to close
	connect(myMaterials, SIGNAL(exitSignal()), actFileClose, SLOT(trigger()));
	mdiArea->addSubWindow(myMaterials);
	myMaterials->show();
	myMaterials->activateWindow();
}

void AtpMainWindow::onActCompPoints(){
	AtpCompanyPoints *myPoints = new AtpCompanyPoints;
	myPoints->setAttribute(Qt::WA_DeleteOnClose);
	//possible windows to close
	connect(myPoints, SIGNAL(exitSignal()), actFileClose, SLOT(trigger()));
	mdiArea->addSubWindow(myPoints);
	myPoints->show();
	myPoints->activateWindow();
}

void AtpMainWindow::onActCompGroupPlace(){
	AtpCompanyGroupPlace *myCompGroupPlce = new AtpCompanyGroupPlace;
	myCompGroupPlce->setAttribute(Qt::WA_DeleteOnClose);
	connect(myCompGroupPlce, SIGNAL(exitSignal()), actFileClose, SLOT(trigger()));
	mdiArea->addSubWindow(myCompGroupPlce);
	myCompGroupPlce->show();
	myCompGroupPlce->activateWindow();
}

/*
 * Clients
*/

void AtpMainWindow::onActClientChuseClient(){
	AtpClientChuse *clChuseClient = new AtpClientChuse(this);
	clChuseClient->setModal(true);
	connect(clChuseClient, SIGNAL(startEditClient()), this, SLOT(onActClientEditClientsList()));
	if (clChuseClient->exec() == QDialog::Accepted){
		checkForClient();
	}
}

void AtpMainWindow::onActClientEditClientsList(){
	AtpClientEditList *clientEditor = new AtpClientEditList;
	clientEditor->setAttribute(Qt::WA_DeleteOnClose);
	//possible windows to close
	connect(clientEditor, SIGNAL(exitSignal()), actFileClose, SLOT(trigger()));
	mdiArea->addSubWindow(clientEditor);
	clientEditor->show();
	clientEditor->activateWindow();
}

void AtpMainWindow::onActClientPoints(){
	AtpClientPoints *clientPointsEditor = new AtpClientPoints;
	clientPointsEditor->setAttribute(Qt::WA_DeleteOnClose);
	//possible windows to close
	connect(clientPointsEditor, SIGNAL(exitSignal()), actFileClose, SLOT(trigger()));
	mdiArea->addSubWindow(clientPointsEditor);
	clientPointsEditor->show();
	clientPointsEditor->activateWindow();
}

/*
 * Tools
*/

void AtpMainWindow::onActToolsSettings(){
	AtpToolsSettings *toolsSettings = new AtpToolsSettings(this);
	toolsSettings->setModal(true);
	connect(toolsSettings, SIGNAL(restartDatabase()), this, SLOT(restartDatabase()));
	toolsSettings->exec();
	delete toolsSettings;
}

void AtpMainWindow::restartDatabase(){
	qDebug() << "RESTART DATABASE!";
	AtpDbComp::uninit();
	AtpDbMain::uninit();
	AtpDbMain::getDataBase();
	int autoLoadComp = AtpSettings::getIntValue("Company/Autoload", 0);
	if (AtpDbMain::isOpen()){
		appStatus = AtpDef::noCompanyLoaded;
		if (autoLoadComp == 2) {
			checkForCompany();
		}
	} else {
		appStatus = AtpDef::noDataBaseLoaded;
	}
	emit dataBaseRestarted(appStatus);
}

void AtpMainWindow::checkForCompany(){
	bool companyLoaded = false;
	int loadCompId = AtpSettings::getIntValue("Company/Id", 0);
	QString loadCompName = AtpSettings::getStringValue("Company/Name", "");
	QString loadCompPath = AtpSettings::getStringValue("Company/Path", "");
	QString myQuerry = QString("SELECT * FROM m_company_t WHERE comp_id = %1").arg(loadCompId);
	QSqlQuery loadedComp = AtpSqlQuery::atpSelect("main", myQuerry);
	QString newCompName, newCompPath;
	if(loadedComp.next()){
		newCompName = loadedComp.value("comp_name").toString();
		newCompPath = loadedComp.value("comp_file").toString();
	}

	if (loadCompName == newCompName && loadCompPath == newCompPath){
		AtpDbComp::getDataBase();
		if(AtpDbComp::isOpen()){
			companyLoaded = true;
			winTitleCompany = newCompName;
		}
	}

	if (companyLoaded){
		QString myWindowTitle = "@atp@ - " + winTitleCompany;
		setWindowTitle(myWindowTitle);
		appStatus = AtpDef::allLoadedOk;
	} else {
		setWindowTitle("@atp@");
		winTitleCompany.clear();
		appStatus = AtpDef::noCompanyLoaded;
	}
	emit companyChanged(appStatus);
}

void AtpMainWindow::checkForClient(){
	int loadClientId = AtpSettings::getIntValue("Client/Id", 0);
	if(loadClientId == 0){
		QString myWindowTitle = "@atp@ - " + winTitleCompany + " -> All companies";
		setWindowTitle(myWindowTitle);
		appStatus = AtpDef::allLoadedOk;
		return;
	}
	bool clientLoaded = false;
	QString loadClientName = AtpSettings::getStringValue("Client/Name", "");
	QString loadClientPath = AtpSettings::getStringValue("Client/Path", "");
	QString myQuerry = QString("SELECT * FROM comp_client_list_t WHERE client_id = %1").arg(loadClientId);
	QSqlQuery loadedClient = AtpSqlQuery::atpSelect("comp", myQuerry);
	QString newClientName, newClientPath;
	if(loadedClient.next()){
		newClientName = loadedClient.value("client_name").toString();
		newClientPath = loadedClient.value("client_file").toString();
	}

	if (loadClientName == newClientName && loadClientPath == newClientPath){
		AtpDbClient::getDataBase();
		if(AtpDbComp::isOpen()){
			clientLoaded = true;
			winTitleClient = newClientName;
		}
	}

	if (clientLoaded){
		QString myWindowTitle = "@atp@ - " + winTitleCompany + " -> " + winTitleClient;
		setWindowTitle(myWindowTitle);
		appStatus = AtpDef::allLoadedOk;
	} else {
		setWindowTitle("@atp@ - " + winTitleCompany);
		winTitleClient.clear();
		appStatus = AtpDef::noClientLoaded;
	}
	emit clientChanged(appStatus);
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

	AtpSettings::removeValue("Client/Name");
	AtpSettings::removeValue("Client/Path");
	AtpSettings::setValue("Client/Id", 0);

	qDebug() << "C" << AtpSettings::getMySettings()->fileName();
}
