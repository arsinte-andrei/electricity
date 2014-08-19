#-------------------------------------------------
#
# Project created by QtCreator 2014-07-30T14:23:28
#
#-------------------------------------------------

include(../../shared.pri)

TEMPLATE = lib

DEFINES += ATPCLIENT_LIBRARY


CONFIG += plugin
NAME = AtpClientLib
TARGET = $${NAME}

LIBS += \
	-lAtpCoreLib \

HEADERS += \
	atpclient_global.h \
	AtpClientEditList.h \
	AtpClientInvoices.h \
	AtpClientQuotes.h \
	AtpClientReceipts.h \
	ui/uiAtpClientEditList.h \
	AtpClientChuse.h \
	ui/uiAtpClientChuse.h \
	AtpClientPoints.h \
	ui/uiAtpClientPoints.h \
	AtpClientSyncPoints.h \
	ui/uiAtpClientSyncPoints.h

SOURCES += \
	AtpClientEditList.cpp \
	AtpClientInvoices.cpp \
	AtpClientQuotes.cpp \
	AtpClientReceipts.cpp \
	AtpClientChuse.cpp \
	AtpClientPoints.cpp \
	AtpClientSyncPoints.cpp
