#include <stdio.h>

#include <QDebug>
#include <QDir>
#include <QSqlDatabase>
#include <QTime>

#if defined(Q_OS_LINUX)
#include <signal.h>
#endif

#include "AtpSingleApplication.h"
#include "AtpSettings.h"
#include "AtpMainWindow.h"

#if defined(Q_OS_LINUX)
void catchSigPipe(int s){
	qDebug() << "SIGPIPE caught: " << s;
}
#endif

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message) {
	QByteArray localMsg = message.toLocal8Bit();
	QByteArray currentTime = QTime::currentTime().toString().toLocal8Bit();

	switch (type) {
	case QtDebugMsg:
		fprintf(stderr,/* "%s - */ "[%s:%u, %s]\n Debug: %s \n", /*currentTime.constData(),*/ context.file, context.line, context.function, localMsg.constData());
		fflush(stderr);
		break;
	case QtWarningMsg:
		fprintf(stderr, /*"%s - */ "[%s:%u, %s:]\n Warning:  %s\n", /*currentTime.constData(),*/ context.file, context.line, context.function, localMsg.constData());
		fflush(stderr);
		break;
	case QtCriticalMsg:
		fprintf(stderr, "%s - [%s:%u, %s]\n Critical: %s\n", currentTime.constData(), context.file, context.line, context.function, localMsg.constData());
		fflush(stderr);
		break;
	case QtFatalMsg:
		fprintf(stderr, "%s -[%s:%u, %s]\n Fatal:    %s\n", currentTime.constData(), context.file, context.line, context.function, localMsg.constData());
		fflush(stderr);
		abort();
	}
}

int main(int argc, char *argv[]){

//debug
	qInstallMessageHandler(messageHandler);
//start app
	AtpSingleApplication *app = new AtpSingleApplication("atp", argc, argv);
	app->setOrganizationName("atp");
	app->setOrganizationDomain("atp-trading.net");
	app->setApplicationName("Electricity");
	app->setApplicationVersion("1");
	app->setApplicationDisplayName("Electricity");
//sigPipe problems
#if defined(Q_OS_LINUX)
	signal(SIGPIPE,catchSigPipe);
	signal(SIGSEGV,catchSigPipe);
#endif

//detect multiple instance
	if (!AtpSettings::getBoolValue("App/MultipleInstance", false)) {
		// send arguments to running instance for further processing:
		if (app->sendMessage(app->arguments().join("\n"), 30000)) {
			qWarning("Application already running. Aborting...");
			delete app;
			return 0;
		}
	}

//SQLITE
	qDebug() << QSqlDatabase::drivers();

// set current working directory:
	QString appPath = AtpSettings::getApplicationPath();
	QDir::setCurrent(appPath);

// disable Qt library paths to avoid plugins for Qt designer from being found:
	QString pluginPath = AtpSettings::getPluginPath();
	if (pluginPath.isEmpty()) {
		qWarning() << QString("Folder '%1' does not exist").arg(pluginPath);
		delete app;
		return -1;
	}
	app->setLibraryPaths(QStringList() << pluginPath);

//check the data folder
	QString dataBaseFolder = AtpSettings::getDataBasePath();
	if(!dataBaseFolder.endsWith("dataBase")){
		qWarning() << QString("Electricity has no rights in '%1' please edit permisions").arg(dataBaseFolder);
		delete app;
		return -2;
	}

//main window
	AtpMainWindow *win = new AtpMainWindow();
	win->show();
//main run
	int	ret = app->exec();
	qDebug()<< "Del app";
	delete win;
	delete app;
	qDebug()<< "Del app after";
	return ret;
}
