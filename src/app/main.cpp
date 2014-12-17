#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("RosaCloud");
    a.setApplicationName("rosa-cloud");
    a.setApplicationDisplayName("Rosa Cloud");
    MainWindow w;
    w.show();
    w.postInit();

    return a.exec();
}
