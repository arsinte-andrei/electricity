#ifndef UIATPCOMPANYSUPPLIERS_H
#define UIATPCOMPANYSUPPLIERS_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QTableView>

#include "atpcompany_global.h"

QT_BEGIN_NAMESPACE

class ATPCOMPANY_EXPORT UiAtpCompanySuppliers{
public:
	QGridLayout *gridLayout;
	QLabel *label_2;
	QLabel *label_3;
	QLineEdit *editName;
	QLabel *label;
	QPlainTextEdit *editAddress;
	QLabel *label_4;
	QLineEdit *editTel;
	QLabel *label_5;
	QLineEdit *editMob;
	QLabel *label_6;
	QLineEdit *editMail;
	QLabel *label_7;
	QLineEdit *editWeb;
	QHBoxLayout *horizontalLayout;
	QPushButton *buttonOk;
	QSpacerItem *horizontalSpacer;
	QPushButton *buttonNew;
	QSpacerItem *horizontalSpacer_2;
	QPushButton *buttonDelete;
	QSpacerItem *horizontalSpacer_3;
	QPushButton *buttonEdit;
	QSpacerItem *horizontalSpacer_4;
	QPushButton *buttonCancel;
	QTableView *tabeSuppliers;
	QLineEdit *editSearch;
	QLabel *label_8;

	void setupUi(QWidget *AtpCompanySuppliers)	{
		if (AtpCompanySuppliers->objectName().isEmpty())
			AtpCompanySuppliers->setObjectName(QStringLiteral("AtpCompanySuppliers"));
		AtpCompanySuppliers->resize(693, 570);
		AtpCompanySuppliers->setWindowTitle("Suppliers list");

		gridLayout = new QGridLayout(AtpCompanySuppliers);
		gridLayout->setObjectName(QStringLiteral("gridLayout"));
		label_2 = new QLabel(AtpCompanySuppliers);
		label_2->setObjectName(QStringLiteral("label_2"));
		label_2->setText("Search:");
		gridLayout->addWidget(label_2, 1, 0, 1, 1);

		label_3 = new QLabel(AtpCompanySuppliers);
		label_3->setObjectName(QStringLiteral("label_3"));
		label_3->setText("Supplier name:");
		gridLayout->addWidget(label_3, 3, 0, 1, 1);

		editName = new QLineEdit(AtpCompanySuppliers);
		editName->setObjectName(QStringLiteral("editName"));
		gridLayout->addWidget(editName, 3, 1, 1, 1);

		label = new QLabel(AtpCompanySuppliers);
		label->setObjectName(QStringLiteral("label"));
		label->setText("Address:");
		gridLayout->addWidget(label, 3, 2, 1, 1);

		editAddress = new QPlainTextEdit(AtpCompanySuppliers);
		editAddress->setObjectName(QStringLiteral("editAddress"));
		gridLayout->addWidget(editAddress, 3, 3, 5, 1);

		label_4 = new QLabel(AtpCompanySuppliers);
		label_4->setObjectName(QStringLiteral("label_4"));
		label_4->setText("Landline:");
		gridLayout->addWidget(label_4, 4, 0, 1, 1);

		editTel = new QLineEdit(AtpCompanySuppliers);
		editTel->setObjectName(QStringLiteral("editTel"));
		gridLayout->addWidget(editTel, 4, 1, 1, 1);

		label_5 = new QLabel(AtpCompanySuppliers);
		label_5->setObjectName(QStringLiteral("label_5"));
		label_5->setText("Mobile:");
		gridLayout->addWidget(label_5, 5, 0, 1, 1);

		editMob = new QLineEdit(AtpCompanySuppliers);
		editMob->setObjectName(QStringLiteral("editMob"));
		gridLayout->addWidget(editMob, 5, 1, 1, 1);

		label_6 = new QLabel(AtpCompanySuppliers);
		label_6->setObjectName(QStringLiteral("label_6"));
		label_6->setText("E-mail:");
		gridLayout->addWidget(label_6, 6, 0, 1, 1);

		editMail = new QLineEdit(AtpCompanySuppliers);
		editMail->setObjectName(QStringLiteral("editMail"));
		gridLayout->addWidget(editMail, 6, 1, 1, 1);

		label_7 = new QLabel(AtpCompanySuppliers);
		label_7->setObjectName(QStringLiteral("label_7"));
		label_7->setText("Website:");
		gridLayout->addWidget(label_7, 7, 0, 1, 1);

		editWeb = new QLineEdit(AtpCompanySuppliers);
		editWeb->setObjectName(QStringLiteral("editWeb"));
		gridLayout->addWidget(editWeb, 7, 1, 1, 1);

		horizontalLayout = new QHBoxLayout();
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		buttonOk = new QPushButton(AtpCompanySuppliers);
		buttonOk->setObjectName(QStringLiteral("buttonOk"));
		buttonOk->setText("Ok");
		horizontalLayout->addWidget(buttonOk);

		horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalLayout->addItem(horizontalSpacer);

		buttonNew = new QPushButton(AtpCompanySuppliers);
		buttonNew->setObjectName(QStringLiteral("buttonNew"));
		buttonNew->setText("New");
		horizontalLayout->addWidget(buttonNew);

		horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalLayout->addItem(horizontalSpacer_2);

		buttonDelete = new QPushButton(AtpCompanySuppliers);
		buttonDelete->setObjectName(QStringLiteral("buttonDelete"));
		buttonDelete->setText("Delete");
		horizontalLayout->addWidget(buttonDelete);

		horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalLayout->addItem(horizontalSpacer_3);

		buttonEdit = new QPushButton(AtpCompanySuppliers);
		buttonEdit->setObjectName(QStringLiteral("buttonEdit"));
		buttonEdit->setText("Edit");
		horizontalLayout->addWidget(buttonEdit);

		horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalLayout->addItem(horizontalSpacer_4);

		buttonCancel = new QPushButton(AtpCompanySuppliers);
		buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
		buttonCancel->setText("Cancel");
		horizontalLayout->addWidget(buttonCancel);

		gridLayout->addLayout(horizontalLayout, 9, 0, 1, 4);

		tabeSuppliers = new QTableView(AtpCompanySuppliers);
		tabeSuppliers->setObjectName(QStringLiteral("tabeSuppliers"));
		gridLayout->addWidget(tabeSuppliers, 8, 0, 1, 4);

		editSearch = new QLineEdit(AtpCompanySuppliers);
		editSearch->setObjectName(QStringLiteral("editSearch"));
		editSearch->setClearButtonEnabled(true);
		editSearch->setPlaceholderText("Search for a supplier here...");
		gridLayout->addWidget(editSearch, 2, 0, 1, 4);

		label_8 = new QLabel(AtpCompanySuppliers);
		label_8->setObjectName(QStringLiteral("label_8"));
		QFont font;
		font.setPointSize(13);
		font.setBold(true);
		font.setWeight(75);
		label_8->setFont(font);
		label_8->setAlignment(Qt::AlignCenter);
		label_8->setText("Suppliers list editor");
		gridLayout->addWidget(label_8, 0, 0, 1, 4);

		QWidget::setTabOrder(editSearch, tabeSuppliers);
		QWidget::setTabOrder(tabeSuppliers, buttonOk);
		QWidget::setTabOrder(buttonOk, editName);
		QWidget::setTabOrder(editName, editTel);
		QWidget::setTabOrder(editTel, editMob);
		QWidget::setTabOrder(editMob, editMail);
		QWidget::setTabOrder(editMail, editWeb);
		QWidget::setTabOrder(editWeb, editAddress);
		QWidget::setTabOrder(editAddress, buttonNew);
		QWidget::setTabOrder(buttonNew, buttonDelete);
		QWidget::setTabOrder(buttonDelete, buttonEdit);
		QWidget::setTabOrder(buttonEdit, buttonCancel);

		enableAndDisable("reset");
	} // setupUi


