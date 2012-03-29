#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>


class QLabel;
class QLineEdit;

class RegisterDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RegisterDialog(QWidget *parent = 0);

    static bool isRegistered();

signals:

public slots:
    void doRegister();

private:
    QLineEdit *sn_lineedit;
    QLineEdit *rn_lineedit;
    QLabel *reg_label;
};

#endif // REGISTERDIALOG_H
