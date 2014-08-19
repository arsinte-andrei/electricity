#ifndef ATPCOMPANYCHUSE_H
#define ATPCOMPANYCHUSE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

#include "atpcompany_global.h"

namespace Ui {
	class AtpCompanyChuse;
}

class ATPCOMPANY_EXPORT AtpCompanyChuse : public QDialog {
		Q_OBJECT

	public:
		explicit AtpCompanyChuse(QWidget *parent = 0);
		~AtpCompanyChuse();

	signals:
		void startEditCompany();

	private slots:
		void onButtonOkClicked();
		void onButtonEditClicked();
		void onButtonCancelClicked();
		void onTableViewDoubleClicked();
		void onEditSearchTextChanged(const QString &arg1);

	private:
		Ui::AtpCompanyChuse *ui;
		QSqlTableModel *model;
		QSortFilterProxyModel *proxyModel;
		void updateDatabase();
		bool acceptCompany();
};

#endif // AtpCompanyChuse_H
