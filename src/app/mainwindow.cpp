#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authdialog.h"
#include "commandrunner.h"
#include "spinbox.h"
#include "utils.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QDesktopServices>
#include <QInputDialog>

#include <QSignalMapper>

#include <QMessageBox>
#include <QMenuBar>
#include "QProcess"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::postInit() {
    if (sudoPassword.isNull()) {
        sudoPassword = askRoot();
    }
    authDialog = new AuthDialog(sudoPassword, this);
    sb = new Spinbox();
    if (readConfig()) {
        fillProviderModel();
    }
    checkInstalled();
}

void MainWindow::fillProviderModel()
{
    QJsonArray providers = m_config["providers"].toArray();
    for (QJsonArray::const_iterator it = providers.constBegin(); it != providers.constEnd(); ++it) {
        Provider *prd;
        QJsonObject provider = (*it).toObject();
        QString name = provider.value("name").toString();
        QString title = provider.value("title").toString();
        QString url = provider.value("url").toString();
        QJsonValue hasClient = provider.value("hasClient");
        if (!hasClient.isNull()) {
            prd = new Provider(name, title, url, hasClient.toBool());
            prd->setFolder(provider.value("folder").toString());
        } else {
            prd = new Provider(name, title, url);
        }
        m_providers.insert(name, prd);
        addItem(m_providers[name]);
    }
}

