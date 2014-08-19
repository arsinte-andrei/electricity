#ifndef ATPCOMPANYSUPPLIERS_H
#define ATPCOMPANYSUPPLIERS_H

#include "atpcompany_global.h"
#include <QWidget>
#include <QMap>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

namespace Ui {
	class AtpCompanySuppliers;
}

class ATPCOMPANY_EXPORT AtpCompanySuppliers : public QWidget{
		Q_OBJECT

	public:
		explicit AtpCompanySuppliers(QWidget *parent = 0);
		~AtpCompanySuppliers();

	public slots:
		void updateDb();

	signals:
		void exitSignal();

	private slots:
		void onButtonOkClicked();
		void onButtonNewClicked();
		void onButtonDeleteClicked();
		void onButtonEditClicked();
		void onButtonCancelClicked();
		void onEditSearchTextEdited(const QString &arg1);
		void onTableSuppliersClicked(const QModelIndex &index);

	private:
		Ui::AtpCompanySuppliers *ui;
		QMap<QString, QVariant> *data;
		QSqlTableModel *model;
		QSortFilterProxyModel *proxyModel;
		int supplierId;
		bool seEediteaza, eNou, eVechi;

		void resetVars();
};

#endif // AtpCompanySuppliers_H
