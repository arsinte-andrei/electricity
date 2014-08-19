#ifndef AtpCompanyPoints_H
#define AtpCompanyPoints_H

#include "atpcompany_global.h"

#include <QWidget>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

namespace Ui {
	class AtpCompanyPoints;
}

class ATPCOMPANY_EXPORT AtpCompanyPoints : public QWidget{
		Q_OBJECT

	public:
		explicit AtpCompanyPoints(QWidget *parent = 0);
		~AtpCompanyPoints();

	public slots:
		void updateDb();

	signals:
		void exitSignal();

	private slots:
		void onTablePointsClicked(const QModelIndex &index);
		void onEditSearchTextChanged(const QString &arg1);
		void onButtonCancelClicked();
		void onButtonEditClicked();
		void onButtonDeleteClicked();
		void onButtonNewClicked();
		void onButtonOkClicked();
		void resetVars();

	private:
		Ui::AtpCompanyPoints *ui;
		bool seEediteaza, eNou, eVechi;
		QMap<QString, QVariant> *data;
		QSqlTableModel *model;
		QSortFilterProxyModel *proxyModel;
		int punctId;
};

#endif // AtpCompanyPoints_H
