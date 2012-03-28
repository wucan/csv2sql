#ifndef CSVREADER_H
#define CSVREADER_H

#include <QStringList>


class QIODevice;

class CSVReader
{
public:
    virtual QStringList parseLine() = 0;
};

#endif // CSVREADER_H
