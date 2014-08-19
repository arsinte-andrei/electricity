#ifndef UIATPCOMPANYCHUSE_H
#define UIATPCOMPANYCHUSE_H

#include <QDialog>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>

#include "atpcompany_global.h"

QT_BEGIN_NAMESPACE

class ATPCOMPANY_EXPORT UiAtpCompanyChuse {
public:
	QLabel *label;
	QLineEdit *editSearch;
	QLabel *label_2;
	QTableView *tableView;
	QPushButton *buttonOk;
	QPushButton *buttonEdit;
	QPushButton *buttonCancel;

	void setupUi(QDialog *AtpCompanyChuse){
		if (AtpCompanyChuse->objectName().isEmpty())
			AtpCompanyChuse->setObjectName(QStringLiteral("AtpCompanyChuse"));
		AtpCompanyChuse->resize(500, 360);
		AtpCompanyChuse->setFixedSize(500, 360);
		QFont font;
		font.setKerning(true);
		AtpCompanyChuse->setFont(font);
		AtpCompanyChuse->setModal(true);
		AtpCompanyChuse->setWindowTitle("Chuse a Company:");

		label = new QLabel(AtpCompanyChuse);
		label->setObjectName(QStringLiteral("label"));
		label->setGeometry(QRect(150, 10, 241, 31));
		QFont font1;
		font1.setPointSize(16);
		font1.setBold(true);
		font1.setWeight(75);
		label->setFont(font1);
		label->setText("Chuse a Company:");

		editSearch = new QLineEdit(AtpCompanyChuse);
		editSearch->setObjectName(QStringLiteral("editSearch"));
		editSearch->setGeometry(QRect(20, 60, 460, 23));
		editSearch->setClearButtonEnabled(true);
		editSearch->setPlaceholderText("Search for a company here...");

		label_2 = new QLabel(AtpCompanyChuse);
		label_2->setObjectName(QStringLiteral("label_2"));
		label_2->setGeometry(QRect(24, 36, 61, 16));
		label_2->setText("Search:");

		tableView = new QTableView(AtpCompanyChuse);
		tableView->setObjectName(QStringLiteral("tableView"));
		tableView->setGeometry(QRect(20, 100, 460, 201));
		tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
		tableView->setSelectionMode(QAbstractItemView::SingleSelection);
		tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		tableView->resizeColumnsToContents();

		buttonOk = new QPushButton(AtpCompanyChuse);
		buttonOk->setObjectName(QStringLiteral("buttonOk"));
		buttonOk->setGeometry(QRect(20, 320, 81, 23));
		buttonOk->setText("Ok");
		buttonOk->setDefault(true);

		buttonEdit = new QPushButton(AtpCompanyChuse);
		buttonEdit->setObjectName(QStringLiteral("buttonEdit"));
		buttonEdit->setGeometry(QRect(190, 320, 101, 23));
		buttonEdit->setText("Edit company");

		buttonCancel = new QPushButton(AtpCompanyChuse);
		buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
		buttonCancel->setGeometry(QRect(400, 320, 81, 23));
		buttonCancel->setText("Cancel");
	} // setupUi

};

namespace Ui {
	class AtpCompanyChuse: public UiAtpCompanyChuse {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UIAtpCompanyChuse_H
