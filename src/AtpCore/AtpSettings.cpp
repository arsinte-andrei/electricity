#include "AtpSettings.h"

#include <QDebug>
#include <QApplication>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDir>

QVariantMap AtpSettings::cache;
QMap<QString, QSettings *> AtpSettings::mySettings;

QString AtpSettings::getAppId() {
	QString ret = qApp->applicationName();
	ret.replace(QRegExp("[^a-zA-Z0-9]"), "");
	// prevent 'empty record name' exception:
	if (ret.isEmpty()) {
		ret = "@atp@";
	}
	return ret;
}

QString AtpSettings::getMainWindowTitle(){
	return QString("@atp@");
}

QString AtpSettings::getAppVersion(){
	return QString("1.0");
}

QString AtpSettings::getApplicationPath() {
	QDir dirName(QApplication::applicationDirPath());
	qDebug() << dirName.path();
	return dirName.path();
}

QString AtpSettings::getPluginPath() {
	QDir appDir = QDir(getApplicationPath());

	QString pluginFolder = "plugins";
	if (!appDir.cd(pluginFolder)) {
		qWarning() << QString("Folder '%1' does not exist").arg(pluginFolder);
		return pluginFolder;
	}
	return appDir.path();
}

QString AtpSettings::getDataBasePath() {
	QDir appDir = QDir(getApplicationPath());

	QString dbFolder = "dataBase";
	if (!appDir.cd(dbFolder)) {
		qWarning() << QString("Folder '%1' does not exist").arg(dbFolder);
		if(appDir.mkdir(dbFolder)){
			appDir.cd(dbFolder);
		}
	}
	return appDir.path();
}

QString AtpSettings::getCompanyPath(QString companyFilesFolder, bool isNew) {
	QDir appDir = QDir(getDataBasePath());
	if (!appDir.cd(companyFilesFolder)) {
		qWarning() << QString("Folder '%1' does not exist").arg(companyFilesFolder);
		if (isNew){
			if(appDir.mkdir(companyFilesFolder)){
				appDir.cd(companyFilesFolder);
			} else {
				qWarning() << QString("Error no permission in '%1' does not exist").arg(companyFilesFolder);
			}
		}
	}
	return appDir.path();
}


QSettings *AtpSettings::getMySettings(QString iniFileName){
	if (mySettings.value(iniFileName)==NULL) {
		QString iniFileNameAndPath;
		iniFileNameAndPath = getApplicationPath() + "/" + iniFileName;
		qDebug() << iniFileNameAndPath;
		QSettings *setari;
		setari = new QSettings(iniFileNameAndPath ,QSettings::IniFormat);
		setari->setPath(QSettings::IniFormat, QSettings::UserScope, AtpSettings::getApplicationPath());
		setari->setDefaultFormat(QSettings::IniFormat);
		setari->setFallbacksEnabled(false);
		mySettings.insert(iniFileName, setari);
		qDebug()<< "A" << iniFileNameAndPath;
		qDebug()<< "B" << setari->fileName();
	}
	return mySettings.value(iniFileName);
}

void AtpSettings::setValue(const QString &key, const QVariant &value, QString iniFileName){
	cache[key] = value;
	getMySettings(iniFileName)->setValue(key, value);
	getMySettings(iniFileName)->sync();
	qDebug() << getMySettings(iniFileName)->fileName();
	qDebug() << key << " -- " << value;
}

void AtpSettings::removeValue(const QString &key, QString iniFileName){
	cache.remove(key);
	getMySettings(iniFileName)->remove(key);
}

QVariant AtpSettings::getValue(const QString &key, const QVariant &defaultValue, QString iniFileName){
	if (cache.contains(key)) {
		return cache[key];
	}

	// slow operation:
	QVariant ret = getMySettings(iniFileName)->value(key, defaultValue);
	cache[key] = ret;
	return ret;
}

bool AtpSettings::getBoolValue(const QString &key, bool defaultValue, QString iniFileName){
	return getValue(key, defaultValue, iniFileName).toBool();
}

double AtpSettings::getDoubleValue(const QString &key, double defaultValue, QString iniFileName){
	return getValue(key, defaultValue, iniFileName).toDouble();
}

int AtpSettings::getIntValue(const QString &key, int defaultValue, QString iniFileName){
	return getValue(key, defaultValue, iniFileName).toInt();
}

QString AtpSettings::getStringValue(const QString &key, const QString &defaultValue, QString iniFileName){
	return getValue(key, defaultValue, iniFileName).toString();
}

QPoint AtpSettings::getPointValue(const QString &key, const QPoint &defaultValue, QString iniFileName){
	return getValue(key, defaultValue, iniFileName).toPoint();
}

QSize AtpSettings::getSizeValue(const QString &key, const QSize &defaultValue, QString iniFileName){
	return getValue(key, defaultValue, iniFileName).toSize();
}
