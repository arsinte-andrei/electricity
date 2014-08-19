#-------------------------------------------------
#
# Project created by QtCreator 2014-07-01T15:27:08
#
#-------------------------------------------------
include(../../shared.pri)
TEMPLATE = lib

DEFINES += ATPGUI_LIBRARY

SOURCES += \
	AtpMainWindow.cpp \
	AtpMdiArea.cpp

HEADERS +=\
		atpguilib_global.h \
	AtpMainWindow.h \
	AtpMdiArea.h \

CONFIG += plugin
NAME = AtpGuiLib
TARGET = $${NAME}

LIBS += \
	-lAtpCoreLib \
	-lAtpToolsLib \
	-lAtpCompanyLib \
	-lAtpClientLib \

RESOURCES += \
	png32/png32.qrc
