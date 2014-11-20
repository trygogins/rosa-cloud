#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authdialog.h"
#include "providermodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_providerModel = new ProviderModel(this);
    ui->providerView->setModel(m_providerModel);
    fillProviderModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillProviderModel()
{
    m_providerModel->addProvider("4Shared", QUrl("https://webdav.4shared.com/"));
    m_providerModel->addProvider("Dropbox", QUrl());
    m_providerModel->addProvider("Yandex.disk", QUrl());
}

