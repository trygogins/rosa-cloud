#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QHash>
#include <QJsonObject>
#include <QHBoxLayout>
#include <QPushButton>
#include "provider.h"
#include "authdialog.h"

namespace Ui {
class MainWindow;
}

class AddProviderDialog;
class ProviderModel;
class ActiveProviderModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openFolder(QString path);
    void changeWidget(QWidget*);
    void installDropbox();
    void installSpiderOak();

private:
    static const int ACTIVATED_COLOR = 0x95FF6B;
    static const int DEACTIVATED_COLOR = 0xFF917A;

    void fillProviderModel();
    bool readConfig();
    void addItem(Provider* provider);
    void checkInstalled();

    QFrame *createWidget(Provider*, QHBoxLayout*);
    QPushButton* createSettingsButton(Provider *);
    QPushButton* createOpenButton(const QString &);

    AuthDialog *authDialog;
    Ui::MainWindow *ui;
    AddProviderDialog *m_addProviderDialog;
    QJsonObject m_config;

    QMap<QString, Provider*> m_providers;
};

#endif // MAINWINDOW_H
