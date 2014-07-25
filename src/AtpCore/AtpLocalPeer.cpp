#include "AtpLocalPeer.h"

#include <QCoreApplication>
#include <QTime>
#include <QDebug>

#if defined(Q_OS_WIN)
#include <QLibrary>
#include <qt_windows.h>
typedef BOOL(WINAPI*PProcessIdToSessionId)(DWORD,DWORD*);
static PProcessIdToSessionId pProcessIdToSessionId = 0;
#endif
#if defined(Q_OS_UNIX)
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#endif

const char* AtpLocalPeer::ack = "ack";

AtpLocalPeer::AtpLocalPeer(QObject *parent, const QString &appId) : QObject(parent), id(appId) {
	qDebug() << "AtpLocalPeer START";
	QString prefix = id;
	if (id.isEmpty()) {
		id = QCoreApplication::applicationFilePath();
#if defined(Q_OS_WIN)
		id = id.toLower();
#endif
		prefix = id.section(QLatin1Char('/'), -1);
	}
	prefix.remove(QRegExp("[^a-zA-Z]"));
	prefix.truncate(6);

	QByteArray idc = id.toUtf8();
	quint16 idNum = qChecksum(idc.constData(), idc.size());
	socketName = QLatin1String("qtsingleapp-") + prefix + QLatin1Char('-') + QString::number(idNum, 16);

#if defined(Q_OS_WIN)
	if (!pProcessIdToSessionId) {
		QLibrary lib("kernel32");
		pProcessIdToSessionId = (PProcessIdToSessionId)lib.resolve("ProcessIdToSessionId");
	}
	if (pProcessIdToSessionId) {
		DWORD sessionId = 0;
		pProcessIdToSessionId(GetCurrentProcessId(), &sessionId);
		socketName += QLatin1Char('-') + QString::number(sessionId, 16);
	}
#else
	socketName += QLatin1Char('-') + QString::number(::getuid(), 16);
#endif

	server = new QLocalServer(this);
	QString lockName = QDir(QDir::tempPath()).absolutePath()
					   + QLatin1Char('/') + socketName
					   + QLatin1String("-lockfile");
	lockFile.setFileName(lockName);
	lockFile.open(QIODevice::ReadWrite);
}

AtpLocalPeer::~AtpLocalPeer(){
	qDebug() << "AtpLocalPeer end";
}

bool AtpLocalPeer::isClient() {
	qDebug() << "AtpLocalPeer isClient";
	if (lockFile.isLocked())
		return false;

	if (!lockFile.lock(AtpLockedFile::WriteLock, false))
		return true;

	bool res = server->listen(socketName);
#if defined(Q_OS_UNIX) && (QT_VERSION >= QT_VERSION_CHECK(4,5,0))
	// ### Workaround
	if (!res && server->serverError() == QAbstractSocket::AddressInUseError) {
		QFile::remove(QDir::cleanPath(QDir::tempPath())+QLatin1Char('/')+socketName);
		res = server->listen(socketName);
	}
#endif
	if (!res)
		qWarning("QtSingleCoreApplication: listen on local socket failed, %s", qPrintable(server->errorString()));
	QObject::connect(server, SIGNAL(newConnection()), SLOT(receiveConnection()));
	return false;
}

bool AtpLocalPeer::sendMessage(const QString& message, int timeout) {
	qDebug() << "AtpLocalPeer sendMessage";
	if (!isClient())
		return false;

	QLocalSocket socket;
	bool connOk = false;
	for(int i = 0; i < 2; i++) {
		// Try twice, in case the other instance is just starting up
		socket.connectToServer(socketName);
		connOk = socket.waitForConnected(timeout/2);
		if (connOk || i)
			break;
		int ms = 250;
#if defined(Q_OS_WIN)
		Sleep(DWORD(ms));
#else
		struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
		nanosleep(&ts, NULL);
#endif
	}
	if (!connOk)
		return false;

	QByteArray uMsg(message.toUtf8());
	QDataStream ds(&socket);
	ds.writeBytes(uMsg.constData(), uMsg.size());
	bool res = socket.waitForBytesWritten(timeout);
	if (res) {
		res &= socket.waitForReadyRead(timeout);   // wait for ack
		if (res) {
			res &= (socket.read(qstrlen(ack)) == ack);
		}
	}
	return res;
}

void AtpLocalPeer::receiveConnection() {
	qDebug() << "AtpLocalPeer receiveConnection";
	QLocalSocket *socket = server->nextPendingConnection();
	if (!socket)
		return;

	while (socket->bytesAvailable() < (int)sizeof(quint32))
		socket->waitForReadyRead();
	QDataStream ds(socket);
	QByteArray uMsg;
	quint32 remaining;
	ds >> remaining;
	uMsg.resize(remaining);
	int got = 0;
	char *uMsgBuf = uMsg.data();
	do {
		got = ds.readRawData(uMsgBuf, remaining);
		remaining -= got;
		uMsgBuf += got;
	} while (remaining && got >= 0 && socket->waitForReadyRead(2000));
	if (got < 0) {
		qWarning() << "AtpLocalPeer: Message reception failed" << socket->errorString();
		delete socket;
		return;
	}
	QString message(QString::fromUtf8(uMsg));
	socket->write(ack, qstrlen(ack));
	socket->waitForBytesWritten(1000);
	socket->waitForDisconnected(1000); // make sure client reads ack
	delete socket;
	emit messageReceived(message);
}
