#ifndef ATPEDITCOMPANY_H
#define ATPEDITCOMPANY_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QMap>

namespace Ui {
	class AtpEditCompany;
}

class AtpEditCompany : public QMdiSubWindow{
		Q_OBJECT

	public:
		explicit AtpEditCompany(QWidget *parent = 0);
		~AtpEditCompany();

	private slots:
		void on_buttonOk_clicked();
		void on_buttonNew_clicked();
		void on_buttonDelete_clicked();
		void on_buttonEdit_clicked();
		void on_buttonCancel_clicked();
		void on_editSearch_textEdited(const QString &arg1);
		void on_tableViewCompany_clicked(const QModelIndex &index);

	private:
		Ui::AtpEditCompany *ui;
		void updateDb();
		void enableAndDisable(QString condition);
		QSortFilterProxyModel *proxyModel;
		QMap<QString, QVariant> *data;
		QSqlTableModel *model;
		int compId;
};

#endif // ATPEDITCOMPANY_H
