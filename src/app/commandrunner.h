#ifndef COMMANDRUNNER_H
#define COMMANDRUNNER_H
#include <QStringList>
#include <QProcess>
#include <QObject>

class CommandRunner : public QObject
{
    Q_OBJECT

public:
    explicit CommandRunner() : QObject() {}

    void runCommand(const QString &command, const QStringList &arguments);

public slots:
    void readyReadStandardOutput();
    void readyReadStandardError();
    void finished(int);
    void stateChanged(QProcess::ProcessState);
    void error(QProcess::ProcessError);

private:
    QProcess* process;
};
#endif // COMMANDRUNNER_H
