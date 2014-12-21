#include "commandrunner.h"
#include <QDebug>

void CommandRunner::runCommand(const QString &command, const QStringList &arguments) {
    process = new QProcess();    
    if (async) {
        connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
        connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
        connect(process, SIGNAL(finished(int)), this, SLOT(finished(int)));
        connect(process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(stateChanged(QProcess::ProcessState)));
        connect(process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(error(QProcess::ProcessError)));
        process->start(command, arguments);
    } else {
        process->execute(command, arguments);
        lastOutput = new QString(process->readAllStandardOutput());
    }
}

void CommandRunner::runCommandAsRoot(const QString& sudoPassword, const QString& command) {
    QString com = "echo '" + sudoPassword + "' | sudo -kS sh -c \"" + command + "\"";
    qDebug() << com;
    runCommand("sh", QStringList() << "-c" << com);
}

void CommandRunner::runCommandDetached(const QString &command) {
    process = new QProcess();
    process->startDetached(command);
}

void CommandRunner::readyReadStandardOutput()
{
    QByteArray out = process->readAllStandardOutput();
    qDebug() << "[" << process->program() << "]" << "standard output" << out;
    lastOutput = new QString(out);
}

void CommandRunner::readyReadStandardError()
{
    qDebug() << "[" << process->program() << "]" << "standard error: " << process->readAllStandardError();
}

void CommandRunner::finished(int res)
{
    qDebug() << "[" << process->program() << "]" << "Finished: " << res;
    emit complete(res);
}

void CommandRunner::stateChanged(QProcess::ProcessState newState)
{
    qDebug() << "[" << process->program() << "]" << "New state" << newState;
}

void CommandRunner::error(QProcess::ProcessError error)
{
    qDebug() << "[" << process->program() << "]" << "Error: " << error;
    qDebug() << "[" << process->program() << "]" << "Error string: " << process->errorString();
    emit complete(- (error + 1) * 100); // used to identify errors (refactoring is welcome)
}

