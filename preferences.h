#ifndef _PREFERENCES_H_
#define _PREFERENCES_H_

#include <QDialog>

#include "ui_preferences.h"


class SettingsData {
private:
    SettingsData();

public:
    static SettingsData & inst();

    QString city;
    QString csv_path;
    QString csv_interval;
    QString db_host;
    QString db_name;
    QString db_user;
    QString db_password;

    QString sn;
    QString rn;
};

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    PreferencesDialog();

private:
    Ui::preferencesDialog ui;

private slots:
    void ok();

    void on_pushButton_csv_path_browse_clicked();

public slots:
    virtual void close();
};


#endif /* _PREFERENCES_H_ */

