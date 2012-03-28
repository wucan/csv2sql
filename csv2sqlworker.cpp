#include <QSemaphore>
#include <QDebug>
#include <QDir>
#include <QFile>

#include "csv2sqlworker.h"
#include "preferences.h"
#include "csvsimplereader.h"
#include "database.h"


extern Database db;

Csv2SqlWorker::Csv2SqlWorker(QObject *parent) :
    QThread(parent)
{
    quit = false;
    busy = false;
    idle = false;
}

Csv2SqlWorker::~Csv2SqlWorker()
{
    if (isRunning()) {
        quit = true;
        sem.release();
        wait();
    }
}

void Csv2SqlWorker::run()
{
    while (true) {
        sem.acquire();
        if (quit)
            break;
        mutex.lock();
        if (idle)
            continue;
        busy = true;
        mutex.unlock();
        scaning();
        mutex.lock();
        busy = false;
        mutex.unlock();
    }
}

void Csv2SqlWorker::requestWorking(const QString & path)
{
    if (!isRunning()) {
        start();
    }

    this->path = path;

    sem.release();
}

void Csv2SqlWorker::cancelWorking()
{
    mutex.lock();
    if (busy) {
        idle = true;
    }
    mutex.unlock();
    /* TODO: */
}

void Csv2SqlWorker::scaning()
{
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Time | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                               .arg(fileInfo.fileName()));
        processCsvFile(fileInfo.filePath());
        mutex.lock();
        if (idle)
            return;
        mutex.unlock();
    }
}

void Csv2SqlWorker::processCsvFile(const QString csv_file)
{
    QFile f(csv_file);
    if (!f.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "File busy:" << csv_file;
        return;
    }

    CSVSimpleReader csv(&f);
    QStringList sl = csv.parseLine();
    while (!sl.isEmpty()) {
        if (sl.size() == CSVRecord::Columns) {
            CSVRecord csv_rec(sl);
            db.insertRecord(csv_rec);
        } else {
            qWarning() << "invalidate csv record: " << sl;
        }
        sl = csv.parseLine();
    }

    /* at last delete the csv file! */
    QFile::remove(csv_file);
}
