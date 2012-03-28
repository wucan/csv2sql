#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    
private slots:
    void on_action_Start_triggered(bool checked);

    void on_action_About_triggered();

    void on_action_Prefences_triggered();

    void weather_timer_timeout();

private:
    Ui::MainWindow *ui;
    QTimer weather_timer;
};

#endif // MAINWINDOW_H
