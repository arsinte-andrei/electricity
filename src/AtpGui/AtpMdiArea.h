#ifndef ATPMDIAREA_H
#define ATPMDIAREA_H

#include "atpguilib_global.h"

#include <QMdiArea>
#include <QTabBar>

#include "AtpDef.h"

class ATPGUILIB_EXPORT AtpMdiArea : public QMdiArea{
		Q_OBJECT
	public:
		explicit AtpMdiArea(QWidget *parent = 0);

	signals:

	public slots:
		void setAtpBackground(AtpDef::mainWindowLoadingStatus bkCode);

	private:
		QTabBar *tabBar;

};

#endif // ATPMDIAREA_H
