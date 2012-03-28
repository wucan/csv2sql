#-------------------------------------------------
#
# Project created by QtCreator 2012-03-27T14:45:38
#
#-------------------------------------------------

QT       += core gui sql network xml

TARGET = csv2sql
TEMPLATE = app
VERSION = 0.1


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    weathersource.cpp \
    about.cpp \
    preferences.cpp \
    csv.cpp

HEADERS  += mainwindow.h \
    database.h \
    weathersource.h \
    about.h \
    preferences.h \
    csv.h

FORMS    += mainwindow.ui \
    about.ui \
    preferences.ui

RESOURCES += \
    resource.qrc

DEFINES += APP_VERSION=\\\"$${VERSION}\\\"
