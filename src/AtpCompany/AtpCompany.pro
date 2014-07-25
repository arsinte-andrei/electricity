#-------------------------------------------------
#
# Project created by QtCreator 2014-07-21T20:44:49
#
#-------------------------------------------------

include(../../shared.pri)

TEMPLATE = lib

DEFINES += ATPCOMPANY_LIBRARY

SOURCES += AtpChuseCompany.cpp \
    AtpEditCompany.cpp

HEADERS +=\
		atpcompany_global.h \
	AtpChuseCompany.h \
    AtpEditCompany.h

CONFIG += plugin
NAME = AtpCompanyLib
TARGET = $${NAME}

FORMS += \
	AtpChuseCompany.ui \
    AtpEditCompany.ui

LIBS += \
	-lAtpCoreLib \
