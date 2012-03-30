#include "csvsimplereader.h"


CSVSimpleReader::CSVSimpleReader(QIODevice *file)
{
    text_stream.setDevice(file);
    total_size = file->size();
    /* incase zero size */
    if (total_size <= 0)
        total_size = 0xFFFFFFFF;
    cur_pos = 0;
}

QStringList CSVSimpleReader::parseLine()
{
    QStringList sl;

    QString line = text_stream.readLine();
    if (!line.isNull() && !line.isEmpty()) {
        sl = line.split(',');
    }
    cur_pos += line.size();

    return sl;
}

float CSVSimpleReader::getPercent()
{
    return ((float)cur_pos / total_size);
}
