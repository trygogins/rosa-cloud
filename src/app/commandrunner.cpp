#include "commandrunner.h"
#include <QDebug>

CommandRunner::CommandRunner() //: QObject(parent)
{   
}


void CommandRunner::runCommand(QString command, QStringList arguments) {
    process = new QProcess();
   // process->execute(command, arguments);

    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
    process->start(command, arguments);
    while (!process->waitForFinished()) {
        qDebug() << ":(" << "\n";
    }

  //  return process.exitCode() == 0;
}

void CommandRunner::readyReadStandardOutput()
{
    qDebug() << process->readAllStandardOutput();
}

void CommandRunner::readyReadStandardError()
{
    qDebug() << process->readAllStandardError();
}
