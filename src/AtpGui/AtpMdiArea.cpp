#include "AtpMdiArea.h"
#include <QMdiSubWindow>

#include <QTextEdit>
#include <QPushButton>

#include <QDebug>
#include <QFontMetrics>
#include <QPixmap>
#include <QPainter>
#include <QColor>

AtpMdiArea::AtpMdiArea(QWidget *parent) : QMdiArea(parent){
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setViewMode(QMdiArea::TabbedView);
	setTabsClosable(true);
	setTabsMovable(true);
}

void AtpMdiArea::setAtpBackground(AtpDef::mainWindowLoadingStatus bkCode){
	int sizeX, sizeY, fontBold, fontBold2;
	qreal fontSize, fontSize2, x0, y0, x1, y1;
	bool font1Ok, font2Ok;
	QString str1, str2;

	sizeX = size().width();
	sizeY = size().height();
	QPixmap pix = QPixmap(sizeX, sizeY);
	pix.fill(Qt::blue);

	QPainter painter( &pix );
	QImage bkImage = QImage(":/elec.png");
	bkImage = bkImage.scaled(sizeX, sizeY);
	painter.drawImage(0, 0, bkImage);
	pix.fromImage(bkImage);

	if (bkCode == AtpDef::allLoadedOk){
		qDebug() << "allOk";

	} else {
		if(bkCode == AtpDef::noCompanyLoaded){
			qDebug() << "noCompany";
			str1 = "No Company Loaded";
			str2 = "Load a Company from Company -> Chuse Company";
		} else if (bkCode == AtpDef::noDataBaseLoaded){
			qDebug() << "noDataBase";
			str1 = "No DataBase Loaded";
			str2 = "Load a DataBase in Tools -> Settings";
		}
		//Font1
		font1Ok = false;
		QFont bkFont1;
		fontSize = sizeY * 0.1;
		fontBold = 99;
		bkFont1.setFamily("Arial");
		do {
			bkFont1.setPointSizeF(fontSize);
		//	bkFont1.setWeight(fontBold);
			QFontMetrics fm1(bkFont1);
			int text1Width = fm1.width(str1);
			int text1Height = fm1.height();
			x0 = (sizeX / 2) - (text1Width / 2);
			y0 = (sizeY * 0.25) + (text1Height);
			if ((text1Width + 50) > sizeX) {
				fontSize = fontSize - 1;
			} else {
				font1Ok = true;
			}
		} while (!font1Ok);

		//Font2
		font2Ok = false;
		QFont bkFont2;
		fontSize2 = sizeY * 0.05;
		fontBold2 = 99;
		bkFont2.setFamily("Arial");
		do {
			bkFont2.setPointSizeF(fontSize2);
		//	bkFont2.setWeight(fontBold);
			QFontMetrics fm2(bkFont2);
			int text1Width2 = fm2.width(str2);
			int text1Height2 = fm2.height();
			x1 = (sizeX / 2) - (text1Width2 / 2);
			y1 = (sizeY * 0.45) + (text1Height2);
			if ((text1Width2 + 50) > sizeX) {
				fontSize2 = fontSize2 - 1;
			} else {
				font2Ok = true;
			}
		} while (!font2Ok);

		painter.setFont(bkFont1);
		QColor culoare;
		culoare.setRgb(255,0,0);
		painter.setPen(culoare);
		painter.drawText( QPointF(x0, y0), str1);
		painter.setFont(bkFont2);
		painter.drawText( QPointF(x1, y1), str2);
	}
	setBackground(pix);
}
