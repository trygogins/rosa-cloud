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

void MainWindow::openFolder(QString path) {
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void MainWindow::activateWidget(QWidget *widget)
{
    QPalette pal = widget->palette();
    pal.setColor(QPalette::Base, ACTIVATED_COLOR);
    widget->setPalette(pal);
}

QWidget* MainWindow::createWidget(Provider *provider, QHBoxLayout *hLayout)
{
    QWidget *widget = new QWidget();
    widget->setAutoFillBackground(true);
    QPalette pal = widget->palette();
    pal.setColor(QPalette::Base, DEACTIVATED_COLOR);
    widget->setPalette(pal);
    widget->setLayout(hLayout);

    QSignalMapper *signalMapper = new QSignalMapper();
    connect(provider, SIGNAL(activated()), signalMapper, SLOT(map()));
    signalMapper->setMapping(provider, widget);
    connect(signalMapper, SIGNAL(mapped(QWidget*)), this, SLOT(activateWidget(QWidget*)));

    return widget;
}

void MainWindow::addItem(int index)
{
    Provider *provider = m_providers[index];

    QListWidgetItem *item = new QListWidgetItem();
    ui->providerView->addItem(item);
    QPushButton *settingsbutton = new QPushButton("Настройки");

    AuthDialog *authDialog = new AuthDialog(this);
    QSignalMapper *signalMapper = new QSignalMapper();
    connect(settingsbutton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(settingsbutton, provider);
    connect(signalMapper, SIGNAL(mapped(QObject*)), authDialog, SLOT(open(QObject*)));

    QPushButton *openbutton = new QPushButton("Открыть папку");
    QString path = "/";
    QSignalMapper *signalMapper2 = new QSignalMapper();
    connect(openbutton, SIGNAL(clicked()), signalMapper2, SLOT(map()));
    signalMapper2->setMapping(openbutton, path);
    connect(signalMapper2, SIGNAL(mapped(QString)), this, SLOT(openFolder(QString)));

    QLabel *label = new QLabel(provider->title());
    label->setStyleSheet("font: 18pt;");
    QVBoxLayout *vLayout= new QVBoxLayout();
    vLayout->addWidget(settingsbutton);
    vLayout->addWidget(openbutton);
    QHBoxLayout *hLayout= new QHBoxLayout();
    hLayout->addWidget(label);
    hLayout->addLayout(vLayout);

    QWidget *widget = createWidget(provider, hLayout);

    item->setSizeHint(widget->sizeHint());
    ui->providerView->setItemWidget(item, widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

