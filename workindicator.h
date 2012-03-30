#ifndef WORKINDICATOR_H
#define WORKINDICATOR_H

#include <QWidget>

#include "csv2sqlworker.h"


class WorkIndicator : public QWidget
{
    Q_OBJECT

public:
    WorkIndicator(Csv2SqlWorker *worker, QWidget *parent = 0);
    QSize sizeHint() const;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_workProcessEvent(WorkEvent event, WorkStatus *status);

private:
    QPoint dragPosition;
    Csv2SqlWorker *_worker;
};

#endif
