#ifndef UIATPCOMPANYGROUPPLACE_H
#define UIATPCOMPANYGROUPPLACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

#include "AtpTreeComboBox.h"

QT_BEGIN_NAMESPACE

class UiAtpCompanyGroupPlace {

	public:
		QGridLayout *gridLayout;
		QLabel *lblFormTitle;
		QLabel *lblPlaceName;
		QLabel *lblParent;
		QLineEdit *editName;
		AtpTreeComboBox *comboParent;
		QTreeView *tableGroup;
		QPushButton *buttonOk;
		QPushButton *buttonNew;
		QPushButton *buttonDelete;
		QPushButton *buttonEdit;
		QPushButton *buttonCancel;

	void setupUi(QWidget *AtpModulesGroupPlace){
		if (AtpModulesGroupPlace->objectName().isEmpty())
			AtpModulesGroupPlace->setObjectName(QStringLiteral("AtpModulesGroupPlace"));
		AtpModulesGroupPlace->resize(442, 377);

		gridLayout = new QGridLayout(AtpModulesGroupPlace);
		gridLayout->setObjectName(QStringLiteral("gridLayout"));

		lblFormTitle = new QLabel(AtpModulesGroupPlace);
		lblFormTitle->setObjectName(QStringLiteral("lblFormTitle"));
		QFont font;
		font.setPointSize(13);
		lblFormTitle->setFont(font);
		lblFormTitle->setAlignment(Qt::AlignCenter);
		gridLayout->addWidget(lblFormTitle, 0, 0, 1, 5);

		lblPlaceName = new QLabel(AtpModulesGroupPlace);
		lblPlaceName->setObjectName(QStringLiteral("lblPlaceName"));
		gridLayout->addWidget(lblPlaceName, 1, 0, 1, 1);

		editName = new QLineEdit(AtpModulesGroupPlace);
		editName->setObjectName(QStringLiteral("editName"));
		gridLayout->addWidget(editName, 1, 1, 1, 4);

		lblParent = new QLabel(AtpModulesGroupPlace);
		lblParent->setObjectName(QStringLiteral("lblParent"));
		gridLayout->addWidget(lblParent, 2, 0, 1, 1);

		comboParent = new AtpTreeComboBox(AtpModulesGroupPlace);
		comboParent->setObjectName(QStringLiteral("comboParent"));
		gridLayout->addWidget(comboParent, 2, 1, 1, 4);

		tableGroup = new QTreeView(AtpModulesGroupPlace);
		tableGroup->setObjectName(QStringLiteral("tableGroup"));
		gridLayout->addWidget(tableGroup, 3, 0, 1, 5);

		buttonOk = new QPushButton(AtpModulesGroupPlace);
		buttonOk->setObjectName(QStringLiteral("buttonOk"));
		QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(buttonOk->sizePolicy().hasHeightForWidth());
		buttonOk->setSizePolicy(sizePolicy);
		gridLayout->addWidget(buttonOk, 4, 0, 1, 1);

		buttonNew = new QPushButton(AtpModulesGroupPlace);
		buttonNew->setObjectName(QStringLiteral("buttonNew"));
		sizePolicy.setHeightForWidth(buttonNew->sizePolicy().hasHeightForWidth());
		buttonNew->setSizePolicy(sizePolicy);
		gridLayout->addWidget(buttonNew, 4, 1, 1, 1);

		buttonDelete = new QPushButton(AtpModulesGroupPlace);
		buttonDelete->setObjectName(QStringLiteral("buttonDelete"));
		sizePolicy.setHeightForWidth(buttonDelete->sizePolicy().hasHeightForWidth());
		buttonDelete->setSizePolicy(sizePolicy);
		gridLayout->addWidget(buttonDelete, 4, 2, 1, 1);

		buttonEdit = new QPushButton(AtpModulesGroupPlace);
		buttonEdit->setObjectName(QStringLiteral("buttonEdit"));
		sizePolicy.setHeightForWidth(buttonEdit->sizePolicy().hasHeightForWidth());
		buttonEdit->setSizePolicy(sizePolicy);
		gridLayout->addWidget(buttonEdit, 4, 3, 1, 1);

		buttonCancel = new QPushButton(AtpModulesGroupPlace);
		buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
		sizePolicy.setHeightForWidth(buttonCancel->sizePolicy().hasHeightForWidth());
		buttonCancel->setSizePolicy(sizePolicy);
		gridLayout->addWidget(buttonCancel, 4, 4, 1, 1);

		retranslateUi(AtpModulesGroupPlace);
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
			editName->setEnabled(false);
			comboParent->setEnabled(false);
			tableGroup->setEnabled(true);
		} else if (condition == "enableFields"){
			editName->setEnabled(true);
			comboParent->setEnabled(true);
			tableGroup->setEnabled(false);
		} else if (condition == "clearFields"){
			editName->clear();
			comboParent->setCurrentIndex(-1);
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

//			disconnect(mycombo,SIGNAL(currentIndexChanged(int)),this,SLOT(onMycomboCurrentIndexChanged()));
//			mycombo->setCurrentIndex(-1);
//			connect(mycombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onMycomboCurrentIndexChanged()));

	void retranslateUi(QWidget *AtpModulesGroupPlace){
		AtpModulesGroupPlace->setWindowTitle(QApplication::translate("AtpModulesGroupPlace", "Group Place", 0));
		lblFormTitle->setText(QApplication::translate("AtpModulesGroupPlace", "Group Place", 0));
		lblPlaceName->setText(QApplication::translate("AtpModulesGroupPlace", "Place name:", 0));
		lblParent->setText(QApplication::translate("AtpModulesGroupPlace", "Parent:", 0));
		buttonOk->setText(QApplication::translate("AtpModulesGroupPlace", "&Ok", 0));
		buttonNew->setText(QApplication::translate("AtpModulesGroupPlace", "&New", 0));
		buttonDelete->setText(QApplication::translate("AtpModulesGroupPlace", "&Delete", 0));
		buttonEdit->setText(QApplication::translate("AtpModulesGroupPlace", "&Edit", 0));
		buttonCancel->setText(QApplication::translate("AtpModulesGroupPlace", "&Cancel", 0));
	} // retranslateUi

};

namespace Ui {
	class AtpCompanyGroupPlace: public UiAtpCompanyGroupPlace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ATPMODULESGROUPPLACER15474_H
