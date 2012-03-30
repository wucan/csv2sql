#include <QtGui>

#include "workindicator.h"


WorkIndicator::WorkIndicator(Csv2SqlWorker *worker, QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), _worker(worker)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    QAction *quitAction = new QAction(tr("E&xit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    addAction(quitAction);

    setContextMenuPolicy(Qt::ActionsContextMenu);
    setToolTip(tr("Drag the diagram with the left mouse button.\n"
                  "Use the right mouse button to open a context menu."));
    setWindowTitle(tr("Work Status Indicator"));

    connect(_worker, SIGNAL(workProcessEvent(WorkEvent, WorkStatus*)),
            this, SLOT(on_workProcessEvent(WorkEvent, WorkStatus*)));
}

void WorkIndicator::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void WorkIndicator::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void WorkIndicator::paintEvent(QPaintEvent *)
{
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };

    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);

    int side = qMin(width(), height());
    QTime time = QTime::currentTime();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);

    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    painter.setPen(hourColor);

    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    painter.setPen(minuteColor);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }
}

void WorkIndicator::resizeEvent(QResizeEvent * /* event */)
{
    int side = qMin(width(), height());
    QRegion maskedRegion(width() / 2 - side / 2, height() / 2 - side / 2, side,
                         side, QRegion::Ellipse);
    setMask(maskedRegion);
}

QSize WorkIndicator::sizeHint() const
{
    return QSize(100, 100);
}

void WorkIndicator::on_workProcessEvent(WorkEvent event, WorkStatus *status)
{
    qDebug() << "event:" << event << ", files:" << status->csv_files
             << ", cur:" << status->cur_file << ", percent:" << status->cur_percent;
}
