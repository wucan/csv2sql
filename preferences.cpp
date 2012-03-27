#include <QPushButton>

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
}

void PreferencesDialog::close()
{
	done(0);
}

void PreferencesDialog::ok()
{
    done(0);
}
