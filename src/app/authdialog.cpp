#include "authdialog.h"
#include "ui_authdialog.h"
#include "providermodel.h"
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

void AuthDialog::open(const QModelIndex &index)
{
    QString name = index.data(ProviderModel::Title).toString();
    m_url = index.data(ProviderModel::Url).toUrl();

    setWindowTitle(tr("Login to %1").arg(name));

    if (!isVisible())
        show();
}

void AuthDialog::on_buttonBox_accepted()
{
    // mount
    QProcess* proc = new QProcess();
    proc->start("sudo mount " + m_url.toString());
}

void AuthDialog::on_buttonBox_rejected()
{
    // unmount
    QProcess* proc = new QProcess();
    proc->start("sudo umount " + m_url.toString());
}
