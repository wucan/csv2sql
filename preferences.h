#ifndef _PREFERENCES_H_
#define _PREFERENCES_H_

#include <QDialog>

#include "ui_preferences.h"


class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    PreferencesDialog();

private:
    Ui::preferencesDialog ui;

private slots:
    void ok();

public slots:
    virtual void close();
};


#endif /* _PREFERENCES_H_ */

