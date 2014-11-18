#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    activated = new bool[(int)ui->listWidget->count()];

    // initialize the map
    serviceHosts = new QHash<QString, QString>();
    serviceHosts->insert("4Shared", "https://webdav.4shared.com/");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    ui->label_2->setText(ui->listWidget->item(currentRow)->text());
    cur_index = currentRow;
    changeState(!activated[cur_index]);
}

void MainWindow::on_pushButton_clicked()
{
      changeState(activated[cur_index]);
      AuthDialog* d = new AuthDialog(this, serviceHosts->value("4Shared"));
      d->show();
}

void MainWindow::changeState(bool state) {
    if (state) {
        ui->label_4->setText("<html><head/><body><p><span style=\" color:#ff0000;\">Не активен</span></p></body></html>");
        ui->pushButton_2->setEnabled(false);
        activated[cur_index] = false;

    } else {
       ui->label_4->setText("<html><head/><body><p><span style=\" color:#00ff00;\">Aктивен</span></p></body></html>");
       ui->pushButton_2->setEnabled(true);
       activated[cur_index] = true;
    }
}

void MainWindow::on_pushButton_2_clicked()
{

}
