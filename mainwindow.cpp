#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "about.h"


static Database db;

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
    } else {
        qDebug() << "stop ...";
        db.closeDatabase();
        ui->action_Start->setIcon(QIcon(":/images/start"));
    }
}

void MainWindow::on_action_About_triggered()
{
    AboutDialog dlg;
    dlg.setModal(false);
    dlg.exec();
}
