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

qint64 CSVSimpleReader::currentPosition()
{
    return cur_pos;
}

bool CSVSimpleReader::seek(qint64 pos)
{
    while (true) {
        QString line = text_stream.readLine();
        if (line.isNull() || line.isEmpty())
            return false;
        cur_pos += line.size();
        if (cur_pos == pos)
            return true;
        else if (cur_pos > pos)
            return false;
    }
}
