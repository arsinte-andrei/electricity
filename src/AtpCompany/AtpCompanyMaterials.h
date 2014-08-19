#ifndef ATPCOMPANYMATERIALS_H
#define ATPCOMPANYMATERIALS_H

#include "atpcompany_global.h"

#include <QWidget>
#include <QMap>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QCompleter>

namespace Ui {
	class AtpCompanyMaterials;
}

class ATPCOMPANY_EXPORT AtpCompanyMaterials : public QWidget{
		Q_OBJECT

	public:
		explicit AtpCompanyMaterials(QWidget *parent = 0);
		~AtpCompanyMaterials();

	public slots:
		void updateDb();

	signals:
		void exitSignal();

	private slots:
		void onComboSupplierCurrentTextChanged(const QString &arg1);
		void onTableMaterialsClicked(const QModelIndex &index);
		void onEditSearchTextChanged(const QString &arg1);
		void onButtonCancelClicked();
		void onButtonEditClicked();
		void onButtonDeleteClicked();
		void onButtonNewClicked();
		void onButtonOkClicked();

	private:
		Ui::AtpCompanyMaterials *ui;
		QMap<QString, QVariant> *data;
		QSqlRelationalTableModel *model;
		QSqlTableModel *modelCombo;
		QSortFilterProxyModel *proxyModelCombo;
		QSortFilterProxyModel *proxyModel;
		QCompleter *myCompletear;
		int matId;
		bool seEediteaza, eNou, eVechi;

		void resetVars();
};

#endif // AtpCompanyMaterials_H
