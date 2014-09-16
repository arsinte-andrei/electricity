#ifndef UIATPCLIENTMATERIALS_H
#define UIATPCLIENTMATERIALS_H

#include <QComboBox>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QTableView>
#include <QDoubleSpinBox>
#include <QApplication>

QT_BEGIN_NAMESPACE

class Ui_AtpClientMaterials {

	public:
		QGridLayout *gridLayout_2;
		QLabel *label_6;
		QDoubleSpinBox *editBuy;
		QLabel *label_5;
		QTableView *tableMaterials;
		QLabel *label_4;
		QGridLayout *gridLayout;
		QPushButton *buttonOk;
		QSpacerItem *horizontalSpacer;
		QPushButton *buttonNew;
		QSpacerItem *horizontalSpacer_2;
		QPushButton *buttonDelete;
		QSpacerItem *horizontalSpacer_4;
		QPushButton *buttonEdit;
		QSpacerItem *horizontalSpacer_3;
		QPushButton *buttonCancel;
		QLineEdit *editSearch;
		QLabel *label_3;
		QLabel *label_2;
		QDoubleSpinBox *editSale;
		QSpinBox *editQuantity;
		QSpacerItem *verticalSpacer;
		QComboBox *comboMaterial;
		QLabel *label;

	void setupUi(QWidget *AtpClientMaterials) {
		if (AtpClientMaterials->objectName().isEmpty())
			AtpClientMaterials->setObjectName(QStringLiteral("AtpClientMaterials"));
		AtpClientMaterials->resize(468, 422);

		gridLayout_2 = new QGridLayout(AtpClientMaterials);
		gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));

		label_6 = new QLabel(AtpClientMaterials);
		label_6->setObjectName(QStringLiteral("label_6"));
		QFont font;
		font.setPointSize(14);
		font.setBold(true);
		font.setWeight(75);
		label_6->setFont(font);
		label_6->setAlignment(Qt::AlignCenter);
		gridLayout_2->addWidget(label_6, 0, 0, 1, 5);

		editBuy = new QDoubleSpinBox(AtpClientMaterials);
		editBuy->setObjectName(QStringLiteral("editBuy"));
		editBuy->setMaximum(2147483647.00000);
		gridLayout_2->addWidget(editBuy, 7, 0, 1, 2);

		label_5 = new QLabel(AtpClientMaterials);
		label_5->setObjectName(QStringLiteral("label_5"));
		gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

		tableMaterials = new QTableView(AtpClientMaterials);
		tableMaterials->setObjectName(QStringLiteral("tableMaterials"));
		gridLayout_2->addWidget(tableMaterials, 3, 0, 1, 5);

		label_4 = new QLabel(AtpClientMaterials);
		label_4->setObjectName(QStringLiteral("label_4"));
		gridLayout_2->addWidget(label_4, 4, 0, 1, 2);

		gridLayout = new QGridLayout();
		gridLayout->setObjectName(QStringLiteral("gridLayout"));

		buttonOk = new QPushButton(AtpClientMaterials);
		buttonOk->setObjectName(QStringLiteral("buttonOk"));
		QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(buttonOk->sizePolicy().hasHeightForWidth());
		buttonOk->setSizePolicy(sizePolicy);
		gridLayout->addWidget(buttonOk, 0, 0, 1, 1);

		horizontalSpacer = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);
		gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

		buttonNew = new QPushButton(AtpClientMaterials);
		buttonNew->setObjectName(QStringLiteral("buttonNew"));
		sizePolicy.setHeightForWidth(buttonNew->sizePolicy().hasHeightForWidth());
		buttonNew->setSizePolicy(sizePolicy);
		gridLayout->addWidget(buttonNew, 0, 2, 1, 1);

		horizontalSpacer_2 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);
		gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

		buttonDelete = new QPushButton(AtpClientMaterials);
		buttonDelete->setObjectName(QStringLiteral("buttonDelete"));
		sizePolicy.setHeightForWidth(buttonDelete->sizePolicy().hasHeightForWidth());
		buttonDelete->setSizePolicy(sizePolicy);
		gridLayout->addWidget(buttonDelete, 0, 4, 1, 1);

		horizontalSpacer_4 = new QSpacerItem(52, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		gridLayout->addItem(horizontalSpacer_4, 0, 5, 1, 1);

		buttonEdit = new QPushButton(AtpClientMaterials);
		buttonEdit->setObjectName(QStringLiteral("buttonEdit"));
		sizePolicy.setHeightForWidth(buttonEdit->sizePolicy().hasHeightForWidth());
		buttonEdit->setSizePolicy(sizePolicy);
		gridLayout->addWidget(buttonEdit, 0, 6, 1, 1);

		horizontalSpacer_3 = new QSpacerItem(55, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		gridLayout->addItem(horizontalSpacer_3, 0, 7, 1, 1);

		buttonCancel = new QPushButton(AtpClientMaterials);
		buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
		sizePolicy.setHeightForWidth(buttonCancel->sizePolicy().hasHeightForWidth());
		buttonCancel->setSizePolicy(sizePolicy);
		gridLayout->addWidget(buttonCancel, 0, 8, 1, 1);

		gridLayout_2->addLayout(gridLayout, 9, 0, 1, 5);

		editSearch = new QLineEdit(AtpClientMaterials);
		editSearch->setObjectName(QStringLiteral("editSearch"));
		gridLayout_2->addWidget(editSearch, 2, 0, 1, 5);

		label_3 = new QLabel(AtpClientMaterials);
		label_3->setObjectName(QStringLiteral("label_3"));
		gridLayout_2->addWidget(label_3, 6, 0, 1, 1);

		label_2 = new QLabel(AtpClientMaterials);
		label_2->setObjectName(QStringLiteral("label_2"));
		gridLayout_2->addWidget(label_2, 6, 2, 1, 1);

		editSale = new QDoubleSpinBox(AtpClientMaterials);
		editSale->setObjectName(QStringLiteral("editSale"));
		editSale->setMaximum(2147483647.00);
		gridLayout_2->addWidget(editSale, 7, 2, 1, 2);

		editQuantity = new QSpinBox(AtpClientMaterials);
		editQuantity->setObjectName(QStringLiteral("editQuantity"));
		editQuantity->setMaximum(2147483647);
		gridLayout_2->addWidget(editQuantity, 7, 4, 1, 1);

		verticalSpacer = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Fixed);
		gridLayout_2->addItem(verticalSpacer, 8, 3, 1, 1);

		comboMaterial = new QComboBox(AtpClientMaterials);
		comboMaterial->setObjectName(QStringLiteral("comboMaterial"));
		QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
		sizePolicy1.setHorizontalStretch(0);
		sizePolicy1.setVerticalStretch(0);
		sizePolicy1.setHeightForWidth(comboMaterial->sizePolicy().hasHeightForWidth());
		comboMaterial->setSizePolicy(sizePolicy1);
		comboMaterial->setMinimumSize(QSize(230, 23));
		comboMaterial->setMaximumSize(QSize(300, 23));
		comboMaterial->setEditable(true);
		comboMaterial->setInsertPolicy(QComboBox::NoInsert);
		gridLayout_2->addWidget(comboMaterial, 5, 0, 1, 4);

		label = new QLabel(AtpClientMaterials);
		label->setObjectName(QStringLiteral("label"));
		gridLayout_2->addWidget(label, 6, 4, 1, 1);

		retranslateUi(AtpClientMaterials);
	} // setupUi

	void retranslateUi(QWidget *AtpClientMaterials){
		AtpClientMaterials->setWindowTitle(QApplication::translate("AtpClientMaterials", "Client Materials", 0));
	   label_6->setText(QApplication::translate("AtpClientMaterials", "Client Materials Editor", 0));
	   label_5->setText(QApplication::translate("AtpClientMaterials", "Search:", 0));
	   label_4->setText(QApplication::translate("AtpClientMaterials", "Name of material:", 0));
	   label_3->setText(QApplication::translate("AtpClientMaterials", "Buy price:", 0));
	   label_2->setText(QApplication::translate("AtpClientMaterials", "Sale price:", 0));
	   label->setText(QApplication::translate("AtpClientMaterials", "Quantity:", 0));
	   buttonOk->setText(QApplication::translate("AtpClientMaterials", "Ok", 0));
	   buttonNew->setText(QApplication::translate("AtpClientMaterials", "New", 0));
	   buttonDelete->setText(QApplication::translate("AtpClientMaterials", "Delete", 0));
	   buttonEdit->setText(QApplication::translate("AtpClientMaterials", "Edit", 0));
	   buttonCancel->setText(QApplication::translate("AtpClientMaterials", "Cancel", 0));
	} // retranslateUi

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
			editBuy->setEnabled(false);
			editSale->setEnabled(false);
			editQuantity->setEnabled(false);
			comboMaterial->setEnabled(false);
			editSearch->setEnabled(true);
			tableMaterials->setEnabled(true);
		} else if (condition == "enableFields"){
			editBuy->setEnabled(true);
			editSale->setEnabled(true);
			editQuantity->setEnabled(true);
			comboMaterial->setEnabled(true);
			editSearch->setEnabled(false);
			tableMaterials->setEnabled(false);
		} else if (condition == "clearFields"){
			editBuy->clear();
			editSale->clear();
			editQuantity->clear();
			editSearch->clear();
			comboMaterial->setCurrentIndex(-1);
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
	class AtpClientMaterials: public Ui_AtpClientMaterials {};
} // namespace Ui

QT_END_NAMESPACE

#endif // AtpClientMaterialsUI_H
