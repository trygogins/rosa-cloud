#include "addproviderdialog.h"
#include "ui_addproviderdialog.h"
#include "authdialog.h"

AddProviderDialog::AddProviderDialog(ProviderModel *providerModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_providerModel(providerModel)
{
    ui->setupUi(this);
    ui->providerView->setModel(providerModel);

    m_authDialog = new AuthDialog(this);

    connect(ui->providerView, SIGNAL(doubleClicked(QModelIndex)),
        m_authDialog, SLOT(open(QModelIndex)));

}

AddProviderDialog::~AddProviderDialog()
{
    delete ui;
}
