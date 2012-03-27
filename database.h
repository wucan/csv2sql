#ifndef DATABASE_H
#define DATABASE_H

class Database
{
public:
    Database();

    bool openDatabase();

private:
    bool checkDatabase();

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
