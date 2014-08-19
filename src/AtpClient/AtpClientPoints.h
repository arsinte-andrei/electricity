#ifndef ATPCLIENTPOINTS_H
#define ATPCLIENTPOINTS_H

#include "atpclient_global.h"

#include <QWidget>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

namespace Ui {
	class AtpClientPoints;
}

class ATPCLIENT_EXPORT AtpClientPoints : public QWidget{
		Q_OBJECT

	public:
		explicit AtpClientPoints(QWidget *parent = 0);
		~AtpClientPoints();

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
		void onButtonSyncClicked();
		void resetVars();

	private:
		Ui::AtpClientPoints *ui;
		bool seEediteaza, eNou, eVechi;
		QMap<QString, QVariant> *data;
		QSqlTableModel *model;
		QSortFilterProxyModel *proxyModel;
		int punctId;
};

#endif // AtpClientPoints_H
