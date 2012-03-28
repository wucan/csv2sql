#include "csvsimplereader.h"


CSVSimpleReader::CSVSimpleReader(QIODevice *file)
{
    text_stream.setDevice(file);
}

QStringList CSVSimpleReader::parseLine()
{
    QStringList sl;

    QString line = text_stream.readLine();
    if (!line.isNull() && !line.isEmpty()) {
        sl = line.split(',');
    }

    return sl;
}
