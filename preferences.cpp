#include <QPushButton>
#include <QSettings>

#include "preferences.h"


SettingsData::SettingsData()
{
    /*
     * restore settings
     */
    QSettings settings("csv2sql.ini", QSettings::IniFormat);
    settings.beginGroup("csv");
    csv_path = settings.value("path", QCoreApplication::applicationDirPath()).toString();
    csv_interval = settings.value("interval", 10).toString();
    settings.endGroup();
    settings.beginGroup("db");
    db_host = settings.value("host", "127.0.0.1").toString();
    db_name = settings.value("name", "adidas").toString();
    db_user = settings.value("user", "adidas").toString();
    db_password = settings.value("password", "adidas").toString();
    settings.endGroup();
}

SettingsData & SettingsData::inst()
{
    static SettingsData data;

    return data;
}

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
    ui.lineEdit_csv_path->setText(SettingsData::inst().csv_path);
    ui.lineEdit_csv_interval->setText(SettingsData::inst().csv_interval);
    ui.lineEdit_db_host->setText(SettingsData::inst().db_host);
    ui.lineEdit_db_name->setText(SettingsData::inst().db_name);
    ui.lineEdit_db_user->setText(SettingsData::inst().db_user);
    ui.lineEdit_db_password->setText(SettingsData::inst().db_password);
}

void PreferencesDialog::close()
{
	done(0);
}

void PreferencesDialog::ok()
{
    SettingsData::inst().csv_path = ui.lineEdit_csv_path->text();
    SettingsData::inst().csv_interval = ui.lineEdit_csv_interval->text();
    SettingsData::inst().db_host = ui.lineEdit_db_host->text();
    SettingsData::inst().db_name = ui.lineEdit_db_name->text();
    SettingsData::inst().db_user = ui.lineEdit_db_user->text();
    SettingsData::inst().db_password = ui.lineEdit_db_password->text();

    /*
     * store settings
     */
    QSettings settings("csv2sql.ini", QSettings::IniFormat);
    settings.beginGroup("csv");
    settings.setValue("path", SettingsData::inst().csv_path);
    settings.setValue("interval", SettingsData::inst().csv_interval);
    settings.endGroup();

    settings.beginGroup("db");
    settings.setValue("host", SettingsData::inst().db_host);
    settings.setValue("name", SettingsData::inst().db_name);
    settings.setValue("user", SettingsData::inst().db_user);
    settings.setValue("password", SettingsData::inst().db_password);
    settings.endGroup();

    done(0);
}
