#include <QPushButton>

#include "about.h"


AboutDialog::AboutDialog()
{
    /* build ui */
    ui.setupUi(this);
    ui.closeButtonBox->addButton(new QPushButton("&Close", this),
        QDialogButtonBox::RejectRole);

    setWindowRole("csv2sql-about");
    setMinimumSize(400, 300);
    resize(400, 300);
    setWindowModality(Qt::WindowModal);

    connect(ui.closeButtonBox, SIGNAL(rejected()), this, SLOT(close()));
    ui.closeButtonBox->setFocus();

    ui.introduction->setText("CSV2SQL " APP_VERSION);

    ui.iconApp->setPixmap(QPixmap(":/images/logo"));

    /* Main Introduction */
    ui.infoLabel->setText(
            "CSV2SQL is CSV -> SQL inject, "
            "for Adidas system.\n"
            "This version of csv2sql was compiled at: " __DATE__" " __TIME__"\n"
            "Copyright (C) 2012 AAA");

    /* License */
    ui.licenseEdit->setText("AAA");

    /* People who helped */
    ui.thanksEdit->setText("");

    /* People who wrote the software */
    ui.authorsEdit->setText("");
}

void AboutDialog::close()
{
	done(0);
}

