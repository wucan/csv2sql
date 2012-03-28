#ifndef WEATHERSOURCE_H
#define WEATHERSOURCE_H

#include <QObject>


class QNetworkReply;

class WeatherInfo {
public:
    QString condition;
    QString temp_f;
    QString temp_c;
    QString humidity;
    QString icon;
    QString wind_condition;

    QString info() {
        return condition + " " + temp_f + "/" + temp_c + ", " + humidity + ", " + wind_condition;
    }
};

class WeatherSource : public QObject
{
    Q_OBJECT

public:
    WeatherSource();
    ~WeatherSource();

    void update();
    WeatherInfo & getWeatherInfo() {
        return weather_info;
    }

private slots:
    void replyFinished(QNetworkReply *reply);

private:
    WeatherInfo weather_info;
};


#endif // WEATHERSOURCE_H
