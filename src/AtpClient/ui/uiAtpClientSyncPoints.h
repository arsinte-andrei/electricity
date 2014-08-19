#ifndef UIATPCLIENTSYNCPOINTS_H
#define UIATPCLIENTSYNCPOINTS_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QCheckBox>
#include <QCommandLinkButton>
#include <QDialog>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QLineEdit>
#include <QGridLayout>

QT_BEGIN_NAMESPACE

class UiAtpClientSyncPoints{
	public:
		QGridLayout *gridLayout;
		QLabel *label_3;
		QLineEdit *editSearchCompPoints;
		QLabel *label;
		QTableView *tableCompPoint;
		QCheckBox *checkAllCompany;
		QPushButton *buttonOk;
		QPushButton *buttonCancel;

	void setupUi(QDialog *AtpClientSyncPoints)    {
		if (AtpClientSyncPoints->objectName().isEmpty())
			AtpClientSyncPoints->setObjectName(QStringLiteral("AtpClientSyncPoints"));
		AtpClientSyncPoints->setWindowModality(Qt::WindowModal);
		AtpClientSyncPoints->resize(480, 340);
		QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(AtpClientSyncPoints->sizePolicy().hasHeightForWidth());
		AtpClientSyncPoints->setSizePolicy(sizePolicy);
		AtpClientSyncPoints->setModal(true);
		gridLayout = new QGridLayout(AtpClientSyncPoints);
		gridLayout->setObjectName(QStringLiteral("gridLayout"));
		label_3 = new QLabel(AtpClientSyncPoints);
		label_3->setObjectName(QStringLiteral("label_3"));
		gridLayout->addWidget(label_3, 0, 0, 1, 2);

		editSearchCompPoints = new QLineEdit(AtpClientSyncPoints);
		editSearchCompPoints->setObjectName(QStringLiteral("editSearchCompPoints"));
		gridLayout->addWidget(editSearchCompPoints, 1, 0, 1, 4);

		label = new QLabel(AtpClientSyncPoints);
		label->setObjectName(QStringLiteral("label"));
		gridLayout->addWidget(label, 2, 0, 1, 2);

		tableCompPoint = new QTableView(AtpClientSyncPoints);
		tableCompPoint->setObjectName(QStringLiteral("tableCompPoint"));
		gridLayout->addWidget(tableCompPoint, 3, 0, 1, 4);

		checkAllCompany = new QCheckBox(AtpClientSyncPoints);
		checkAllCompany->setObjectName(QStringLiteral("checkAllCompany"));
		checkAllCompany->setTristate(true);
		gridLayout->addWidget(checkAllCompany, 4, 0, 1, 1);

		buttonOk = new QPushButton(AtpClientSyncPoints);
		buttonOk->setObjectName(QStringLiteral("buttonOk"));
		gridLayout->addWidget(buttonOk, 4, 2, 1, 1);

		buttonCancel = new QPushButton(AtpClientSyncPoints);
		buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
		gridLayout->addWidget(buttonCancel, 4, 3, 1, 1);


		retranslateUi(AtpClientSyncPoints);
	} // setupUi

	void retranslateUi(QDialog *AtpClientSyncPoints){
		AtpClientSyncPoints->setWindowTitle(QApplication::translate("AtpClientSyncPoints", "Points Price Sync", 0));
		label_3->setText(QApplication::translate("AtpClientSyncPoints", "Search:", 0));
		label->setText(QApplication::translate("AtpClientSyncPoints", "Company Points List", 0));
		checkAllCompany->setText(QApplication::translate("AtpClientSyncPoints", "Select All", 0));
		buttonOk->setText(QApplication::translate("AtpClientSyncPoints", "&Ok", 0));
		buttonCancel->setText(QApplication::translate("AtpClientSyncPoints", "&Cancel", 0));
	} // retranslateUi

};

namespace Ui {
	class AtpClientSyncPoints: public UiAtpClientSyncPoints {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ATPCLIENTSYNCPOINTSNA4529_H