void MainWindow::checkInstalled() {
    QString username = qgetenv("USER");
    QFile config("/home/" + username + "/.rosa-cloud");
    if (config.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&config);
        QString providerName;
        while (!(providerName = stream.readLine()).isNull()) {
            QStringList info = providerName.split(" ");
            if (m_providers[info.at(0)]) {
                m_providers[info.at(0)]->setInstalled(true);
                if (info.at(1) == "1") {
                    m_providers[info.at(0)]->setMount(true);
                }
            }
        }
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

void MainWindow::changeWidget(QWidget *widget)
{
    QPalette pal = widget->palette();
    bool isDeactivated = pal.color(QPalette::Base) == ACTIVATED_COLOR;
    int color = isDeactivated ? DEACTIVATED_COLOR : ACTIVATED_COLOR;
    pal.setColor(QPalette::Base, color);
    QPushButton* connButton = widget->findChild<QPushButton*>("conn");
    connButton->setText(isDeactivated ? "Установить" : "Настройки");
    QPushButton *openButton = widget->findChild<QPushButton*>("open");
    openButton->setDisabled(isDeactivated ? true : false);
    QLabel *name = widget->findChild<QLabel*>("name");
    Provider *provider = m_providers[name->text()];
    if (!isDeactivated && provider->hasClient()) {
        connButton->setText("Открыть");
        openButton->setDisabled(true);
    }
    widget->setPalette(pal);
}

QFrame* MainWindow::createWidget(Provider *provider, QHBoxLayout *hLayout)
{
    QFrame *widget = new QFrame();
    widget->setAutoFillBackground(true);
    QPalette pal = widget->palette();
    pal.setColor(QPalette::Base, DEACTIVATED_COLOR);
    widget->setPalette(pal);
    widget->setLayout(hLayout);
    widget->setFrameShape(QFrame::Box);
    widget->setLineWidth(1);
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(provider, SIGNAL(mount()), signalMapper, SLOT(map()));
    signalMapper->setMapping(provider, widget);
    connect(signalMapper, SIGNAL(mapped(QWidget*)), this, SLOT(changeWidget(QWidget*)));

    return widget;
}

QPushButton* MainWindow::createSettingsButton(Provider *provider)
{
    QPushButton *connButton = new QPushButton(tr("Установить"));
    connButton->setObjectName("conn");
    if (provider->hasClient()) {
        if (provider->name() == "dropbox") {
            connect(connButton, SIGNAL(clicked()), this, SLOT(installDropbox()));
        }
        if (provider->name() == "spideroak") {
            connect(connButton, SIGNAL(clicked()), this, SLOT(installSpiderOak()));
        }
    } else {
        QSignalMapper *signalMapper = new QSignalMapper(this);
        connect(connButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(connButton, provider);
        connect(signalMapper, SIGNAL(mapped(QObject*)), authDialog, SLOT(openAuthDialog(QObject*)));

    }
    return connButton;
}

QPushButton* MainWindow::createOpenButton(const QString &path)
{
    QPushButton *openButton = new QPushButton(tr("Открыть папку"));
    openButton->setObjectName("open");
    openButton->setDisabled(true);
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(openButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(openButton, path);
    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(openFolder(QString)));

    return openButton;
}

void MainWindow::addItem(Provider* provider)
{
    QListWidgetItem *item = new QListWidgetItem();
    ui->providerView->addItem(item);

    QPushButton *settingsButton = createSettingsButton(provider);

    QString path;
    if (provider->hasClient()) {
        path = "/home/" + qgetenv("USER") + "/" + provider->folder();
    } else {
        path = "/home/" + qgetenv("USER") + "/" + provider->name() + "_folder";
    }
    QPushButton *openButton = createOpenButton(path);

    QLabel *label = new QLabel(provider->title());
    label->setStyleSheet("font: 18pt;");
    QLabel *label2 = new QLabel(provider->name());
    label2->setVisible(false);
    label2->setObjectName("name");

    QVBoxLayout *vLayout= new QVBoxLayout();
    vLayout->addWidget(settingsButton);
    vLayout->addWidget(openButton);
    QHBoxLayout *hLayout= new QHBoxLayout();
    hLayout->addWidget(label);
    hLayout->addWidget(label2);
    hLayout->addLayout(vLayout);

    QFrame *widget = createWidget(provider, hLayout);

    item->setSizeHint(widget->sizeHint());
    ui->providerView->setItemWidget(item, widget);
}

void MainWindow::executeCommand(const QString& command, const QStringList& args)
{
    CommandRunner *runner = new CommandRunner();
    runner->runCommand(command, args);
}

void MainWindow::installDropbox()
{
    Provider* provider = m_providers["dropbox"];
    CommandRunner runner;
    if (!(provider->isActive())) {
        runner.runCommand("urpmi", QStringList() << "kfilebox");
        provider->setInstalled(true);
        provider->setMount(true);
        markClientMounted(provider->name());
    }

    runner.runCommandDetached("kfilebox");
}

void MainWindow::installSpiderOak()
{
    Provider* provider = m_providers["spideroak"];
    CommandRunner* runner = new CommandRunner(true);
    if (!(provider->isActive())) {
        sb->show();
        QStringList arguments;
        arguments << "https://spideroak.com/directdownload?platform=fedora&arch=x86_64" << "-O" << "spideroak.rpm";
        connect(runner, SIGNAL(complete(int)), this, SLOT(spiderDownloaded(int)));
        runner->runCommand("wget", arguments);
    } else {
        runner->runCommandDetached("SpiderOak");
    }
}

void MainWindow::spiderDownloaded(int response)
{
    if (response != 0) {
        QMessageBox::critical(this, tr("Ошибка"), "Ошибка при загрузке SpiderOak!", QMessageBox::Ok);
        sb->close();
    } else {
        CommandRunner *runner = new CommandRunner(true);
        connect(runner, SIGNAL(complete(int)), this, SLOT(spiderInstalled(int)));
        runner->runCommand("urpmi", QStringList() << "--force" << "spideroak.rpm");
    }
}

void MainWindow::spiderInstalled(int response)
{
    if (response != 0) {
        QMessageBox::critical(this, tr("Ошибка"), "Ошибка при установке SpiderOak!", QMessageBox::Ok);
        sb->close();
    } else {
        m_providers["spideroak"]->setInstalled(true);
        m_providers["spideroak"]->setMount(true);
        markClientMounted("spideroak");
        sb->close();
        CommandRunner *runner = new CommandRunner();
        runner->runCommandDetached("SpiderOak");
    }
}

QString MainWindow::askRoot() {
    bool ok;
    int count = 0;
    while (true) {
        QString res = QInputDialog::getText(this, tr("Введите Root пароль"),
                                            tr("Пароль:"), QLineEdit::Password,
                                             "", &ok);
        if (!ok) {
            this->close();
            return res;
        }
        if (correct(res)) {
            return res;
        }
        if (++count == 3) {
            QMessageBox::critical(this, tr("Ошибка"), "Вы ввели неверный пароль трижды!", QMessageBox::Ok);
            QApplication::quit();
        }
    }
}
