#ifndef ATPCLIENTEDITLIST_H
#define ATPCLIENTEDITLIST_H

#include "atpclient_global.h"
#include <QWidget>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QMap>

namespace Ui {
	class AtpClientEditList;
}

class ATPCLIENT_EXPORT AtpClientEditList : public QWidget{
		Q_OBJECT

	public:
		AtpClientEditList(QWidget *parent = 0);
		~AtpClientEditList();

	public slots:
		void updateDb();

	private slots:
		void onButtonOkClicked();
		void onButtonNewClicked();
		void onButtonDeleteClicked();
		void onButtonEditClicked();
		void onButtonCancelClicked();
		void onTableClientListClicked(const QModelIndex &index);
		void onEditSearchTextEdited(const QString &arg1);

	signals:
		void exitSignal();

	private:
		Ui::AtpClientEditList *ui;
		QSqlTableModel *model;
		QSortFilterProxyModel *proxyModel;
		QMap<QString, QVariant> *data;
		int clientId;
		QString clientName, clientFileName;
		bool seEediteaza, eNou, eVechi;

		void resetVars();
};

#endif // AtpClientEditList_H
