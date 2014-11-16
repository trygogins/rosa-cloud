#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    activated = new bool[ui->listWidget->size()];
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->label_2->setText(item->text());
    cur_index = ui->listWidget->row( item );
}

void MainWindow::on_pushButton_clicked()
{
    if (activated[cur_index]) {
       ui->label_4->setText("<html><head/><body><p><span style=\" color:#0000ff;\">Aктивен</span></p></body></html>");
       ui->pushButton_2->setEnabled(false);
       activated[cur_index] = true;
    } else {
       ui->label_4->setText("<html><head/><body><p><span style=\" color:#ff0000;\">Не активен</span></p></body></html>");
       ui->pushButton_2->setEnabled(false);
       activated[cur_index] = false;
    }
}
