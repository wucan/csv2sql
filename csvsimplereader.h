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

private:
    QTextStream text_stream;
};

#endif // CSVSIMPLEREADER_H
