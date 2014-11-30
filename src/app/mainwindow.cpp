#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "providermodel.h"
#include "activeprovidermodel.h"
#include "addproviderdialog.h"
#include "commandrunner.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

#include <QMessageBox>
#include <QMenuBar>
#include "QProcess"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_providerModel = new ProviderModel(this);
    m_activeProviderModel = new ActiveProviderModel(this);

    if (readConfig()) {
        fillProviderModel();
        m_providerModel->load();
        m_activeProviderModel->setSourceModel(m_providerModel);
    }

    ui->providerView->setModel(m_activeProviderModel);
    m_addProviderDialog = new AddProviderDialog(m_providerModel, this);

    connect(ui->addButton, SIGNAL(clicked()), m_addProviderDialog, SLOT(show()));
    connect(ui->pushButton1, SIGNAL(clicked()), this, SLOT(installDropbox()));
    connect(ui->pushButton2, SIGNAL(clicked()), this, SLOT(installSpiderOak()));
    createMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, tr("About"), qApp->applicationDisplayName());
}

void MainWindow::fillProviderModel()
{
    QJsonArray providers = m_config["providers"].toArray();
    for (QJsonArray::const_iterator it = providers.constBegin(); it != providers.constEnd(); ++it) {
        QJsonObject provider = (*it).toObject();
        QString name = provider.value("name").toString();
        QString title = provider.value("title").toString();
        QString url = provider.value("url").toString();
        m_providerModel->addProvider(name, title, url);
    }
}

bool MainWindow::readConfig()
{
    QFile file(":/config.js");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Can't read config file";
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    m_config = doc.object();
    return !m_config.isEmpty();
}

void MainWindow::createMenu()
{
    QMenu *aboutMenu = menuBar()->addMenu("About");
    aboutMenu->addAction("About", this, SLOT(showAbout()));
    aboutMenu->addAction("About Qt", qApp, SLOT(aboutQt()));
}

void MainWindow::installDropbox()
{
    CommandRunner runner;
    QStringList arguments;
    runner.runCommand("urpmi kfilebox && kfilebox", arguments);
}

void MainWindow::installSpiderOak()
{
    CommandRunner runner;
    QStringList arguments;
    arguments << "https://spideroak.com/directdownload?platform=fedora&arch=x86_64" << "-O" << "spideroak.rpm";
    runner.runCommand("wget", arguments); //  && urpmi spideroak.rpm && SpiderOak", arguments);
}
