#include "commandrunner.h"
#include <QDebug>

CommandRunner::CommandRunner() //: QObject(parent)
{   
}


void CommandRunner::runCommand(QString command, QStringList arguments) {
    QProcess* process = new QProcess();
    process->execute(command, arguments);
}

void CommandRunner::runCommandAsRoot(QString sudoPassword, QString command) {
    QString com = "echo '" + sudoPassword + "' | sudo -kS sh -c \"" + command + "\"";
    qDebug() << com;
    runCommand("sh", QStringList() << "-c" << com);
}
