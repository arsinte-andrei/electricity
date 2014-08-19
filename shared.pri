#-------------------------------------------------
#
# Project created by @atp@ 30/06/2014 08:16:09
#
#-------------------------------------------------

DEFINES += ATP_LIBRARY

# output directory:

CONFIG(debug, debug|release) {
	ROUTDIR = debug
} else {
	ROUTDIR = release
}

CONFIG(plugin, plugin) {
	build_pass:CONFIG(debug, debug|release) {
		TARGET = $$join(TARGET,,,_debug)

		# Qt uses '_debug' for unix and 'd' for Windows
		# which is not reliably detectable (e.g.: abcd.dll)
		# unix: TARGET = $$join(TARGET,,,_debug)
		# else: TARGET = $$join(TARGET,,,d)
	}
}

QT += core \
	gui \
#	script \
#	scripttools \
	sql \
#	svg \
	network \
	printsupport \
	xml \
	xmlpatterns \
#	help \
	designer \
	uitools \
	widgets \
	webkitwidgets

CONFIG -= warn_off
CONFIG += warn_on
CONFIG += debug_and_release ordered embed_manifest_dll embed_manifest_exe

QMAKE_TARGET_COMPANY = atp-trading.net
QMAKE_TARGET_DESCRIPTION = an application for people involved in electric jobs
QMAKE_TARGET_COPYRIGHT = Open Source
QMAKE_TARGET_PRODUCT = atpElectricity Application Framework

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

DESTDIR = $$PWD/$$ROUTDIR
UI_DIR = .ui

LIBS += -L$$PWD/$$ROUTDIR

INCLUDEPATH += \
	$$PWD/src/AtpCore \
	$$PWD/src/AtpTools \
	$$PWD/src/AtpClient \
	$$PWD/src/AtpCompany \
	$$PWD/src/AtpGui
