#ifndef CSV2SQLWORKER_H
#define CSV2SQLWORKER_H

#include <QThread>
#include <QSemaphore>


class Csv2SqlWorker : public QThread
{
    Q_OBJECT
public:
    explicit Csv2SqlWorker(QObject *parent = 0);
    virtual ~Csv2SqlWorker();

    void run();
    void requestWorking(const QString & path);

private:
    void scaning();
    void processCsvFile(const QString csv_file);

signals:

public slots:

private:
    QSemaphore sem;
    bool quit;
    QString path;
};

#endif // CSV2SQLWORKER_H
