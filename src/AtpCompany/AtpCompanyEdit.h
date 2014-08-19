#ifndef ATPCOMPANYEDIT_H
#define ATPCOMPANYEDIT_H

#include "atpcompany_global.h"

#include <QWidget>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QMap>

namespace Ui {
	class AtpCompanyEdit;
}

class ATPCOMPANY_EXPORT AtpCompanyEdit : public QWidget{
		Q_OBJECT

	public:
		explicit AtpCompanyEdit(QWidget *parent = 0);
		~AtpCompanyEdit();

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
		void onTableViewCompanyClicked(const QModelIndex &index);
		void onEditSearchTextChanged(const QString &arg1);

	private:
		Ui::AtpCompanyEdit *ui;
		QSortFilterProxyModel *proxyModel;
		QMap<QString, QVariant> *data;
		QSqlTableModel *model;
		int compId;
		QString compName, compPath;
		bool seEediteaza, eNou, eVechi;

		void resetVars();
};

#endif // AtpCompanyEdit_H
