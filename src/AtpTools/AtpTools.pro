#-------------------------------------------------
#
# Project created by QtCreator 2014-07-21T23:52:28
#
#-------------------------------------------------

include(../../shared.pri)

TEMPLATE = lib

DEFINES += ATPTOOLS_LIBRARY

SOURCES += AtpToolsSettings.cpp

HEADERS += AtpToolsSettings.h\
		atptools_global.h

FORMS += AtpToolsSettings.ui

CONFIG += plugin
NAME = AtpToolsLib
TARGET = $${NAME}

LIBS += \
	-lAtpCoreLib \
