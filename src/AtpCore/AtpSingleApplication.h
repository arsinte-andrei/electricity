#ifndef ATPSINGLEAPPLICATION_H
#define ATPSINGLEAPPLICATION_H

#include "atpcore_global.h"

#include <QApplication>

class AtpLocalPeer;

class ATPCORE_EXPORT AtpSingleApplication : public QApplication {
	Q_OBJECT

	public:
		AtpSingleApplication(const QString &id, int &argc, char **argv);
		~AtpSingleApplication();

		static AtpSingleApplication* getInstance();

		bool isRunning();
		QString id() const;

		void setActivationWindow(QWidget *aw, bool activateOnMessage = true);
		QWidget *activationWindow() const;

	public slots:
		bool sendMessage(const QString &message, int timeout = 5000);
		void activateWindow();

	signals:
		void messageReceived(const QString& message);

	private:
		void sysInit(const QString &appId = QString());
		AtpLocalPeer *peer;
		QWidget *actWin;
};

Q_DECLARE_METATYPE(AtpSingleApplication*)

#endif // ATPSINGLEAPPLICATION_H
