#ifndef ATPEDITCOMPANY_H
#define ATPEDITCOMPANY_H

#include <QMdiSubWindow>

namespace Ui {
	class AtpEditCompany;
}

class AtpEditCompany : public QMdiSubWindow{
		Q_OBJECT

	public:
		explicit AtpEditCompany(QWidget *parent = 0, Qt::WindowFlags flags = 0);
		~AtpEditCompany();

	private slots:
		void on_editSearch_textEdited(const QString &arg1);
		void on_buttonOk_clicked();
		void on_buttonEdit_clicked();
		void on_buttonNew_clicked();
		void on_buttonDelete_clicked();
		void on_tableViewCompanyEditor_clicked(const QModelIndex &index);
		void on_buttonCancel_clicked();

	private:
		Ui::AtpEditCompany *ui;
		void updateDb();
};

#endif // ATPEDITCOMPANY_H
