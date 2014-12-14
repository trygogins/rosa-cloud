#include "authdialog.h"
#include "ui_authdialog.h"
#include "commandrunner.h"
#include <QMessageBox>
#include <QProcess>
#include <QDebug>

#include <QFile>
#include <QDir>
#include <QTextStream>

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

    if (!isVisible())
        show();    

    //there will be the save and connect methods
}

void AuthDialog::on_buttonBox_accepted()
{
    QString name = provider->name();
    QUrl url = provider->url();
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();
    QString username = qgetenv("USER");
    QString mountPoint = "/home/" + username + "/" + name + "_folder";

    CommandRunner runner;
    QFile config("/home/" + username + "/.rosa-cloud");
    if (!isProviderInstalled(&config, name)) {
        if (config.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream stream(&config);
            stream << name << endl;
            config.close();
        }

        QString fstabCredentials = url.toString() + " " + mountPoint + " davfs user,rw,noauto 0 0";
        QString davfsCredentials = url.toString() + " " + login + " " + password;

        runner.runCommand("sh", QStringList() << "-c" << "echo '" + fstabCredentials + "' | gksudo tee -a /etc/fstab");
        runner.runCommand("sh", QStringList() << "-c" << "echo '" + davfsCredentials + "' | tee -a $HOME/.davfs2/secrets");
        provider->setToken(QString("token!!"));

        // mount
        runner.runCommand("mkdir", QStringList() << mountPoint);
    }

    runner.runCommand("mount", QStringList() << url.toString());
}

void AuthDialog::on_buttonBox_rejected()
{

}

bool AuthDialog::isProviderInstalled(QFile *configFile, QString name)
{
    if (configFile->open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(configFile);
        QString providerName;
        do {
            providerName = stream.readLine();
            if (providerName.compare(name) == 0) {
                return true;
            }
        } while (!providerName.isNull());
    }

    return false;
}
