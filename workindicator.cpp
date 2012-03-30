#include <QtGui>

#include "workindicator.h"


WorkIndicator::WorkIndicator(Csv2SqlWorker *worker, QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint), _worker(worker)
{
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
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    /* draw */
    if (_worker->status.csv_files > 0) {
        float left_files_percent = (float)(_worker->status.cur_index + 1) / _worker->status.csv_files;
        float one_file_percent = 1.0 / _worker->status.csv_files;

        QColor filesColor(127, 0, 127);
        QColor percentColor(0, 127, 127, 191);
        painter.setPen(Qt::NoPen);
        painter.setBrush(filesColor);
        painter.drawPie(80,  0, 200, 200, 0, (1 - left_files_percent) * 360 * 16);
        painter.setBrush(percentColor);
        painter.drawPie(80,  0, 200, 200, (1 - left_files_percent) * 360 * 16, one_file_percent * 360 * 16);

        painter.drawPie(300, 0, 200, 200, 0, (1 - _worker->status.cur_percent) * 360 * 16);
    }
}

void WorkIndicator::resizeEvent(QResizeEvent * /* event */)
{
}

QSize WorkIndicator::sizeHint() const
{
    return QSize(100, 100);
}

void WorkIndicator::on_workProcessEvent(WorkEvent event, WorkStatus *status)
{
    update();
}
