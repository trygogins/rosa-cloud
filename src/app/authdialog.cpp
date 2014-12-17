#include "authdialog.h"
#include "ui_authdialog.h"
#include <QMessageBox>
#include <QProcess>
#include <QInputDialog>
#include <QDir>
#include "commandrunner.h"
#include "spinbox.h"

#include <QDebug>

#include <QFile>
#include <QTextStream>

AuthDialog::AuthDialog(QString sudoPassword, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    this->sudoPassword = sudoPassword;
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
        egn = QInputDialog::getText(this, tr("Введите путь до хранилища"),
                                                 tr("URL:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
        if (!ok || egn.isEmpty()) {
                 //action if error
        }
    }
    Spinbox *sp = new Spinbox();
    sp->show();

    QUrl url = provider->url();
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();
    QString username = qgetenv("USER");
    QString mountPoint = "/home/" + username + "/" + name + "_folder";

    CommandRunner runner;
    QFile config("/home/" + username + "/.rosa-cloud");
    if (!(provider->isActive())) {
        if (config.open(QFile::WriteOnly | QFile::Append | QFile::Text)) {
            QTextStream stream(&config);
            stream << name << endl;
            config.close();
        }

        QString davfsCredentials = url.toString() + " " + login + " " + password;

        runner.runCommandAsRoot(sudoPassword,
                                "echo '" + davfsCredentials + "' >> /etc/davfs2/secrets");
        runner.runCommand("mkdir", QStringList() << mountPoint);
    }
    // mount
    runner.runCommandAsRoot(sudoPassword, "mount -t davfs2 -o rw " + url.toString() + " " + mountPoint);
    //message for ui to change
    provider->setActivated(true);

    sp->close();
    this->close();
}

void AuthDialog::on_pushButton_2_clicked()
{
    provider->setActivated(false);
    //unmount
    QString name = provider->name();
    QString username = qgetenv("USER");
    QString mountPoint = "/home/" + username + "/" + name + "_folder";
    CommandRunner runner;
    runner.runCommandAsRoot(sudoPassword, "umount " + mountPoint);

    this->close();
}
