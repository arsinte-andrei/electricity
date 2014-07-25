#-------------------------------------------------
#
# Project created by QtCreator 2014-07-01T15:50:29
#
#-------------------------------------------------

include(../../shared.pri)
TEMPLATE = lib

DEFINES += ATPCORE_LIBRARY

SOURCES += \
    AtpSingleApplication.cpp \
    AtpLocalPeer.cpp \
	AtpLockedFile.cpp \
    AtpSettings.cpp \
    AtpDb.cpp

win32 {
	SOURCES += AtpLockedFile_win.cpp
}
else {
	SOURCES += AtpLockedFile_unix.cpp
}

HEADERS +=\
        atpcore_global.h \
    AtpSingleApplication.h \
    AtpLocalPeer.h \
    AtpLockedFile.h \
    AtpSettings.h \
    AtpDb.h

CONFIG += plugin
NAME = AtpCoreLib
TARGET = $${NAME}
