#include "AtpLockedFile.h"

#include <QDebug>

AtpLockedFile::AtpLockedFile() : QFile() {
#ifdef Q_OS_WIN
	wmutex = 0;
	rmutex = 0;
#endif
	m_lock_mode = NoLock;
}

AtpLockedFile::AtpLockedFile(const QString &name) : QFile(name) {
#ifdef Q_OS_WIN
	wmutex = 0;
	rmutex = 0;
#endif
	m_lock_mode = NoLock;
}

bool AtpLockedFile::open(OpenMode mode) {
	if (mode & QIODevice::Truncate) {
		qWarning("AtpLockedFile::open(): Truncate mode not allowed.");
		return false;
	}
	return QFile::open(mode);
}

bool AtpLockedFile::isLocked() const {
	return m_lock_mode != NoLock;
}

AtpLockedFile::LockMode AtpLockedFile::lockMode() const {
	return m_lock_mode;
}
