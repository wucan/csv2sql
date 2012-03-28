#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>


class CSVRecord {
public:
    static const int Columns = 6;

public:
    CSVRecord(const QStringList &sl) {
        date = sl.at(0);
        time = sl.at(1);
        site = sl.at(2);
        store = sl.at(3);
        in = sl.at(4);
        out = sl.at(5);
    }

    QString date;
    QString time;
    QString site;
    QString store;
    QString in;
    QString out;
};

class Database
{
public:
    Database();
    ~Database();

    bool openDatabase();
    void closeDatabase();
    bool insertRecord(CSVRecord &csv_rec);

private:
    bool checkDatabase();

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
