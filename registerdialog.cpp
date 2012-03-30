#include <QtGui>

#include "registerdialog.h"
#include "preferences.h"


RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Register the Software"));
    setMinimumWidth(400);

    QGridLayout *root_grid_layout = new QGridLayout();

    QGridLayout *grid_layout = new QGridLayout();
    QGridLayout *buttons_grid_layout = new QGridLayout();
    /* SN(Serial Number) */
    QLabel *sn_label = new QLabel(tr("Serial Number"), this);
    sn_lineedit = new QLineEdit(this);
    grid_layout->addWidget(sn_label, 0, 0);
    grid_layout->addWidget(sn_lineedit, 0, 1);
    /* RN(Register Number) */
    QLabel *rn_label = new QLabel(tr("Register Number"), this);
    rn_lineedit = new QLineEdit(this);

    grid_layout->addWidget(rn_label, 1, 0);
    grid_layout->addWidget(rn_lineedit, 1, 1);
    /* Ok and Cancel buttons */
    reg_label = new QLabel();
    reg_label->setPixmap(QPixmap(isRegistered() ? ":/images/unlock" : ":/images/lock"));
    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QPushButton *ok_pushbutton = new QPushButton(tr("Register"), this);
    QPushButton *cancel_pushbutton = new QPushButton(tr("Close"), this);
    buttons_grid_layout->addWidget(reg_label, 0, 0);
    buttons_grid_layout->addItem(spacer, 0, 1);
    buttons_grid_layout->addWidget(ok_pushbutton, 0,2);
    buttons_grid_layout->addWidget(cancel_pushbutton, 0, 3);
    connect(ok_pushbutton, SIGNAL(clicked()), this, SLOT(doRegister()));
    connect(cancel_pushbutton, SIGNAL(clicked()), this, SLOT(close()));

    root_grid_layout->addItem(grid_layout, 0, 0);
    root_grid_layout->addItem(buttons_grid_layout, 1, 0);
    setLayout(root_grid_layout);

    sn_lineedit->setText(SettingsData::inst().sn);
    rn_lineedit->setText(SettingsData::inst().rn);
}

void RegisterDialog::doRegister()
{
    SettingsData::inst().sn = sn_lineedit->text();
    SettingsData::inst().rn = rn_lineedit->text();

    QSettings settings("csv2sql.ini", QSettings::IniFormat);
    settings.beginGroup("reg");
    settings.setValue("sn", SettingsData::inst().sn);
    settings.setValue("rn", SettingsData::inst().rn);
    settings.endGroup();

    reg_label->setPixmap(QPixmap(isRegistered() ? ":/images/unlock" : ":/images/lock"));
}

bool RegisterDialog::isRegistered()
{
    /* FIXME */
    return (SettingsData::inst().sn == SettingsData::inst().rn);
}
