#ifndef ATPLOCALPEER_H
#define ATPLOCALPEER_H

#include "atpcore_global.h"

#include <QLocalServer>
#include <QLocalSocket>
#include <QDir>

#include "AtpLockedFile.h"


class ATPCORE_EXPORT AtpLocalPeer : public QObject {
	Q_OBJECT

public:
	AtpLocalPeer(QObject *parent=0, const QString &appId = QString());
	~AtpLocalPeer();
	bool isClient();
	bool sendMessage(const QString &message, int timeout);
	QString applicationId() const {
		return id;
	}

signals:
	void messageReceived(const QString &message);

protected slots:
	void receiveConnection();

protected:
	QString id;
	QString socketName;
	QLocalServer *server;
	AtpLockedFile lockFile;

private:
	static const char *ack;
};

#endif // ATPLOCALPEER_H
