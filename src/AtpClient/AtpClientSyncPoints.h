#ifndef ATPCLIENTSYNCPOINTS_H
#define ATPCLIENTSYNCPOINTS_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QMap>
#include <QCheckBox>

namespace Ui {
	class AtpClientSyncPoints;
}

class AtpClientSyncPoints : public QDialog{
		Q_OBJECT

	public:
		explicit AtpClientSyncPoints(QString clientName, QWidget *parent = 0);
		~AtpClientSyncPoints();

	private:
		Ui::AtpClientSyncPoints *ui;
		QSqlTableModel *modelPointComp;
		QSortFilterProxyModel *proxyPointComp;
		int rowsCompPoint;
		QMap<QString, QCheckBox *> mapCheckComp;
		QMap<QString, bool> mapAllComp;
		QString clientName;

		void updateDb();

	private slots:
		void onButtonOkClicked();
		void onButtonCancelClicked();
		void onButtonFromCompanyClicked();
		void onCheckAllComp(int status);
		void onCheckButtonCompPressed();
		void connectAllCompCheck();
		void disconnectAllCompCheck();
		void onEditSearchCompPoint(const QString &arg1);
		void updateCheckBoxPosition();
};

#endif // ATPCLIENTSYNCPOINTS_H