	void enableAndDisable(QString condition){
		if (condition == "reset"){
			enableAndDisable("resetButtons");
			enableAndDisable("disableFields");
			enableAndDisable("clearFields");
		} else if (condition == "resetButtons"){
			buttonNew->setText("New");
			buttonNew->setEnabled(true);
			buttonEdit->setText("Edit");
			buttonEdit->setEnabled(false);
			buttonDelete->setEnabled(false);
		} else if (condition == "disableFields"){
			editAddress->setEnabled(false);
			editName->setEnabled(false);
			editMail->setEnabled(false);
			editMob->setEnabled(false);
			editTel->setEnabled(false);
			editWeb->setEnabled(false);
			editSearch->setEnabled(true);
			tabeSuppliers->setEnabled(true);
		} else if (condition == "enableFields"){
			editAddress->setEnabled(true);
			editName->setEnabled(true);
			editMail->setEnabled(true);
			editMob->setEnabled(true);
			editTel->setEnabled(true);
			editWeb->setEnabled(true);
			editSearch->setEnabled(false);
			tabeSuppliers->setEnabled(false);
		} else if (condition == "clearFields"){
			editName->clear();
			editAddress->clear();
			editMail->clear();
			editMob->clear();
			editTel->clear();
			editSearch->clear();
			editWeb->clear();
		} else if (condition == "edit"){
			buttonEdit->setText("Save");
			buttonDelete->setEnabled(false);
			buttonNew->setEnabled(false);
			enableAndDisable("enableFields");
		} else if (condition == "new") {
			buttonNew->setText("Save");
			buttonDelete->setEnabled(false);
			buttonEdit->setEnabled(false);
			enableAndDisable("clearFields");
			enableAndDisable("enableFields");
		}
	}


};

namespace Ui {
	class AtpCompanySuppliers: public UiAtpCompanySuppliers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AtpCompanySuppliers_H
