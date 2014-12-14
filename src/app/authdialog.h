#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QUrl>

#include "provider.h"

namespace Ui {
class AuthDialog;
}

class AuthDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = 0);
    ~AuthDialog();

public slots:
    void openAuthDialog(QObject *o_provider);

private slots:
//    void on_buttonBox_accepted();

//    void on_buttonBox_rejected();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AuthDialog *ui;
    Provider *provider;
};

#endif // AUTHDIALOG_H
