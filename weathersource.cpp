#include <QDebug>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QDomDocument>

#include "weathersource.h"


static QNetworkAccessManager *manager;

WeatherSource::WeatherSource()
{
    if (!manager) {
        manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));
    }
}

WeatherSource::~WeatherSource()
{
}

void WeatherSource::update()
{
    manager->get(QNetworkRequest((QUrl("http://www.google.com/ig/api?weather=BeiJing"))));
}

void WeatherSource::replyFinished(QNetworkReply *reply)
{
    QByteArray ba = reply->readAll();
    QDomDocument doc;
    QString err_msg;
    int err_line;

    if (doc.setContent(ba, false, &err_msg, &err_line)) {
        QDomElement root = doc.documentElement();
        QDomElement weather_elem = root.firstChildElement("weather");
        QDomElement current_conditions_elem = weather_elem.firstChildElement("current_conditions");
        QDomElement elem = current_conditions_elem.firstChildElement();
        while (!elem.isNull()) {
            QString tag = elem.tagName();
            if (tag == "condition")
                weather_info.condition = elem.attribute("data");
            else if (tag == "temp_f")
                weather_info.temp_f = elem.attribute("data");
            else if (tag == "temp_c")
                weather_info.temp_c = elem.attribute("data");
            else if (tag == "humidity")
                weather_info.humidity = elem.attribute("data");
            else if (tag == "icon")
                weather_info.icon = elem.attribute("data");
            else if (tag == "wind_condition")
                weather_info.wind_condition = elem.attribute("data");
            else
                qWarning() << "Unknown current_conditions element:" << tag;

            elem = elem.nextSiblingElement();
        }

        qDebug() << weather_info.info();
    } else {
        qWarning() << "Failed to parse weather:" << err_msg << ", line" << err_line;
    }

    reply->deleteLater();
}
