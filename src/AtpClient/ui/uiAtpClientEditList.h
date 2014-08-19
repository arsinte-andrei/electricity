#ifndef UIATPCLIENTEDITLIST_H
#define UIATPCLIENTEDITLIST_H

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

class ATPCOMPANY_EXPORT UiAtpClientEditList{
public:
	QGridLayout *gridLayout;
	QPlainTextEdit *editAddress;
	QLineEdit *editName;
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
	QLabel *label;
	QLineEdit *editMail;
	QLabel *label_3;
	QLineEdit *editMob;
	QLabel *label_4;
	QLineEdit *editTel;
	QLabel *label_5;
	QLineEdit *editSearch;
	QLabel *label_2;
	QTableView *tableClientList;
	QLabel *label_6;
	QLabel *label_7;

	void setupUi(QWidget *AtpClientEditList) {
		if (AtpClientEditList->objectName().isEmpty())
			AtpClientEditList->setObjectName(QStringLiteral("AtpClientEditList"));
		AtpClientEditList->resize(660, 439);
		AtpClientEditList->setWindowTitle("Client List Editor");

		gridLayout = new QGridLayout(AtpClientEditList);
		gridLayout->setObjectName(QStringLiteral("gridLayout"));

		editAddress = new QPlainTextEdit(AtpClientEditList);
		editAddress->setObjectName(QStringLiteral("editAddress"));
		gridLayout->addWidget(editAddress, 5, 3, 4, 1);

		editName = new QLineEdit(AtpClientEditList);
		editName->setObjectName(QStringLiteral("editName"));
		gridLayout->addWidget(editName, 5, 1, 1, 1);

		horizontalLayout = new QHBoxLayout();
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		buttonOk = new QPushButton(AtpClientEditList);
		buttonOk->setObjectName(QStringLiteral("buttonOk"));
		buttonOk->setText("Ok");
		horizontalLayout->addWidget(buttonOk);

		horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalLayout->addItem(horizontalSpacer);

		buttonNew = new QPushButton(AtpClientEditList);
		buttonNew->setObjectName(QStringLiteral("buttonNew"));
		buttonNew->setText("New");
		horizontalLayout->addWidget(buttonNew);

		horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalLayout->addItem(horizontalSpacer_2);

		buttonDelete = new QPushButton(AtpClientEditList);
		buttonDelete->setObjectName(QStringLiteral("buttonDelete"));
		buttonDelete->setText("Delete");
		horizontalLayout->addWidget(buttonDelete);

		horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalLayout->addItem(horizontalSpacer_3);

		buttonEdit = new QPushButton(AtpClientEditList);
		buttonEdit->setObjectName(QStringLiteral("buttonEdit"));
		buttonEdit->setText("Edit");
		horizontalLayout->addWidget(buttonEdit);

		horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalLayout->addItem(horizontalSpacer_4);

		buttonCancel = new QPushButton(AtpClientEditList);
		buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
		buttonCancel->setText("Cancel");
		horizontalLayout->addWidget(buttonCancel);

		gridLayout->addLayout(horizontalLayout, 10, 0, 1, 4);

		label = new QLabel(AtpClientEditList);
		label->setObjectName(QStringLiteral("label"));
		label->setText("Client name:");
		gridLayout->addWidget(label, 5, 0, 1, 1);

		editMail = new QLineEdit(AtpClientEditList);
		editMail->setObjectName(QStringLiteral("editMail"));
		gridLayout->addWidget(editMail, 8, 1, 1, 1);

		label_3 = new QLabel(AtpClientEditList);
		label_3->setObjectName(QStringLiteral("label_3"));
		label_3->setText("Mobile:");
		gridLayout->addWidget(label_3, 7, 0, 1, 1);

		editMob = new QLineEdit(AtpClientEditList);
		editMob->setObjectName(QStringLiteral("editMob"));
		gridLayout->addWidget(editMob, 7, 1, 1, 1);

		label_4 = new QLabel(AtpClientEditList);
		label_4->setObjectName(QStringLiteral("label_4"));
		label_4->setText("Email:");
		gridLayout->addWidget(label_4, 8, 0, 1, 1);

		editTel = new QLineEdit(AtpClientEditList);
		editTel->setObjectName(QStringLiteral("editTel"));
		gridLayout->addWidget(editTel, 6, 1, 1, 1);

		label_5 = new QLabel(AtpClientEditList);
		label_5->setObjectName(QStringLiteral("label_5"));
		label_5->setText("Address:");
		gridLayout->addWidget(label_5, 5, 2, 1, 1);

		editSearch = new QLineEdit(AtpClientEditList);
		editSearch->setObjectName(QStringLiteral("editSearch"));
		gridLayout->addWidget(editSearch, 4, 0, 1, 4);

		label_2 = new QLabel(AtpClientEditList);
		label_2->setObjectName(QStringLiteral("label_2"));
		label_2->setText("Landline:");
		gridLayout->addWidget(label_2, 6, 0, 1, 1);

		tableClientList = new QTableView(AtpClientEditList);
		tableClientList->setObjectName(QStringLiteral("tableClientList"));
		gridLayout->addWidget(tableClientList, 9, 0, 1, 4);

		label_6 = new QLabel(AtpClientEditList);
		label_6->setObjectName(QStringLiteral("label_6"));
		label_6->setText("Search:");
		gridLayout->addWidget(label_6, 3, 0, 1, 1);

		label_7 = new QLabel(AtpClientEditList);
		label_7->setObjectName(QStringLiteral("label_7"));
		QFont font;
		font.setPointSize(13);
		font.setBold(true);
		font.setWeight(75);
		label_7->setFont(font);
		label_7->setAlignment(Qt::AlignCenter);
		label_7->setText("Client list editor");
		gridLayout->addWidget(label_7, 2, 0, 1, 4);

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
			editSearch->setEnabled(true);
			tableClientList->setEnabled(true);
		} else if (condition == "enableFields"){
			editAddress->setEnabled(true);
			editName->setEnabled(true);
			editMail->setEnabled(true);
			editMob->setEnabled(true);
			editTel->setEnabled(true);
			editSearch->setEnabled(false);
			tableClientList->setEnabled(false);
		} else if (condition == "clearFields"){
			editAddress->clear();
			editName->clear();
			editMail->clear();
			editMob->clear();
			editTel->clear();
			editSearch->clear();
			tableClientList->clearSelection();
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
	class AtpClientEditList: public UiAtpClientEditList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AtpClientEditList_H
