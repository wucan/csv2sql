#ifndef _ABOUT_H_
#define _ABOUT_H_

#include <QDialog>

#include "ui_about.h"


class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    AboutDialog();

private:
    Ui::aboutWidget ui;

public slots:
    virtual void close();
};


#endif /* _ABOUT_H_ */

