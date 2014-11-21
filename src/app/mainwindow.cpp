#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authdialog.h"
#include "providermodel.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_providerModel = new ProviderModel(this);
    ui->providerView->setModel(m_providerModel);
    if (readConfig())
        fillProviderModel();

    m_authDialog = new AuthDialog(this);

    connect(ui->providerView, SIGNAL(doubleClicked(QModelIndex)),
            m_authDialog, SLOT(open(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
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

