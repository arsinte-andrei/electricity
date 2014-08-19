#ifndef UIATPCLIENTCHUSE_H
#define UIATPCLIENTCHUSE_H

#include <QDialog>
#include <QObject>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QCheckBox>

#include "atpclient_global.h"

QT_BEGIN_NAMESPACE

class ATPCLIENT_EXPORT UiAtpClientChuse {
	public:
		QLabel *label;
		QLineEdit *editSearch;
		QLabel *label_2;
		QTableView *tableView;
		QPushButton *buttonOk;
		QPushButton *buttonEdit;
		QPushButton *buttonCancel;
		QCheckBox *checkBoxAllClients;

	void setupUi(QDialog *AtpChuseClient)	{
		if (AtpChuseClient->objectName().isEmpty())
			AtpChuseClient->setObjectName(QStringLiteral("AtpChuseClient"));
		AtpChuseClient->resize(500, 372);
		QFont font;
		font.setKerning(true);
		AtpChuseClient->setFont(font);
		AtpChuseClient->setModal(true);

		label = new QLabel(AtpChuseClient);
		label->setObjectName(QStringLiteral("label"));
		label->setGeometry(QRect(70, 10, 361, 31));
		QFont font1;
		font1.setPointSize(16);
		font1.setBold(true);
		font1.setWeight(75);
		label->setFont(font1);

		editSearch = new QLineEdit(AtpChuseClient);
		editSearch->setObjectName(QStringLiteral("editSearch"));
		editSearch->setGeometry(QRect(20, 60, 460, 23));

		label_2 = new QLabel(AtpChuseClient);
		label_2->setObjectName(QStringLiteral("label_2"));
		label_2->setGeometry(QRect(24, 36, 81, 16));

		tableView = new QTableView(AtpChuseClient);
		tableView->setObjectName(QStringLiteral("tableView"));
		tableView->setGeometry(QRect(20, 100, 460, 201));

		buttonOk = new QPushButton(AtpChuseClient);
		buttonOk->setObjectName(QStringLiteral("buttonOk"));
		buttonOk->setGeometry(QRect(20, 340, 81, 23));

		buttonEdit = new QPushButton(AtpChuseClient);
		buttonEdit->setObjectName(QStringLiteral("buttonEdit"));
		buttonEdit->setGeometry(QRect(190, 340, 101, 23));

		buttonCancel = new QPushButton(AtpChuseClient);
		buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
		buttonCancel->setGeometry(QRect(400, 340, 81, 23));

		checkBoxAllClients = new QCheckBox(AtpChuseClient);
		checkBoxAllClients->setObjectName(QStringLiteral("checkBoxAllClients"));
		checkBoxAllClients->setGeometry(QRect(20, 310, 131, 21));

		retranslateUi(AtpChuseClient);
	} // setupUi

	void retranslateUi(QDialog *AtpChuseClient)	{
		AtpChuseClient->setWindowTitle(QObject::tr("Chuse a Client:"));
		label->setText(QObject::tr("Chuse a Client to work with:"));
		label_2->setText(QObject::tr("Search:"));
		buttonOk->setText(QObject::tr("Ok"));
		buttonEdit->setText(QObject::tr("Edit clients"));
		buttonCancel->setText(QObject::tr("Cancel"));
		checkBoxAllClients->setText(QObject::tr("Select all clients"));
	} // retranslateUi

};

namespace Ui {
	class AtpClientChuse: public UiAtpClientChuse {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ATPCLIENTCHUSETI5503_H
