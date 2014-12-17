#include "spinbox.h"
#include "ui_spinbox.h"
#include <QLabel>
#include <QMovie>

Spinbox::Spinbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spinbox)
{
    ui->setupUi(this);
    ui->label->setText(tr("Загрузка может занять несколько минут, подождите"));
    QMovie* spinnerMovie = new QMovie(":/spinner.gif");
    QSize t2(50, 50);
    spinnerMovie->setScaledSize(t2);
    ui->label_2->setMovie(spinnerMovie);
    spinnerMovie->start();
}

Spinbox::~Spinbox()
{
    delete ui;
}
