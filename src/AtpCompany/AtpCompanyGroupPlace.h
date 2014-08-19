#ifndef AtpCompanyGroupPlace_H
#define AtpCompanyGroupPlace_H

#include "atpcompany_global.h"

#include <QWidget>
#include <QStandardItem>
#include <QTreeView>

namespace Ui {
	class AtpCompanyGroupPlace;
}

class ATPCOMPANY_EXPORT AtpCompanyGroupPlace : public QWidget{
		Q_OBJECT

	public:
		explicit AtpCompanyGroupPlace(QWidget *parent = 0);
		~AtpCompanyGroupPlace();

	private slots:
		void onButtonOkClicked();
		void onButtonNewClicked();
		void onButtonDeleteClicked();
		void onButtonEditClicked();
		void onButtonCancelClicked();
		void onTableGroupClicked();
		void onMycomboCurrentIndexChanged();

		void resetVars();

	signals:
		void currentIndexChanged(int newIndex);
		void exitSignal();

	private:
		Ui::AtpCompanyGroupPlace *ui;
		QStandardItem *parent;
		QStandardItemModel *myModel;
		QMap<int, QStandardItem*> rowItemMap;
		int grupId, grupParent, CgrupId, CgrupParent;
		bool seEediteaza, eNou, eVechi;
		QString grupName;

		void updateDb();

		void addNewRecord();
		void deleteRecord(int id);
		bool ckDbIntegrity();
		void restoreTreeStructure(int id);
};

#endif // AtpCompanyGroupPlace_H
