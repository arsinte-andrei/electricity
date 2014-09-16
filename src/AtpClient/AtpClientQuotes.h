#ifndef ATPCLIENTQUOTES_H
#define ATPCLIENTQUOTES_H

#include "atpclient_global.h"
#include <QWidget>
/*
namespace Ui {
	class AtpClientQuotes;
}
*/
class ATPCLIENT_EXPORT AtpClientQuotes : public QWidget{
		Q_OBJECT

	public:
		explicit AtpClientQuotes(QWidget *parent = 0);
		~AtpClientQuotes();

	private:
//		Ui::AtpClientQuotes *ui;
};

#endif // AtpClientQuotes_H
