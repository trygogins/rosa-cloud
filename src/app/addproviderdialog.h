#ifndef ADDPROVIDERDIALOG_H
#define ADDPROVIDERDIALOG_H

#include <QDialog>
#include "providermodel.h"

namespace Ui {
class Dialog;
}

class AuthDialog;

class AddProviderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddProviderDialog(ProviderModel *providerModel, QWidget *parent = 0);
    ~AddProviderDialog();

private:
    Ui::Dialog *ui;
    ProviderModel *m_providerModel;
    AuthDialog *m_authDialog;
};

#endif // ADDPROVIDERDIALOG_H
