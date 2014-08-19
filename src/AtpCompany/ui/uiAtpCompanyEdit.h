#ifndef UIATPCOMPANYEDIT_H
#define UIATPCOMPANYEDIT_H

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

class ATPCOMPANY_EXPORT UiAtpCompanyEdit {
public:
	QGridLayout *gridLayout_2;
	QLabel *label_9;
	QLabel *label_8;
	QLineEdit *editSearch;
	QGridLayout *gridLayout;
	QLabel *label;
	QLineEdit *editCompany;
	QLabel *label_3;
	QLineEdit *editDirector;
	QLabel *label_4;
	QLineEdit *editTel;
	QLabel *label_5;
	QLineEdit *editMob;
	QLabel *label_6;
	QLineEdit *editMail;
	QLabel *label_7;
	QLabel *label_2;
	QLineEdit *editWebsite;
	QPlainTextEdit *editAddress;
	QTableView *tableViewCompany;
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

	void setupUi(QWidget *AtpCompanyEdit){
		if (AtpCompanyEdit->objectName().isEmpty())
			AtpCompanyEdit->setObjectName(QStringLiteral("AtpCompanyEdit"));
		AtpCompanyEdit->resize(709, 578);
		AtpCompanyEdit->setWindowTitle("Company Editor");

		gridLayout_2 = new QGridLayout(AtpCompanyEdit);
		gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));

		label_9 = new QLabel(AtpCompanyEdit);
		label_9->setObjectName(QStringLiteral("label_9"));
		QFont font;
		font.setPointSize(12);
		font.setBold(true);
		font.setWeight(75);
		label_9->setFont(font);
		label_9->setTextFormat(Qt::RichText);
		label_9->setAlignment(Qt::AlignCenter);
		label_9->setText("Company editor");
		gridLayout_2->addWidget(label_9, 0, 0, 1, 1);

		label_8 = new QLabel(AtpCompanyEdit);
		label_8->setObjectName(QStringLiteral("label_8"));
		label_8->setText("Search:");
		gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

		editSearch = new QLineEdit(AtpCompanyEdit);
		editSearch->setObjectName(QStringLiteral("editSearch"));
		editSearch->setClearButtonEnabled(true);
		editSearch->setPlaceholderText("Search for a company here...");
		gridLayout_2->addWidget(editSearch, 2, 0, 1, 1);

		gridLayout = new QGridLayout();
		gridLayout->setObjectName(QStringLiteral("gridLayout"));
		label = new QLabel(AtpCompanyEdit);
		label->setObjectName(QStringLiteral("label"));
		label->setText("Company name:");
		gridLayout->addWidget(label, 0, 0, 1, 1);

		editCompany = new QLineEdit(AtpCompanyEdit);
		editCompany->setObjectName(QStringLiteral("editCompany"));
		gridLayout->addWidget(editCompany, 0, 1, 1, 1);

		label_3 = new QLabel(AtpCompanyEdit);
		label_3->setObjectName(QStringLiteral("label_3"));
		label_3->setText("Director:");
		gridLayout->addWidget(label_3, 1, 0, 1, 1);

		editDirector = new QLineEdit(AtpCompanyEdit);
		editDirector->setObjectName(QStringLiteral("editDirector"));
		gridLayout->addWidget(editDirector, 1, 1, 1, 1);

		label_4 = new QLabel(AtpCompanyEdit);
		label_4->setObjectName(QStringLiteral("label_4"));
		label_4->setText("Telephone:");
		gridLayout->addWidget(label_4, 2, 0, 1, 1);

		editTel = new QLineEdit(AtpCompanyEdit);
		editTel->setObjectName(QStringLiteral("editTel"));
		gridLayout->addWidget(editTel, 2, 1, 1, 1);

		label_5 = new QLabel(AtpCompanyEdit);
		label_5->setObjectName(QStringLiteral("label_5"));
		label_5->setText("Mobile:");
		gridLayout->addWidget(label_5, 3, 0, 1, 1);

		editMob = new QLineEdit(AtpCompanyEdit);
		editMob->setObjectName(QStringLiteral("editMob"));
		gridLayout->addWidget(editMob, 3, 1, 1, 1);

		label_6 = new QLabel(AtpCompanyEdit);
		label_6->setObjectName(QStringLiteral("label_6"));
		label_6->setText("E-mail:");
		gridLayout->addWidget(label_6, 4, 0, 1, 1);

		editMail = new QLineEdit(AtpCompanyEdit);
		editMail->setObjectName(QStringLiteral("editMail"));
		gridLayout->addWidget(editMail, 4, 1, 1, 1);

		label_7 = new QLabel(AtpCompanyEdit);
		label_7->setObjectName(QStringLiteral("label_7"));
		label_7->setText("Address:");
		gridLayout->addWidget(label_7, 0, 2, 1, 1);

		label_2 = new QLabel(AtpCompanyEdit);
		label_2->setObjectName(QStringLiteral("label_2"));
		label_2->setText("Website:");
		gridLayout->addWidget(label_2, 4, 2, 1, 1);

		editWebsite = new QLineEdit(AtpCompanyEdit);
		editWebsite->setObjectName(QStringLiteral("editWebsite"));
		gridLayout->addWidget(editWebsite, 4, 3, 1, 1);

		editAddress = new QPlainTextEdit(AtpCompanyEdit);
		editAddress->setObjectName(QStringLiteral("editAddress"));
		editAddress->setDocumentTitle(QString());
		editAddress->setPlainText(QString());
		gridLayout->addWidget(editAddress, 0, 3, 4, 1);

		gridLayout_2->addLayout(gridLayout, 3, 0, 1, 1);

		tableViewCompany = new QTableView(AtpCompanyEdit);
		tableViewCompany->setObjectName(QStringLiteral("tableViewCompany"));
		tableViewCompany->setSelectionBehavior(QAbstractItemView::SelectRows);
		tableViewCompany->setSelectionMode(QAbstractItemView::SingleSelection);
		tableViewCompany->setEditTriggers(QAbstractItemView::NoEditTriggers);
		tableViewCompany->resizeColumnsToContents();
		gridLayout_2->addWidget(tableViewCompany, 4, 0, 1, 1);

		horizontalLayout = new QHBoxLayout();
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		buttonOk = new QPushButton(AtpCompanyEdit);
		buttonOk->setObjectName(QStringLiteral("buttonOk"));
		buttonOk->setText("Ok");
		buttonOk->setDefault(true);
		horizontalLayout->addWidget(buttonOk);

		horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalLayout->addItem(horizontalSpacer);

		buttonNew = new QPushButton(AtpCompanyEdit);
		buttonNew->setObjectName(QStringLiteral("buttonNew"));
		buttonNew->setText("New");
		horizontalLayout->addWidget(buttonNew);

		horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalLayout->addItem(horizontalSpacer_2);

		buttonDelete = new QPushButton(AtpCompanyEdit);
		buttonDelete->setObjectName(QStringLiteral("buttonDelete"));
		buttonDelete->setText("Delete");
		horizontalLayout->addWidget(buttonDelete);

		horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalLayout->addItem(horizontalSpacer_3);

		buttonEdit = new QPushButton(AtpCompanyEdit);
		buttonEdit->setObjectName(QStringLiteral("buttonEdit"));
		buttonEdit->setText("Edit");
		horizontalLayout->addWidget(buttonEdit);

		horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		horizontalLayout->addItem(horizontalSpacer_4);

		buttonCancel = new QPushButton(AtpCompanyEdit);
		buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
		buttonCancel->setText("Cancel");
		horizontalLayout->addWidget(buttonCancel);

		gridLayout_2->addLayout(horizontalLayout, 5, 0, 1, 1);

		QWidget::setTabOrder(buttonOk, editSearch);
		QWidget::setTabOrder(editSearch, tableViewCompany);
		QWidget::setTabOrder(tableViewCompany, editCompany);
		QWidget::setTabOrder(editCompany, editDirector);
		QWidget::setTabOrder(editDirector, editAddress);
		QWidget::setTabOrder(editAddress, editTel);
		QWidget::setTabOrder(editTel, editMob);
		QWidget::setTabOrder(editMob, editMail);
		QWidget::setTabOrder(editMail, editWebsite);
		QWidget::setTabOrder(editWebsite, buttonNew);
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
			editCompany->setEnabled(false);
			editDirector->setEnabled(false);
			editMail->setEnabled(false);
			editMob->setEnabled(false);
			editTel->setEnabled(false);
			editWebsite->setEnabled(false);
			editSearch->setEnabled(true);
			editSearch->clear();
			tableViewCompany->setEnabled(true);
		} else if (condition == "enableFields"){
			editAddress->setEnabled(true);
			editCompany->setEnabled(true);
			editDirector->setEnabled(true);
			editMail->setEnabled(true);
			editMob->setEnabled(true);
			editTel->setEnabled(true);
			editWebsite->setEnabled(true);
			editSearch->setEnabled(false);
			tableViewCompany->setEnabled(false);
		} else if (condition == "clearFields"){
			editAddress->clear();
			editCompany->clear();
			editDirector->clear();
			editMail->clear();
			editMob->clear();
			editTel->clear();
			editWebsite->clear();
			editSearch->clear();
			tableViewCompany->clearSelection();
		} else if (condition == "edit"){
			buttonEdit->setText("Save");
			buttonDelete->setEnabled(false);
			buttonNew->setEnabled(false);
			enableAndDisable("enableFields");
		} else if (condition == "new") {
			buttonNew->setText("Save");
			buttonDelete->setEnabled(false);
			buttonEdit->setEnabled(false);
			editSearch->setEnabled(false);
			enableAndDisable("clearFields");
			enableAndDisable("enableFields");
		}
	}


};

namespace Ui {
	class AtpCompanyEdit: public UiAtpCompanyEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AtpCompanyEdit_H
