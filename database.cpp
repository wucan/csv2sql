#include <QtSql>
#include <QSqlDatabase>
#include <QODBCDriver>
#include <QMessageBox>

#include "database.h"

Database::Database()
{
}

Database::~Database()
{
	closeDatabase();
}

bool Database::checkDatabase()
{
    /* check ODBC driver support */
    QStringList sl = QSqlDatabase::drivers();
    qDebug() << "Support database drivers:";
    for (int i = 0; i < sl.size(); ++i)
        qDebug() << " " << sl.at(i).toLocal8Bit().constData();

    if (!QSqlDatabase::isDriverAvailable("QODBC")) {
        qWarning() << "SQLServer database driver not available, check it!";
        return false;
    }

    return true;
}

bool Database::openDatabase()
{
    if (!checkDatabase())
        return false;

    db = QSqlDatabase::addDatabase("QODBC");
    if (!db.isValid()) {
        qCritical() << "QODBC driver is invalidate!";
        return false;
    }

    qDebug("connectting to database...");

    db.setHostName("127.0.0.1");
    db.setDatabaseName("adidas");
    db.setUserName("adidas");
    db.setPassword("adidas");
    if (!db.open()) {
        QMessageBox::critical(NULL, "Cannot open database",
                              db.lastError().text(),
                              QMessageBox::Ok);
        return false;
    }

    /* dump database info */
    QSqlQuery query;
    if (!query.exec("SELECT * FROM entrance")) {
        qWarning() << query.lastError();
    }
    QSqlRecord rec = query.record();
    qDebug() << "Columns in table entrance:";
    for (int i = 0; i < rec.count(); i++)
        qDebug() << " " << rec.fieldName(i);

    return true;
}

void Database::closeDatabase()
{
    if (db.isOpen())
        db.close();
}

bool Database::insertRecord(CSVRecord &csv_rec)
{
    QSqlQuery query;
    query.prepare("INSERT INTO entrance (Date, Time, Site, Store, InCount, OutCount) "
                  "VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(csv_rec.date);
    query.addBindValue(csv_rec.time);
    query.addBindValue(csv_rec.site);
    query.addBindValue(csv_rec.store);
    query.addBindValue(csv_rec.in);
    query.addBindValue(csv_rec.out);
    if (!query.exec()) {
        qWarning() << query.lastError().text();
    }

    return true;
}
