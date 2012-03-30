#ifndef WORKINDICATOR_H
#define WORKINDICATOR_H

#include <QWidget>

class WorkIndicator : public QWidget
{
    Q_OBJECT

public:
    WorkIndicator(QWidget *parent = 0);
    QSize sizeHint() const;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QPoint dragPosition;
};

#endif
