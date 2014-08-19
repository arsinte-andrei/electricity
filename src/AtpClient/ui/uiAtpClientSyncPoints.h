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

QT_BEGIN_NAMESPACE

class UiAtpClientSyncPoints{
	public:
		QPushButton *buttonOk;
		QPushButton *buttonCancel;
		QTableView *tableCompPoint;
		QTableView *tableClientPoint;
		QLabel *label;
		QLabel *label_2;
		QCommandLinkButton *buttonFromCompany;
		QCommandLinkButton *buttonFromClient;
		QCheckBox *checkAllCompany;
		QCheckBox *checkAllClient;
		QLineEdit *editSearchCompPoints;
		QLineEdit *editSearchClientPoints;
		QLabel *label_3;
		QLabel *label_4;

	void setupUi(QDialog *AtpClientSyncPoints)    {
		if (AtpClientSyncPoints->objectName().isEmpty())
			AtpClientSyncPoints->setObjectName(QStringLiteral("AtpClientSyncPoints"));
	   AtpClientSyncPoints->resize(565, 506);

	   buttonOk = new QPushButton(AtpClientSyncPoints);
	   buttonOk->setObjectName(QStringLiteral("buttonOk"));
	   buttonOk->setGeometry(QRect(70, 470, 81, 23));

	   buttonCancel = new QPushButton(AtpClientSyncPoints);
	   buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
	   buttonCancel->setGeometry(QRect(390, 470, 81, 23));

	   tableCompPoint = new QTableView(AtpClientSyncPoints);
	   tableCompPoint->setObjectName(QStringLiteral("tableCompantPoint"));
	   tableCompPoint->setGeometry(QRect(20, 100, 256, 291));

	   tableClientPoint = new QTableView(AtpClientSyncPoints);
	   tableClientPoint->setObjectName(QStringLiteral("tableClientPoint"));
	   tableClientPoint->setGeometry(QRect(290, 100, 256, 291));

	   label = new QLabel(AtpClientSyncPoints);
	   label->setObjectName(QStringLiteral("label"));
	   label->setGeometry(QRect(20, 70, 131, 20));
	   label_2 = new QLabel(AtpClientSyncPoints);
	   label_2->setObjectName(QStringLiteral("label_2"));
	   label_2->setGeometry(QRect(290, 70, 131, 20));

	   buttonFromCompany = new QCommandLinkButton(AtpClientSyncPoints);
	   buttonFromCompany->setObjectName(QStringLiteral("buttonFromCompany"));
	   buttonFromCompany->setGeometry(QRect(20, 420, 256, 41));

	   buttonFromClient = new QCommandLinkButton(AtpClientSyncPoints);
	   buttonFromClient->setObjectName(QStringLiteral("buttonFromClient"));
	   buttonFromClient->setGeometry(QRect(290, 420, 256, 41));

	   checkAllCompany = new QCheckBox(AtpClientSyncPoints);
	   checkAllCompany->setObjectName(QStringLiteral("checAllCompany"));
	   checkAllCompany->setGeometry(QRect(20, 400, 85, 21));
	   checkAllCompany->setTristate(true);
	   checkAllCompany->setCheckState(Qt::PartiallyChecked);

	   checkAllClient = new QCheckBox(AtpClientSyncPoints);
	   checkAllClient->setObjectName(QStringLiteral("checkAllClient"));
	   checkAllClient->setGeometry(QRect(290, 400, 85, 21));
	   checkAllClient->setTristate(true);
	   checkAllClient->setCheckState(Qt::PartiallyChecked);

	   editSearchCompPoints = new QLineEdit(AtpClientSyncPoints);
	   editSearchCompPoints->setObjectName(QStringLiteral("editSearchCompPoints"));
	   editSearchCompPoints->setGeometry(QRect(20, 40, 251, 23));

	   editSearchClientPoints = new QLineEdit(AtpClientSyncPoints);
	   editSearchClientPoints->setObjectName(QStringLiteral("editSearchClientPoints"));
	   editSearchClientPoints->setGeometry(QRect(290, 40, 251, 23));

	   label_3 = new QLabel(AtpClientSyncPoints);
	   label_3->setObjectName(QStringLiteral("label_3"));
	   label_3->setGeometry(QRect(20, 10, 131, 20));
	   label_4 = new QLabel(AtpClientSyncPoints);
	   label_4->setObjectName(QStringLiteral("label_4"));
	   label_4->setGeometry(QRect(290, 10, 131, 20));

		retranslateUi(AtpClientSyncPoints);
	} // setupUi

	void retranslateUi(QDialog *AtpClientSyncPoints){
	   AtpClientSyncPoints->setWindowTitle(QApplication::translate("AtpClientSyncPoints", "Dialog", 0));
	   buttonOk->setText(QApplication::translate("AtpClientSyncPoints", "&Ok", 0));
	   buttonCancel->setText(QApplication::translate("AtpClientSyncPoints", "&Cancel", 0));
	   label->setText(QApplication::translate("AtpClientSyncPoints", "Company Points List", 0));
	   label_2->setText(QApplication::translate("AtpClientSyncPoints", "Client Points List", 0));
	   buttonFromCompany->setText(QApplication::translate("AtpClientSyncPoints", "From Company to Client", 0));
	   buttonFromClient->setText(QApplication::translate("AtpClientSyncPoints", "From Client to Company", 0));
	   checkAllCompany->setText(QApplication::translate("AtpClientSyncPoints", "Select All", 0));
	   checkAllClient->setText(QApplication::translate("AtpClientSyncPoints", "Select All", 0));
	   label_3->setText(QApplication::translate("AtpClientSyncPoints", "Search:", 0));
	   label_4->setText(QApplication::translate("AtpClientSyncPoints", "Search:", 0));
	   } // retranslateUi

};

namespace Ui {
	class AtpClientSyncPoints: public UiAtpClientSyncPoints {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ATPCLIENTSYNCPOINTSNA4529_H
