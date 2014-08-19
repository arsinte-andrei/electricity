#ifndef ATPCLIENTRECEIPTS_H
#define ATPCLIENTRECEIPTS_H

#include "atpclient_global.h"
#include <QWidget>

namespace Ui {
	class AtpClientReceipts;
}

class ATPCLIENT_EXPORT AtpClientReceipts : public QWidget{
		Q_OBJECT

	public:
		explicit AtpClientReceipts(QWidget *parent = 0);
		~AtpClientReceipts();

	private:
		Ui::AtpClientReceipts *ui;
};

#endif // AtpClientReceipts_H
