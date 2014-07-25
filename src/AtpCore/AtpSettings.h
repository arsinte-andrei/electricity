#ifndef ATPSETTINGS_H
#define ATPSETTINGS_H

#include "atpcore_global.h"

#include <QPoint>
#include <QSize>
#include <QSettings>
#include <QString>

#ifndef ATPDEFAULT_QVARIANT
#define ATPDEFAULT_QVARIANT QVariant()
#endif

class ATPCORE_EXPORT AtpSettings{

	public:
		static QString getAppId();
		static QString getMainWindowTitle();
		static QString getAppVersion();

		static QString getApplicationPath();
		static QString getPluginPath();

		static QSettings *getMySettings(QString iniFileName = "atp.ini");
		static void setValue(const QString& key, const QVariant& value, QString iniFileName = "atp.ini");
		static void removeValue(const QString& key, QString iniFileName);

		static QVariant getValue(const QString &key, const QVariant& defaultValue = ATPDEFAULT_QVARIANT, QString iniFileName = "atp.ini");
		static bool getBoolValue(const QString &key, bool defaultValue, QString iniFileName = "atp.ini");
		static double getDoubleValue(const QString &key, double defaultValue, QString iniFileName = "atp.ini");
		static int getIntValue(const QString &key, int defaultValue, QString iniFileName = "atp.ini");
		static QString getStringValue(const QString &key, const QString &defaultValue, QString iniFileName = "atp.ini");
		static QPoint getPointValue(const QString &key, const QPoint &defaultValue, QString iniFileName = "atp.ini");
		static QSize getSizeValue(const QString &key, const QSize &defaultValue, QString iniFileName = "atp.ini");

	private:
		static QVariantMap cache; // cache for faster access
		static QMap<QString, QSettings *> mySettings;
};

Q_DECLARE_METATYPE(AtpSettings*)

#endif
