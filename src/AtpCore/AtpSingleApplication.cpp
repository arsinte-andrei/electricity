#include "AtpSingleApplication.h"

#include <QDebug>
#include <QWidget>

#include "AtpLocalPeer.h"

void AtpSingleApplication::sysInit(const QString &appId) {
	qDebug()<<"AtpSingleApplication sysInit";
	actWin = 0;
	peer = new AtpLocalPeer(this, appId);
	connect(peer, SIGNAL(messageReceived(const QString&)), SIGNAL(messageReceived(const QString&)));
}

AtpSingleApplication::AtpSingleApplication(const QString &id, int &argc, char **argv) : QApplication(argc, argv) {
	qDebug()<<"Start AtpSingleApplication";
	sysInit(id);
}

AtpSingleApplication::~AtpSingleApplication(){
	qDebug()<<"Exit AtpSingleApplication";
}

bool AtpSingleApplication::isRunning() {
	qDebug()<<"AtpSingleApplication isRunning";
	return peer->isClient();
}

bool AtpSingleApplication::sendMessage(const QString &message, int timeout) {
	qDebug()<<"AtpSingleApplication sendMessage";
	return peer->sendMessage(message, timeout);
}

QString AtpSingleApplication::id() const {
	qDebug()<<"AtpSingleApplication id";
	return peer->applicationId();
}

void AtpSingleApplication::setActivationWindow(QWidget *aw, bool activateOnMessage) {
	qDebug()<<"AtpSingleApplication setActiveWindow";
	actWin = aw;
	if (activateOnMessage)
		connect(peer, SIGNAL(messageReceived(const QString&)), this, SLOT(activateWindow()));
	else
		disconnect(peer, SIGNAL(messageReceived(const QString&)), this, SLOT(activateWindow()));
}

QWidget* AtpSingleApplication::activationWindow() const {
	qDebug()<<"AtpSingleApplication activationWindow";
	return actWin;
}

void AtpSingleApplication::activateWindow() {
	qDebug()<<"AtpSingleApplication activateWindow";
	if (actWin) {
		actWin->setWindowState(actWin->windowState() & ~Qt::WindowMinimized);
		actWin->raise();
		actWin->activateWindow();
	}
}
