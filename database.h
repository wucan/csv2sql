#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>


class Database
{
public:
    Database();
    ~Database();

    bool openDatabase();
    void closeDatabase();

private:
    bool checkDatabase();

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
