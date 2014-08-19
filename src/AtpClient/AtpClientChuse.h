#ifndef ATPCLIENTCHUSE_H
#define ATPCLIENTCHUSE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

#include "atpclient_global.h"

namespace Ui {
	class AtpClientChuse;
}

class ATPCLIENT_EXPORT AtpClientChuse : public QDialog {
		Q_OBJECT

	public:
		explicit AtpClientChuse(QWidget *parent = 0);
		~AtpClientChuse();

	signals:
		void startEditClient();

	private slots:
		void onButtonOkClicked();
		void onButtonEditClicked();
		void onButtonCancelClicked();
		void onTableViewDoubleClicked();
		void onEditSearchTextChanged(const QString &arg1);

	private:
		Ui::AtpClientChuse *ui;
		QSqlTableModel *model;
		QSortFilterProxyModel *proxyModel;
		void updateDatabase();
		bool acceptClient();
};

#endif // AtpClientChuse_H
