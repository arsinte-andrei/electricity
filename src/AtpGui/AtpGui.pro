#-------------------------------------------------
#
# Project created by QtCreator 2014-07-01T15:27:08
#
#-------------------------------------------------
include(../../shared.pri)
TEMPLATE = lib

DEFINES += ATPGUI_LIBRARY

SOURCES += \
	AtpMainWindow.cpp

HEADERS +=\
		atpguilib_global.h \
	AtpMainWindow.h

CONFIG += plugin
NAME = AtpGuiLib
TARGET = $${NAME}

LIBS += \
	-lAtpCoreLib \
	-lAtpToolsLib \
	-lAtpCompanyLib \
