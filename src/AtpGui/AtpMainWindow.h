#ifndef ATPMAINWINDOW_H
#define ATPMAINWINDOW_H

#include "atpguilib_global.h"

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMdiArea>
#include <QToolBar>

class ATPGUILIB_EXPORT AtpMainWindow : public QMainWindow{
		Q_OBJECT
	public:
		AtpMainWindow(QWidget* parent = 0);
		~AtpMainWindow();

	public slots:
		void quit();

	signals:
		void closeRequested();

	protected:
		virtual void closeEvent(QCloseEvent *event);
		QMdiArea *mdiArea;

	private:
		void readSettings();
		void writeSettings();

		bool maybeSave();

		void createActions();
		void createMenus();
		void createToolBars();
		void createStatusBar();

//File
		QMenu *menuFile;
		QToolBar *toolBarFile;
		QAction *actFileExit;
//Company
		QMenu *menuCompany;
		QToolBar *toolBarComp;
		QAction *actCompChuse;
		QAction *actCompEdit;
		QAction *actCompSuppliers;
		QAction *actCompClients;
//Modules
		QMenu *menuModules;
		QToolBar *toolBarModules;
		QAction *actModulesInvoices;
		QAction *actModulesReceipt;
		QAction *actModulesQuotes;
		QAction *actModulesGroupPlace;
		QAction *actModulesPoints;
		QAction *actModulesMaterials;
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

		void onActCompChuseCompany();
		void onActCompEditCompany();
		void onActToolsSettings();

};

	Q_DECLARE_METATYPE(AtpMainWindow*)

#endif // ATPMAINWINDOW_H
