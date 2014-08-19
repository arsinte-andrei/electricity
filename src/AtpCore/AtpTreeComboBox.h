#ifndef ATPTREECOMBOBOX_H
#define ATPTREECOMBOBOX_H

#include <QComboBox>
#include <QEvent>
#include <QMouseEvent>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QTreeView>

#include "atpcore_global.h"

class ATPCORE_EXPORT AtpTreeComboBox : public QComboBox{
		Q_OBJECT
	public:
		explicit AtpTreeComboBox(/*QTreeView *treeView, QStandardItemModel *model, */QWidget *parent = 0);

		bool eventFilter(QObject *object, QEvent *event);
		virtual void showPopup();
		virtual void hidePopup();

	signals:

	public slots:

	private:
			bool skipNextHide;

};

#endif // ATPTREECOMBOBOX_H
