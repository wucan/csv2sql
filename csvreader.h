#ifndef CSVREADER_H
#define CSVREADER_H

#include <QStringList>


class QIODevice;

class CSVReader
{
public:
    virtual QStringList parseLine() = 0;
    virtual float getPercent() = 0;
    virtual qint64 currentPosition() = 0;
    virtual bool seek(qint64 pos) = 0;
};

#endif // CSVREADER_H
