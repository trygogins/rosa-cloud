#include "authdialog.h"
#include "ui_authdialog.h"
#include "providermodel.h"
#include <QMessageBox>
#include <QProcess>
#include "commandrunner.h"

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
    name = index.data(ProviderModel::Title).toString();
    m_url = index.data(ProviderModel::Url).toUrl();

    setWindowTitle(tr("Login to %1").arg(name));

    if (!isVisible())
        show();
}

void AuthDialog::on_buttonBox_accepted()
{
    QString login = "";
    QString password = "";
    QString username = qgetenv("USER");
    QString mountPoint = "/home/" + username + "/" + name + "_folder";

    QString fstabCredentials = m_url.toString() + " " + mountPoint + " davfs user,rw,noauto 0 0";
    QString davfsCredentials = m_url.toString() + " " + login + " " + password;

    CommandRunner runner;
    runner.runCommand("sh", QStringList() << "-c" << "echo '" + fstabCredentials + "' | sudo tee -a /etc/fstab");
    runner.runCommand("sh", QStringList() << "-c" << "echo '" + davfsCredentials + "' | tee -a $HOME/.davfs2/secrets");
    // mount
    runner.runCommand("mkdir", QStringList() << mountPoint);
    runner.runCommand("mount", QStringList() << m_url.toString());
}

void AuthDialog::on_buttonBox_rejected()
{
    // unmount
    QProcess* proc = new QProcess();
    proc->start("umount " + m_url.toString());
}
