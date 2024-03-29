#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDesktopWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "weathersource.h"
#include "about.h"
#include "preferences.h"
#include "csv2sqlworker.h"
#include "registerdialog.h"
#include "workindicator.h"


Database db;
static WeatherSource weather_src;
static Csv2SqlWorker worker;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("CSV2SQL");
    setWindowIcon(QIcon(":/images/logo"));
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - width()) / 2, (desktop->height() - height()) / 2);

    indicator = new WorkIndicator(&worker, this);
    ui->horizontalLayout_status->addWidget(indicator);

    /*
     * create tray icon
     */
    createActions();
    createTrayIcon();
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->setToolTip(tr("CSV2SQL"));
    trayIcon->setIcon(QIcon(":/images/logo"));
    trayIcon->show();

    ui->action_Start->setEnabled(RegisterDialog::isRegistered());

    cancel_progress_dialog.setLabelText(tr("Wait for current csv file completed ..."));
    cancel_progress_dialog.setCancelButtonText(tr("Abort and Quit"));
    cancel_progress_dialog.setModal(true);
    connect(&cancel_progress_dialog, SIGNAL(canceled()), this, SLOT(cancel_progress_diglog_canceled()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    qDebug() << "start ...";
    db.openDatabase();
    ui->action_Start->setIcon(QIcon(":/images/stop"));
    startCollectWeather();
    startWork();
}

void MainWindow::stop()
{
    qDebug() << "stop ...";
    if (worker.isBusy()) {
        worker.cancelWorking();
        connect(&worker, SIGNAL(workProcessEvent(WorkEvent,WorkStatus*)),
                this, SLOT(workProcessEventHandler(WorkEvent,WorkStatus*)));
        int rc = cancel_progress_dialog.exec();
        if (rc == -1) {
            // user canceled, force break out the working
            worker.forceCancelWorking();
        }
        disconnect(&worker, SIGNAL(workProcessEvent(WorkEvent,WorkStatus*)),
                   this, SLOT(workProcessEventHandler(WorkEvent,WorkStatus*)));
    }
    db.closeDatabase();
    ui->action_Start->setIcon(QIcon(":/images/start"));
    stopCollectWeather();
    stopWork();
}

void MainWindow::on_action_Start_triggered(bool checked)
{
    if (checked) {
        start();
    } else {
        stop();
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
    if (dlg.exec() && ui->action_Start->isChecked()) {
        stop();
        start();
    }
}

void MainWindow::weather_timer_timeout()
{
    weather_src.update();
}

void MainWindow::weather_updated(WeatherInfo &info)
{
    ui->label_google_weather->setText(info.info());
}

void MainWindow::startCollectWeather()
{
    connect(&weather_src, SIGNAL(updated(WeatherInfo&)), this, SLOT(weather_updated(WeatherInfo&)));
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

void MainWindow::directoryChanged(const QString &path)
{
    worker.requestWorking(path);
}

void MainWindow::startWork()
{
    worker.resetState();
    worker.requestWorking(SettingsData::inst().csv_path);

    fs_watcher.addPath(SettingsData::inst().csv_path);
    connect(&fs_watcher, SIGNAL(directoryChanged(const QString &)), this, SLOT(directoryChanged(const QString &)));
}

void MainWindow::stopWork()
{
    disconnect(&fs_watcher, SIGNAL(directoryChanged(const QString &)), this, SLOT(directoryChanged(const QString &)));
    fs_watcher.removePaths(fs_watcher.directories());
}

void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(on_action_Exit_triggered()));
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

void MainWindow::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);

    QMainWindow::setVisible(visible);
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        setVisible(!isVisible());
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        break;
    }
}

void MainWindow::messageClicked()
{
    QMessageBox::information(0, tr("Systray"), tr("CSV2SQL"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isVisible()) {
        hide();
        event->ignore();
    }
}

void MainWindow::on_action_Iconize_triggered()
{
    hide();
}

void MainWindow::on_action_Register_triggered()
{
    RegisterDialog dialog(this);
    dialog.setModal(false);
    dialog.exec();

    ui->action_Start->setEnabled(RegisterDialog::isRegistered());
}

void MainWindow::on_action_Exit_triggered()
{
    if (ui->action_Start->isChecked())
        stop();

    hide();
    close();
}

void MainWindow::workProcessEventHandler(WorkEvent event, WorkStatus *status)
{
    cancel_progress_dialog.setValue(status->cur_percent * 100);
    if (event == WorkEventEnd)
        cancel_progress_dialog.close();
}

void MainWindow::cancel_progress_diglog_canceled()
{
    cancel_progress_dialog.setResult(-1);
    cancel_progress_dialog.close();
}
