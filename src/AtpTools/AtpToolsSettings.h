#ifndef ATPTOOLSSETTINGS_H
#define ATPTOOLSSETTINGS_H

#include <QDialog>

#include "atptools_global.h"

namespace Ui {
	class AtpToolsSettings;
}

class ATPTOOLS_EXPORT AtpToolsSettings : public QDialog {
		Q_OBJECT

	public:
		AtpToolsSettings(QWidget *parent = 0);
		~AtpToolsSettings();

	signals:
		void restartDatabase();
		void settingsChanged();
		void dialogIsClosing();

	private slots:
		void on_buttonOpenFile_clicked();
		void on_buttonCreateDataBase_clicked();
		void on_buttonApply_clicked();
		void on_buttonCancel_clicked();
		void on_buttonOk_clicked();
		void on_tabMainSettings_currentChanged(int index);
		void on_editCurrencyPrefix_textEdited();
		void on_editCurrencySuffix_textEdited();
		void on_editDiscountPrefix_textEdited();
		void on_editDiscountSuffix_textEdited();
		void on_checkBoxAutoLoadCompany_stateChanged();
		void on_editPathOpen_textEdited(const QString &arg1);
		void onSettingsChanged();
		void onCloseDialog();

	private:
		Ui::AtpToolsSettings *ui;
		void processChanged();
		void resetAll();
		bool changed, //general
		changedDbFilePath, restartDb, //TAB 1
		changedDiscountSuffix,	changedDiscountPrefix,	changedCurrancySuffix, changedCurrancyPrefix, //TAB 2
		changedAutoLoadCompany //TAB 3
		;

	protected:
		virtual void closeEvent(QCloseEvent *event);
};

#endif // TOOLS_SETTINGS_H
