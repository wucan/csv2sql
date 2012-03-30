#ifndef CSVSIMPLEREADER_H
#define CSVSIMPLEREADER_H

#include <QStringList>
#include <QTextStream>

#include "csvreader.h"


class QIODevice;

class CSVSimpleReader : public CSVReader
{
public:
    CSVSimpleReader(QIODevice *dev);

    virtual QStringList parseLine();
    virtual float getPercent();

private:
    QTextStream text_stream;
    qint64 total_size;
    qint64 cur_pos;
};

#endif // CSVSIMPLEREADER_H
