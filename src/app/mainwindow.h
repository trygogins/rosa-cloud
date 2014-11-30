#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QHash>
#include <QJsonObject>
#include "provider.h"

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
    void showAbout();
    void openFolder(QString path);

private:
    void fillProviderModel();
    bool readConfig();
    void createMenu();
    void addItem(int index);

    Ui::MainWindow *ui;
    AddProviderDialog *m_addProviderDialog;
    //ProviderModel *m_providerModel;
//    ActiveProviderModel *m_activeProviderModel;
    QJsonObject m_config;

    QList<Provider*> m_providers;
};

#endif // MAINWINDOW_H
