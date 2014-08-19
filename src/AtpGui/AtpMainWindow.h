#ifndef ATPMAINWINDOW_H
#define ATPMAINWINDOW_H

#include "atpguilib_global.h"

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMdiArea>
#include <QToolBar>

#include "AtpDef.h"
#include "AtpMdiArea.h"

class ATPGUILIB_EXPORT AtpMainWindow : public QMainWindow{
		Q_OBJECT
	public:
		AtpMainWindow(QWidget* parent = 0);
		~AtpMainWindow();

	public slots:
		void quit();
//		void testSlot(bool closeThem);

	signals:
		void closeRequested();
		void windowResized(AtpDef::mainWindowLoadingStatus);
		void dataBaseRestarted(AtpDef::mainWindowLoadingStatus);
		void companyChanged(AtpDef::mainWindowLoadingStatus);
		void clientChanged(AtpDef::mainWindowLoadingStatus);

	protected:
		void closeEvent(QCloseEvent *event);
		void resizeEvent (QResizeEvent *event);

	private:
		QString winTitleCompany, winTitleClient;
		AtpDef::mainWindowLoadingStatus appStatus;
		void readSettings();
		void writeSettings();

		bool maybeSave();

		void createActions();
		void createMenus();
		void createToolBars();
		void createStatusBar();

		AtpMdiArea *mdiArea;
//File
		QMenu *menuFile;
		QToolBar *toolBarFile;
		QAction *actFileExit;
		QAction *actFileClose;
		QAction *actFileCloseAll;
//Company
		QMenu *menuCompany;
		QToolBar *toolBarComp;
		QAction *actCompChuse;
		QAction *actCompEdit;
		QAction *actCompSuppliers;
		QAction *actCompMaterials;
		QAction *actCompPoints;
		QAction *actCompPlace;
//Client
		QMenu *menuClients;
		QToolBar *toolBarModules;
		QAction *actClientInvoices;
		QAction *actClientReceipt;
		QAction *actClientQuotes;
		QAction *actClientPoints;
		QAction *actClientMaterials;
		QAction *actClientList;
		QAction *actClientChuse;
//Tools
		QMenu *menuTools;
		QToolBar *toolBarTools;
		QAction *actToolsUsers;
		QAction *actToolsSettings;
//Reporting
		QMenu *menuReporting;
		QToolBar *toolBarReporting;
		QAction *actReportsReports;
		QAction *actReportsTemplates;
//Help
		QMenu *menuHelp;
		QToolBar *toolBarHelp;
		QAction *actHelpRegister;
		QAction *actHelpUpdates;
		QAction *actHelpHelp;
		QAction *actHelpAbout;

		QAction *separatorAct;

	private slots:
		void updateMenus();
		void restartDatabase();
		void checkForCompany();
		void checkForClient();
//company
		void onActCompChuseCompany();
		void onActCompEditCompany();
		void onActCompEditSuppliers();
		void onActCompMaterials();
		void onActCompPoints();
		void onActCompGroupPlace();
//Clients
		void onActClientChuseClient();
		void onActClientEditClientsList();
		void onActClientPoints();
//Tools
		void onActToolsSettings();

};

	Q_DECLARE_METATYPE(AtpMainWindow*)

#endif // ATPMAINWINDOW_H
