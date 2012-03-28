#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSystemTrayIcon>

#include "weathersource.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void startCollectWeather();
    void stopCollectWeather();
    
private:
    void createActions();
    void createTrayIcon();
    void setVisible(bool visible);

protected:
	void closeEvent(QCloseEvent *event);

private slots:
    void on_action_Start_triggered(bool checked);

    void on_action_About_triggered();

    void on_action_Prefences_triggered();

    void weather_timer_timeout();
    void weather_updated(WeatherInfo &info);

    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void messageClicked();

private:
    Ui::MainWindow *ui;
    QTimer weather_timer;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

#endif // MAINWINDOW_H
