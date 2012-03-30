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
    csv.cpp \
    csv2sqlworker.cpp \
    csvsimplereader.cpp \
    registerdialog.cpp \
    shapedclock.cpp \
    workindicator.cpp

HEADERS  += mainwindow.h \
    database.h \
    weathersource.h \
    about.h \
    preferences.h \
    csv.h \
    csv2sqlworker.h \
    csvreader.h \
    csvsimplereader.h \
    registerdialog.h \
    shapedclock.h \
    workindicator.h

FORMS    += mainwindow.ui \
    about.ui \
    preferences.ui

RESOURCES += \
    resource.qrc

DEFINES += APP_VERSION=\\\"$${VERSION}\\\"

TRANSLATIONS += lang_zh_CN.ts
