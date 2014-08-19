#ifndef UIATPCOMPANYMATERIALS_H
#define UIATPCOMPANYMATERIALS_H

#include <QComboBox>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QTableView>

QT_BEGIN_NAMESPACE

class Ui_AtpCompanyMaterials {

	public:
		QGridLayout *gridLayout_2;
		QGridLayout *gridLayout;
		QSpacerItem *horizontalSpacer_5;
		QSpacerItem *horizontalSpacer_6;
		QSpacerItem *verticalSpacer;
		QSpacerItem *horizontalSpacer;
		QSpacerItem *horizontalSpacer_2;
		QSpacerItem *horizontalSpacer_4;
		QSpacerItem *horizontalSpacer_3;

		QLabel *lblTitle;
		QLabel *lblSearch;
		QLabel *lblName;
		QLabel *lblBuy;
		QLabel *lblSale;
		QLabel *lblSupplier;

		QLineEdit *editBuy;
		QLineEdit *editSale;
		QLineEdit *editSearch;
		QLineEdit *editName;

		QComboBox *comboSupplier;

		QPushButton *buttonOk;
		QPushButton *buttonNew;
		QPushButton *buttonDelete;
		QPushButton *buttonEdit;
		QPushButton *buttonCancel;

		QTableView *tableMaterials;



