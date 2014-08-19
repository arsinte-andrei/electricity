#include "AtpTreeComboBox.h"

AtpTreeComboBox::AtpTreeComboBox(/*QTreeView *treeView, QStandardItemModel *model, */QWidget *parent) :	QComboBox(parent),  skipNextHide(false){
	setModel(new QStandardItemModel);
	setView(new QTreeView);
//	setModel(model);
//	setView(treeView);
	view()->viewport()->installEventFilter(this);
}

bool AtpTreeComboBox::eventFilter(QObject *object, QEvent *event){
	if (event->type() == QEvent::MouseButtonPress && object == view()->viewport()) {
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
		QModelIndex index = view()->indexAt(mouseEvent->pos());
		if (!view()->visualRect(index).contains(mouseEvent->pos()))
			skipNextHide = true;
	}
	return false;

}

void AtpTreeComboBox::showPopup(){
	setMaxVisibleItems(10);
	setRootModelIndex(QModelIndex());
	QComboBox::showPopup();
}

void AtpTreeComboBox::hidePopup(){
	//setRootModelIndex(view()->currentIndex().parent());
	//setCurrentIndex(view()->currentIndex().row());
	if (skipNextHide)
		skipNextHide = false;
	else
		QComboBox::hidePopup();
}
