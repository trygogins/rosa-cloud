#include "authdialog.h"
#include "ui_authdialog.h"
#include <QMessageBox>
#include <QProcess>
#include <QInputDialog>
#include <QDir>
#include "commandrunner.h"
#include "spinbox.h"
#include "utils.h"

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
    setWindowTitle(tr("Авторизация в %1").arg(provider->name()));
    ui->loginEdit->setText("");
    ui->passwordEdit->setText("");

    if (provider->isActive() && !provider->isMount()) {
        CommandRunner runner;
        QString username = qgetenv("USER");
        QString mountPoint = "/home/" + username + "/" + provider->name() + "_folder";
        runner.runCommandAsRoot(sudoPassword, "mount -t davfs2 -o rw " + provider->url().toString() + " " + mountPoint);
        markMountInFile(provider->name(), "1");
        provider->setMount(true);
        return;
    }

    if (!isVisible())
        show();

    if (provider->isMount()) {
        ui->pushButton_2->setDisabled(false);
        ui->pushButton->setDisabled(true);

        ui->loginEdit->setDisabled(true);
        ui->passwordEdit->setDisabled(true);
    } else {
        ui->pushButton_2->setDisabled(true);
        ui->pushButton->setDisabled(false);

        ui->loginEdit->setDisabled(false);
        ui->passwordEdit->setDisabled(false);
    }
}

void AuthDialog::on_pushButton_clicked()
{
    QString name = provider->name();
    //url for egnyte
    QString egn;
    if (name == "egnyte") {
        bool ok;
        egn = QInputDialog::getText(this, tr("Введите имя хранилища"),
                                                 tr("Имя:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
        if (!ok || egn.isEmpty()) {
            QMessageBox::critical(this, tr("Ошибка"), "Ошибка при установке Egnyte!", QMessageBox::Ok);
            return;
        }
    }
    Spinbox *sp = new Spinbox();
    sp->show();

    QString url = provider->url().toString();
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();
    QString username = qgetenv("USER");
    QString mountPoint = "/home/" + username + "/" + name + "_folder";

    if (name == "egnyte") {
        url = url.replace("username", egn);
    }

    CommandRunner runner;
    QString davfsCredentials = url + " " + login + " " + password;


    runner.runCommandAsRoot(sudoPassword,
                            "echo '" + davfsCredentials + "' >> /etc/davfs2/secrets");
    runner.runCommand("mkdir", QStringList() << mountPoint);

    // mount
    int res = runner.runCommandAsRoot(sudoPassword, "mount -t davfs2 -o rw " + url + " " + mountPoint);
    if (res != 0) {
        sp->close();
        QMessageBox::critical(this, tr("Ошибка"), "Ошибка при авторизации в " + name + "!", QMessageBox::Ok);
        markClientUnmounted(sudoPassword, name);
        CommandRunner runner;
        runner.runCommandAsRoot(sudoPassword, QString("sed -i") +
                           " '/" + davfsCredentials.replace(QString("/"), QString("\\/")) + "/d' " +
                           " /etc/davfs2/secrets");
        runner.runCommand("rmdir", QStringList() << mountPoint);
        return;
    }
    //message for ui to change
    markClientMounted(name);
    provider->setInstalled(true);
    provider->setMount(true);

    sp->close();
    this->close();
}

void AuthDialog::on_pushButton_2_clicked()
{
    markClientUnmounted(sudoPassword, provider->name());
    provider->setMount(false);
    this->close();
}
