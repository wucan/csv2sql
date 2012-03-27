#-------------------------------------------------
#
# Project created by QtCreator 2012-03-27T14:45:38
#
#-------------------------------------------------

QT       += core gui sql network xml

TARGET = csv2sql
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    weathersource.cpp

HEADERS  += mainwindow.h \
    database.h \
    weathersource.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
