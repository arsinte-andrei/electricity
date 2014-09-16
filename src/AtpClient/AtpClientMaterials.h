#ifndef ATPCLIENTMATERIALS_H
#define ATPCLIENTMATERIALS_H

#include "atpclient_global.h"

#include <QWidget>
#include <QMap>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QCompleter>
#include <QTableView>

namespace Ui {
	class AtpClientMaterials;
}

class ATPCLIENT_EXPORT AtpClientMaterials : public QWidget{
		Q_OBJECT

	public:
		explicit AtpClientMaterials(QString clientName, QWidget *parent = 0);
		~AtpClientMaterials();

	public slots:
		void updateDb();

	signals:
		void exitSignal();

	private slots:
		void onComboSupplierCurrentTextChanged(const QString &arg1);
		void onComboSupplierIndexChanged(const QString &arg1);
		void onTableMaterialsClicked(const QModelIndex &index);
		void onEditSearchTextChanged(const QString &arg1);
		void onButtonCancelClicked();
		void onButtonEditClicked();
		void onButtonDeleteClicked();
		void onButtonNewClicked();
		void onButtonOkClicked();

	private:
		Ui::AtpClientMaterials *ui;
		QMap<QString, QVariant> *data;
		QSqlTableModel *model;
		QSqlRelationalTableModel *modelCombo;
		QSortFilterProxyModel *proxyModelCombo;
		QSortFilterProxyModel *proxyModel;
		QCompleter *myCompletear;
		QTableView *tableViewCombo;
		int matId;
		bool seEediteaza, eNou, eVechi;
		QString clientName;
		QString matSupplier;

		void resetVars();
};

#endif // AtpClientMaterials_H
