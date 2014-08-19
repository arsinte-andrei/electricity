#ifndef ATPCLIENTINVOICES_H
#define ATPCLIENTINVOICES_H

#include "atpclient_global.h"
#include <QWidget>

namespace Ui {
	class AtpClientInvoices;
}

class ATPCLIENT_EXPORT AtpClientInvoices : public QWidget{
		Q_OBJECT

	public:
		explicit AtpClientInvoices(QWidget *parent = 0);
		~AtpClientInvoices();

	private:
		Ui::AtpClientInvoices *ui;
};

#endif // AtpClientInvoices_H
