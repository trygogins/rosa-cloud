#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QHash>
#include <QJsonObject>
#include <QHBoxLayout>
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
    void openFolder(QString path);
    void activateWidget(QWidget*);

private:
    static const int ACTIVATED_COLOR = 0x95FF6B;
    static const int DEACTIVATED_COLOR = 0xFF0000;

    void fillProviderModel();
    bool readConfig();
    void addItem(int index);

    QWidget *createWidget(Provider*, QHBoxLayout*);

    Ui::MainWindow *ui;
    AddProviderDialog *m_addProviderDialog;
    QJsonObject m_config;

    QList<Provider*> m_providers;
};

#endif // MAINWINDOW_H
