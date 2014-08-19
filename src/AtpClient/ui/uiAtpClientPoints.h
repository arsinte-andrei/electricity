#ifndef UIATPCLIENTPOINTS
#define UIATPCLIENTPOINTS

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class uiAtpClientPoints {
public:
	QGridLayout *gridLayout;
	QLineEdit *editPrice2;
	QLineEdit *editPrice1;
	QHBoxLayout *horizontalLayout;
	QPushButton *buttonOk;
	QPushButton *buttonNew;
	QPushButton *buttonDelete;
	QPushButton *buttonEdit;
	QPushButton *buttonSync;
	QPushButton *buttonCancel;
	QLineEdit *editName;
	QLabel *label_3;
	QTableView *tablePoint;
	QLabel *label;
	QLineEdit *editSearch;
	QLabel *label_2;
	QLabel *label_4;

	void setupUi(QWidget *AtpClientPoints){
		if (AtpClientPoints->objectName().isEmpty())
			AtpClientPoints->setObjectName(QStringLiteral("AtpClientPoints"));
		AtpClientPoints->resize(639, 379);
		AtpClientPoints->setWindowTitle("Company Point price editor");

		gridLayout = new QGridLayout(AtpClientPoints);
		gridLayout->setObjectName(QStringLiteral("gridLayout"));

		editPrice2 = new QLineEdit(AtpClientPoints);
		editPrice2->setObjectName(QStringLiteral("editPrice2"));
		QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(editPrice2->sizePolicy().hasHeightForWidth());
		editPrice2->setSizePolicy(sizePolicy);
		gridLayout->addWidget(editPrice2, 5, 3, 1, 1);

		editPrice1 = new QLineEdit(AtpClientPoints);
		editPrice1->setObjectName(QStringLiteral("editPrice1"));
		sizePolicy.setHeightForWidth(editPrice1->sizePolicy().hasHeightForWidth());
		editPrice1->setSizePolicy(sizePolicy);
		gridLayout->addWidget(editPrice1, 5, 2, 1, 1);

		horizontalLayout = new QHBoxLayout();
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		buttonOk = new QPushButton(AtpClientPoints);
		buttonOk->setObjectName(QStringLiteral("buttonOk"));
		sizePolicy.setHeightForWidth(buttonOk->sizePolicy().hasHeightForWidth());
		buttonOk->setSizePolicy(sizePolicy);
		buttonOk->setText("&Ok");
		horizontalLayout->addWidget(buttonOk);

		buttonNew = new QPushButton(AtpClientPoints);
		buttonNew->setObjectName(QStringLiteral("buttonNew"));
		sizePolicy.setHeightForWidth(buttonNew->sizePolicy().hasHeightForWidth());
		buttonNew->setSizePolicy(sizePolicy);
		buttonNew->setText("&New");
		horizontalLayout->addWidget(buttonNew);

		buttonDelete = new QPushButton(AtpClientPoints);
		buttonDelete->setObjectName(QStringLiteral("buttonDelete"));
		sizePolicy.setHeightForWidth(buttonDelete->sizePolicy().hasHeightForWidth());
		buttonDelete->setSizePolicy(sizePolicy);
		buttonDelete->setText("&Delete");
		horizontalLayout->addWidget(buttonDelete);

		buttonEdit = new QPushButton(AtpClientPoints);
		buttonEdit->setObjectName(QStringLiteral("buttonEdit"));
		sizePolicy.setHeightForWidth(buttonEdit->sizePolicy().hasHeightForWidth());
		buttonEdit->setSizePolicy(sizePolicy);
		buttonEdit->setText("&Edit");
		horizontalLayout->addWidget(buttonEdit);

		buttonSync = new QPushButton(AtpClientPoints);
		buttonSync->setObjectName(QStringLiteral("buttonSync"));
		sizePolicy.setHeightForWidth(buttonSync->sizePolicy().hasHeightForWidth());
		buttonSync->setSizePolicy(sizePolicy);
		buttonSync->setText("&Sync");
		horizontalLayout->addWidget(buttonSync);

		buttonCancel = new QPushButton(AtpClientPoints);
		buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
		sizePolicy.setHeightForWidth(buttonCancel->sizePolicy().hasHeightForWidth());
		buttonCancel->setSizePolicy(sizePolicy);
		buttonCancel->setText("&Cancel");
		horizontalLayout->addWidget(buttonCancel);

		gridLayout->addLayout(horizontalLayout, 6, 1, 1, 2);

		editName = new QLineEdit(AtpClientPoints);
		editName->setObjectName(QStringLiteral("editName"));
		gridLayout->addWidget(editName, 5, 0, 1, 2);

		label_3 = new QLabel(AtpClientPoints);
		label_3->setObjectName(QStringLiteral("label_3"));
		label_3->setAlignment(Qt::AlignCenter);
		label_3->setText("Point price:");
		gridLayout->addWidget(label_3, 4, 2, 1, 2);

		tablePoint = new QTableView(AtpClientPoints);
		tablePoint->setObjectName(QStringLiteral("tablePoint"));
		gridLayout->addWidget(tablePoint, 3, 0, 1, 4);

		label = new QLabel(AtpClientPoints);
		label->setObjectName(QStringLiteral("label"));
		label->setText("Search:");
		gridLayout->addWidget(label, 1, 0, 1, 1);

		editSearch = new QLineEdit(AtpClientPoints);
		editSearch->setObjectName(QStringLiteral("editSearch"));
		gridLayout->addWidget(editSearch, 2, 0, 1, 4);

		label_2 = new QLabel(AtpClientPoints);
		label_2->setObjectName(QStringLiteral("label_2"));
		label_2->setText("Point name:");
		gridLayout->addWidget(label_2, 4, 0, 1, 1);

		label_4 = new QLabel(AtpClientPoints);
		label_4->setObjectName(QStringLiteral("label_4"));
		QFont font;
		font.setPointSize(14);
		label_4->setFont(font);
		label_4->setAlignment(Qt::AlignCenter);
		label_4->setText("Points editor");
		gridLayout->addWidget(label_4, 0, 0, 1, 4);
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
			editPrice2->setEnabled(false);
			editPrice1->setEnabled(false);
			editName->setEnabled(false);
			editSearch->setEnabled(true);
			editSearch->clear();
			tablePoint->setEnabled(true);
		} else if (condition == "enableFields"){
			editName->setEnabled(true);
			editPrice1->setEnabled(true);
			editPrice2->setEnabled(true);
			editSearch->setEnabled(false);
			tablePoint->setEnabled(false);
		} else if (condition == "clearFields"){
			editName->clear();
			editPrice1->clear();
			editPrice2->clear();
			editSearch->clear();
			tablePoint->clearSelection();
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
	class AtpClientPoints: public uiAtpClientPoints {};
} // namespace Ui

QT_END_NAMESPACE

#endif // uiAtpClientPoints
