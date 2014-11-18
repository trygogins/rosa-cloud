#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QHash>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::MainWindow *ui;
    bool *activated;
    int cur_index;
    QHash<QString, QString>* serviceHosts;

    void changeState(bool state);
};

#endif // MAINWINDOW_H
