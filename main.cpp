#include <QtGui/QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* i18n */
    QString locale = QLocale::system().name();
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + locale,
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);
    QTranslator myappTranslator;
    myappTranslator.load("lang_" + locale);
    a.installTranslator(&myappTranslator);

    MainWindow w;
    w.show();
    
    return a.exec();
}
