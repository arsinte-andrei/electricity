#-------------------------------------------------
#
# Project created by QtCreator 2014-07-21T20:44:49
#
#-------------------------------------------------

include(../../shared.pri)

TEMPLATE = lib

DEFINES += ATPCOMPANY_LIBRARY

CONFIG += plugin
NAME = AtpCompanyLib
TARGET = $${NAME}

LIBS += \
	-lAtpCoreLib \

HEADERS += \
    atpcompany_global.h \
    AtpCompanyChuse.h \
    AtpCompanyEdit.h \
    AtpCompanyGroupPlace.h \
    AtpCompanyMaterials.h \
    AtpCompanyPoints.h \
    ui/uiAtpCompanyChuse.h \
    ui/uiAtpCompanyEdit.h \
    ui/uiAtpCompanyMaterials.h \
    AtpCompanySuppliers.h \
    ui/uiAtpCompanySuppliers.h \
    ui/uiAtpCompanyPoints.h \
    ui/uiAtpCompanyGroupPlace.h

SOURCES += \
    AtpCompanyChuse.cpp \
    AtpCompanyEdit.cpp \
    AtpCompanyGroupPlace.cpp \
    AtpCompanyMaterials.cpp \
    AtpCompanyPoints.cpp \
    AtpCompanySuppliers.cpp
