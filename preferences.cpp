#include <QPushButton>
#include <QSettings>

#include "preferences.h"


PreferencesDialog::PreferencesDialog()
{
    /* build ui */
    ui.setupUi(this);

    setWindowTitle("Preferences");
    setWindowModality(Qt::WindowModal);

    connect(ui.buttonBox->buttons().at(0), SIGNAL(clicked()), this, SLOT(ok()));
    connect(ui.buttonBox->buttons().at(1), SIGNAL(clicked()), this, SLOT(close()));
    ui.buttonBox->buttons().at(1)->setFocus();

    /*
     * restore settings
     */
    QSettings settings("csv2sql.ini", QSettings::IniFormat);
    settings.beginGroup("csv");
    ui.lineEdit_csv_path->setText(settings.value("path", QCoreApplication::applicationDirPath()).toString());
    ui.lineEdit_csv_interval->setText(settings.value("interval", 10).toString());
    settings.endGroup();
    settings.beginGroup("db");
    ui.lineEdit_db_host->setText(settings.value("host", "127.0.0.1").toString());
    ui.lineEdit_db_name->setText(settings.value("name", "adidas").toString());
    ui.lineEdit_db_user->setText(settings.value("user", "adidas").toString());
    ui.lineEdit_db_password->setText(settings.value("password", "adidas").toString());
    settings.endGroup();
}

void PreferencesDialog::close()
{
	done(0);
}

void PreferencesDialog::ok()
{
    /*
     * store settings
     */
    QSettings settings("csv2sql.ini", QSettings::IniFormat);
    settings.beginGroup("csv");
    settings.setValue("path", ui.lineEdit_csv_path->text());
    settings.setValue("interval", ui.lineEdit_csv_interval->text());
    settings.endGroup();

    settings.beginGroup("db");
    settings.setValue("host", ui.lineEdit_db_host->text());
    settings.setValue("name", ui.lineEdit_db_name->text());
    settings.setValue("user", ui.lineEdit_db_user->text());
    settings.setValue("password", ui.lineEdit_db_password->text());
    settings.endGroup();

    done(0);
}
