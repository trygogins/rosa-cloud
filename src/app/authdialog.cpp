#include "authdialog.h"
#include "ui_authdialog.h"
#include <QMessageBox>
#include <QProcess>
#include <QInputDialog>
#include <QDir>
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

void AuthDialog::openAuthDialog(QObject *o_provider)
{
    Provider *provider = dynamic_cast<Provider*>(o_provider);
    this->provider = provider;
    setWindowTitle(tr("Login to %1").arg(provider->name()));
    ui->loginEdit->setText("");
    ui->passwordEdit->setText("");

    if (!isVisible())
        show();

    if (provider->isActive()) {
        ui->pushButton_2->setDisabled(false);
    } else {
        ui->pushButton_2->setDisabled(true);
    }
}

void AuthDialog::on_pushButton_clicked()
{
    QString name = provider->name();
    //url for egnyte
    QString egn;
    if (name == "egnyte") {
        bool ok;
        egn = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("URL:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
        if (ok && !egn.isEmpty()) {
                 //action
        }
    }
    QUrl url = provider->url();
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();
    QString username = qgetenv("USER");
    QString mountPoint = "/home/" + username + "/" + name + "_folder";

    QString fstabCredentials = url.toString() + " " + mountPoint + " davfs user,rw,noauto 0 0";
    QString davfsCredentials = url.toString() + " " + login + " " + password;

    CommandRunner runner;
    runner.runCommand("sh", QStringList() << "-c" << "echo '" + fstabCredentials + "' | sudo tee -a /etc/fstab");
    runner.runCommand("sh", QStringList() << "-c" << "echo '" + davfsCredentials + "' | tee -a $HOME/.davfs2/secrets");

    // mount
    runner.runCommand("mkdir", QStringList() << mountPoint);
    runner.runCommand("sudo mount", QStringList() << url.toString());

    //message for ui to change
    provider->setToken(QString("token!!"));

    this->close();
}

void AuthDialog::on_pushButton_2_clicked()
{
    //unmount
}
