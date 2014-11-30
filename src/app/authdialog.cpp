#include "authdialog.h"
#include "ui_authdialog.h"
#include <QMessageBox>
#include <QProcess>

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
}

AuthDialog::~AuthDialog()
{
    delete ui;
}

void AuthDialog::openAuthDialog(QObject *o_provider)
{
    Provider *provider = dynamic_cast<Provider*>(o_provider);
    this->provider = provider;
    m_url = provider->url();
    setWindowTitle(tr("Login to %1").arg(provider->name()));

    if (!isVisible())
        show();    

    //there will be the save and connect methods
}

void AuthDialog::on_buttonBox_accepted()
{
    // mount
    provider->setToken(QString("token!!"));
    QProcess* proc = new QProcess();
    proc->start("sudo mount " + m_url.toString());
}

void AuthDialog::on_buttonBox_rejected()
{
    // unmount
    QProcess* proc = new QProcess();
    proc->start("sudo umount " + m_url.toString());
}
