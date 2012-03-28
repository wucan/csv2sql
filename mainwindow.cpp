#include <QDebug>
#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "weathersource.h"
#include "about.h"
#include "preferences.h"


static Database db;
static WeatherSource weather_src;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Start_triggered(bool checked)
{
    if (checked) {
        qDebug() << "start ...";
        db.openDatabase();
        ui->action_Start->setIcon(QIcon(":/images/stop"));
        startCollectWeather();
    } else {
        qDebug() << "stop ...";
        db.closeDatabase();
        ui->action_Start->setIcon(QIcon(":/images/start"));
        stopCollectWeather();
    }
}

void MainWindow::on_action_About_triggered()
{
    AboutDialog dlg;
    dlg.setModal(false);
    dlg.exec();
}

void MainWindow::on_action_Prefences_triggered()
{
    PreferencesDialog dlg;
    dlg.setModal(false);
    dlg.exec();
}

void MainWindow::weather_timer_timeout()
{
    weather_src.update();
}

void MainWindow::startCollectWeather()
{
    weather_timer_timeout();

    weather_timer.setInterval(SettingsData::inst().csv_interval.toInt() * 60 * 1000);
    weather_timer.setSingleShot(false);
    connect(&weather_timer, SIGNAL(timeout()), this, SLOT(weather_timer_timeout()));
    weather_timer.start();
}

void MainWindow::stopCollectWeather()
{
    weather_timer.stop();
}
