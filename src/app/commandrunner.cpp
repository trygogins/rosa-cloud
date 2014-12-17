#include "commandrunner.h"
#include <QDebug>

void CommandRunner::runCommand(const QString &command, const QStringList &arguments) {
    process = new QProcess();

    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
    connect(process, SIGNAL(finished(int)), this, SLOT(finished(int)));
    connect(process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(stateChanged(QProcess::ProcessState)));
    connect(process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(error(QProcess::ProcessError)));
    process->start(command, arguments);
}

void CommandRunner::readyReadStandardOutput()
{
    qDebug() << "[" << process->program() << "]" << "standard output" << process->readAllStandardOutput();
}

void CommandRunner::readyReadStandardError()
{
    qDebug() << "[" << process->program() << "]" << "standard error: " << process->readAllStandardError();
}

void CommandRunner::finished(int res)
{
    qDebug() << "[" << process->program() << "]" << "Finished: " << res;
}

void CommandRunner::stateChanged(QProcess::ProcessState newState)
{
    qDebug() << "[" << process->program() << "]" << "New state" << newState;
}

void CommandRunner::error(QProcess::ProcessError error)
{
    qDebug() << "[" << process->program() << "]" << "Error: " << error;
    qDebug() << "[" << process->program() << "]" << "Error string: " << process->errorString();
}
