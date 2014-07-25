#ifndef ATPCHUSECOMPANY_H
#define ATPCHUSECOMPANY_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

#include "atpcompany_global.h"

namespace Ui {
	class AtpChuseCompany;
}

class ATPCOMPANY_EXPORT AtpChuseCompany : public QDialog {
		Q_OBJECT

	public:
		explicit AtpChuseCompany(QWidget *parent = 0);
		~AtpChuseCompany();

	private slots:
		void on_buttonOk_clicked();

		void on_buttonEdit_clicked();

		void on_buttonCancel_clicked();

		void on_editSearch_textEdited(const QString &arg1);

	private:
		Ui::AtpChuseCompany *ui;
		QSqlTableModel *model;
		QSortFilterProxyModel *proxyModel;
		void updateDatabase();
};

#endif // ATPCHUSECOMPANY_H
