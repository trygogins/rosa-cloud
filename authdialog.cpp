#include "authdialog.h"
#include "ui_authdialog.h"
#include <QMessageBox>
#include <QProcess>

AuthDialog::AuthDialog(QWidget *parent, QString host) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    this->host = host;
    ui->setupUi(this);
}

AuthDialog::~AuthDialog()
{
    delete ui;
}

void AuthDialog::on_buttonBox_accepted()
{
    // mount
    QProcess* proc = new QProcess();
    proc->start("sudo mount " + host);
}

void AuthDialog::on_buttonBox_rejected()
{
    // unmount
    QProcess* proc = new QProcess();
    proc->start("sudo umount " + host);
}
