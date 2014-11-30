#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authdialog.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QDesktopServices>

#include <QSignalMapper>

#include <QMessageBox>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (readConfig()) {
        fillProviderModel();
    }
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
        Provider *prd = new Provider(name, title, url);
        m_providers.push_back(prd);
        addItem(m_providers.size() - 1);
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

void MainWindow::openFolder(QString path) {
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void MainWindow::addItem(int index)
{
    QListWidgetItem *item = new QListWidgetItem();
    ui->providerView->addItem(item);
    QPushButton *settingsbutton = new QPushButton("Настройки");

    AuthDialog *authDialog = new AuthDialog(this);
    QSignalMapper *signalMapper = new QSignalMapper();
    connect(settingsbutton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(settingsbutton, m_providers[index]);
    connect(signalMapper, SIGNAL(mapped(QObject*)), authDialog, SLOT(open(QObject*)));

    QPushButton *openbutton = new QPushButton("Открыть папку");
    QString path = "/";
    QSignalMapper *signalMapper2 = new QSignalMapper();
    connect(openbutton, SIGNAL(clicked()), signalMapper2, SLOT(map()));
    signalMapper2->setMapping(openbutton, path);
    connect(signalMapper2, SIGNAL(mapped(QString)), this, SLOT(openFolder(QString)));

    QLabel *label = new QLabel(m_providers[index]->title());
    label->setStyleSheet("font: 18pt;");
    QVBoxLayout *vLayout= new QVBoxLayout();
    vLayout->addWidget(settingsbutton);
    vLayout->addWidget(openbutton);
    QHBoxLayout *hLayout= new QHBoxLayout();
    hLayout->addWidget(label);
    hLayout->addLayout(vLayout);
    QWidget *widget = new QWidget();
    widget->setAutoFillBackground(true);

    QPalette pal = widget->palette();
    const int GREEN = 0x95FF6B;
    pal.setColor(QPalette::Base, GREEN);
    widget->setPalette(pal);
    widget->setLayout(hLayout);
    item->setSizeHint(widget->sizeHint());
    ui->providerView->setItemWidget(item, widget);
}