	void setupUi(QWidget *AtpCompanyMaterials) {
		if (AtpCompanyMaterials->objectName().isEmpty()) {
			AtpCompanyMaterials->setObjectName(QStringLiteral("AtpCompanyMaterials"));
		}
		AtpCompanyMaterials->resize(491, 335);
		AtpCompanyMaterials->setWindowTitle("Materials Editor");

		gridLayout_2 = new QGridLayout(AtpCompanyMaterials);
		gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));

		lblSearch = new QLabel(AtpCompanyMaterials);
		lblSearch->setObjectName(QStringLiteral("lblSearch"));
		lblSearch->setText("Search:");
		gridLayout_2->addWidget(lblSearch, 1, 0, 1, 1);

		lblName = new QLabel(AtpCompanyMaterials);
		lblName->setObjectName(QStringLiteral("lblName"));
		lblName->setText("Name of material:");
		gridLayout_2->addWidget(lblName, 4, 0, 1, 1);

		lblBuy = new QLabel(AtpCompanyMaterials);
		lblBuy->setObjectName(QStringLiteral("lblBuy"));
		lblBuy->setText("Buy price:");
		gridLayout_2->addWidget(lblBuy, 6, 0, 1, 1);

		lblSale = new QLabel(AtpCompanyMaterials);
		lblSale->setObjectName(QStringLiteral("lblSale"));
		lblSale->setText("Sale price:");
		gridLayout_2->addWidget(lblSale, 6, 2, 1, 1);

		lblSupplier = new QLabel(AtpCompanyMaterials);
		lblSupplier->setObjectName(QStringLiteral("lblSupplier"));
		lblSupplier->setText("Supplier:");
		gridLayout_2->addWidget(lblSupplier, 6, 5, 1, 1);

		editBuy = new QLineEdit(AtpCompanyMaterials);
		editBuy->setObjectName(QStringLiteral("editBuy"));
		QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(editBuy->sizePolicy().hasHeightForWidth());
		editBuy->setSizePolicy(sizePolicy);
		gridLayout_2->addWidget(editBuy, 7, 0, 1, 1);

		horizontalSpacer_5 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		gridLayout_2->addItem(horizontalSpacer_5, 7, 1, 1, 1);

		editSale = new QLineEdit(AtpCompanyMaterials);
		editSale->setObjectName(QStringLiteral("editSale"));
		sizePolicy.setHeightForWidth(editSale->sizePolicy().hasHeightForWidth());
		editSale->setSizePolicy(sizePolicy);
		gridLayout_2->addWidget(editSale, 7, 2, 1, 2);

		horizontalSpacer_6 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		gridLayout_2->addItem(horizontalSpacer_6, 7, 4, 1, 1);

		comboSupplier = new QComboBox(AtpCompanyMaterials);
		comboSupplier->setObjectName(QStringLiteral("comboSupplier"));
		QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
		sizePolicy1.setHorizontalStretch(0);
		sizePolicy1.setVerticalStretch(0);
		sizePolicy1.setHeightForWidth(comboSupplier->sizePolicy().hasHeightForWidth());
		comboSupplier->setSizePolicy(sizePolicy1);
		comboSupplier->setMinimumSize(QSize(230, 23));
		comboSupplier->setMaximumSize(QSize(300, 23));
		gridLayout_2->addWidget(comboSupplier, 7, 5, 1, 1);

		verticalSpacer = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Fixed);
		gridLayout_2->addItem(verticalSpacer, 8, 3, 1, 1);

		gridLayout = new QGridLayout();
		gridLayout->setObjectName(QStringLiteral("gridLayout"));
		buttonOk = new QPushButton(AtpCompanyMaterials);
		buttonOk->setObjectName(QStringLiteral("buttonOk"));
		sizePolicy.setHeightForWidth(buttonOk->sizePolicy().hasHeightForWidth());
		buttonOk->setSizePolicy(sizePolicy);
		buttonOk->setText("Ok");
		gridLayout->addWidget(buttonOk, 0, 0, 1, 1);

		horizontalSpacer = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);
		gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

		buttonNew = new QPushButton(AtpCompanyMaterials);
		buttonNew->setObjectName(QStringLiteral("buttonNew"));
		sizePolicy.setHeightForWidth(buttonNew->sizePolicy().hasHeightForWidth());
		buttonNew->setText("New");
		buttonNew->setSizePolicy(sizePolicy);
		gridLayout->addWidget(buttonNew, 0, 2, 1, 1);

		horizontalSpacer_2 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);
		gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

		buttonDelete = new QPushButton(AtpCompanyMaterials);
		buttonDelete->setObjectName(QStringLiteral("buttonDelete"));
		sizePolicy.setHeightForWidth(buttonDelete->sizePolicy().hasHeightForWidth());
		buttonDelete->setSizePolicy(sizePolicy);
		buttonDelete->setText("Delete");
		gridLayout->addWidget(buttonDelete, 0, 4, 1, 1);

		horizontalSpacer_4 = new QSpacerItem(52, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		gridLayout->addItem(horizontalSpacer_4, 0, 5, 1, 1);

		buttonEdit = new QPushButton(AtpCompanyMaterials);
		buttonEdit->setObjectName(QStringLiteral("buttonEdit"));
		sizePolicy.setHeightForWidth(buttonEdit->sizePolicy().hasHeightForWidth());
		buttonEdit->setSizePolicy(sizePolicy);
		buttonEdit->setText("Edit");
		gridLayout->addWidget(buttonEdit, 0, 6, 1, 1);

		horizontalSpacer_3 = new QSpacerItem(55, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		gridLayout->addItem(horizontalSpacer_3, 0, 7, 1, 1);

		buttonCancel = new QPushButton(AtpCompanyMaterials);
		buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
		sizePolicy.setHeightForWidth(buttonCancel->sizePolicy().hasHeightForWidth());
		buttonCancel->setSizePolicy(sizePolicy);
		buttonCancel->setText("Cancel");
		gridLayout->addWidget(buttonCancel, 0, 8, 1, 1);

		gridLayout_2->addLayout(gridLayout, 9, 0, 1, 6);

		tableMaterials = new QTableView(AtpCompanyMaterials);
		tableMaterials->setObjectName(QStringLiteral("tableMaterials"));
		tableMaterials->setSelectionBehavior(QAbstractItemView::SelectRows);
		tableMaterials->setSelectionMode(QAbstractItemView::SingleSelection);
		tableMaterials->setAlternatingRowColors(true);
		gridLayout_2->addWidget(tableMaterials, 3, 0, 1, 6);

		editSearch = new QLineEdit(AtpCompanyMaterials);
		editSearch->setObjectName(QStringLiteral("editSearch"));
		editSearch->setClearButtonEnabled(true);
		editSearch->setPlaceholderText("Search for materials here...");
		gridLayout_2->addWidget(editSearch, 2, 0, 1, 6);

		editName = new QLineEdit(AtpCompanyMaterials);
		editName->setObjectName(QStringLiteral("editName"));
		gridLayout_2->addWidget(editName, 5, 0, 1, 6);

		lblTitle = new QLabel(AtpCompanyMaterials);
		lblTitle->setObjectName(QStringLiteral("lblTitle"));
		QFont font;
		font.setPointSize(14);
		font.setBold(true);
		font.setWeight(75);
		lblTitle->setFont(font);
		lblTitle->setAlignment(Qt::AlignCenter);
		lblTitle->setText("Materials Editor");
		gridLayout_2->addWidget(lblTitle, 0, 0, 1, 6);

		enableAndDisable("reset");
	}

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
			editName->setEnabled(false);
			editSale->setEnabled(false);
			comboSupplier->setEnabled(false);
			editSearch->setEnabled(true);
			tableMaterials->setEnabled(true);
		} else if (condition == "enableFields"){
			editBuy->setEnabled(true);
			editName->setEnabled(true);
			editSale->setEnabled(true);
			comboSupplier->setEnabled(true);
			editSearch->setEnabled(false);
			tableMaterials->setEnabled(false);
		} else if (condition == "clearFields"){
			editName->clear();
			editBuy->clear();
			editSale->clear();
			editSearch->clear();
			comboSupplier->setCurrentIndex(-1);
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
	class AtpCompanyMaterials: public Ui_AtpCompanyMaterials {};
} // namespace Ui

QT_END_NAMESPACE

#endif // AtpCompanyMaterialsUI_H
