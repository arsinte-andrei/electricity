#ifndef ATPCLIENTSYNCPOINTS_H
#define ATPCLIENTSYNCPOINTS_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

namespace Ui {
	class AtpClientSyncPoints;
}

class AtpClientSyncPoints : public QDialog{
		Q_OBJECT

	public:
		explicit AtpClientSyncPoints(QWidget *parent = 0);
		~AtpClientSyncPoints();

	private:
		Ui::AtpClientSyncPoints *ui;
		QSqlTableModel *modelPointComp, *modelPointClient;
		QSortFilterProxyModel *proxyPointComp, *proxyPointclient;
		int rowsCompPoint,rowsClientPoint;

		void updateDb();

	private slots:
		void onButtonOkClicked();
		void onButtonCancelClicked();
		void onButtonFromCompanyClicked();
		void onButtonFromClientClicked();
		void onCheckAllComp(int status);
		void onCheckAllClient(int status);
};

#endif // ATPCLIENTSYNCPOINTS_H
