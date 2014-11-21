#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QHash>
#include <QJsonObject>

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

private:
    void fillProviderModel();
    bool readConfig();

    Ui::MainWindow *ui;
    AddProviderDialog *m_addProviderDialog;

    ProviderModel *m_providerModel;
    ActiveProviderModel *m_activeProviderModel;
    QJsonObject m_config;
};

#endif // MAINWINDOW_H
