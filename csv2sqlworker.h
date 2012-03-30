#ifndef CSV2SQLWORKER_H
#define CSV2SQLWORKER_H

#include <QThread>
#include <QSemaphore>
#include <QMutex>


enum WorkEvent {
    WorkEventBegin = 0,
    WorkEventEnd,
    WorkEventNext,
    WorkEventTick,

    WorkEventNum
};

class WorkStatus {
public:
    int csv_files;
    QString cur_file;
    float cur_percent;
};

class Csv2SqlWorker : public QThread
{
    Q_OBJECT
public:
    explicit Csv2SqlWorker(QObject *parent = 0);
    virtual ~Csv2SqlWorker();

    void run();
    void requestWorking(const QString & path);
    void cancelWorking();
    void resetState() {
        mutex.lock();
        busy = false;
        idle = false;
        mutex.unlock();
    }
    bool isBusy() {
        return busy;
    }

private:
    void scaning();
    void processCsvFile(const QString csv_file);

signals:
    void workProcessEvent(WorkEvent, WorkStatus *status);

public slots:

private:
    QSemaphore sem;
    bool quit;
    QString path;

    QMutex mutex;
    bool busy;
    bool idle;

    WorkStatus status;
};

#endif // CSV2SQLWORKER_H
