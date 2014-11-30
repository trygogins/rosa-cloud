#include "commandrunner.h"
#include <QDebug>

CommandRunner::CommandRunner() //: QObject(parent)
{   
}


void CommandRunner::runCommand(QString command, QStringList arguments) {
    QProcess* process = new QProcess();
    process->start(command, arguments);
    //QObject::connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput(process)));
    //connect(&process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError(process)));

//    while (!process.waitForFinished());

  //  return process.exitCode() == 0;
}

//void CommandRunner::readyReadStandardOutput(QProcess process)
//{
//    qDebug() << process.readAllStandardOutput();
//}

//void CommandRunner::readyReadStandardError(QProcess process)
//{
//    qDebug() << process.readAllStandardError();
//}
