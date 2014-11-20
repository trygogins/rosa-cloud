#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QHash>

namespace Ui {
class MainWindow;
}

class ProviderModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void fillProviderModel();

    Ui::MainWindow *ui;
    ProviderModel *m_providerModel;
};

#endif // MAINWINDOW_H
