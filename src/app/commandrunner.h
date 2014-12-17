#ifndef COMMANDRUNNER_H
#define COMMANDRUNNER_H
#include <QStringList>
#include <QProcess>
#include <QObject>

class CommandRunner : public QObject
{
    Q_OBJECT

public:
    CommandRunner();

    void runCommand(QString command, QStringList arguments);

public slots:
    void readyReadStandardOutput();
    void readyReadStandardError();
    void finished(int);
    void stateChanged(QProcess::ProcessState);

private:
    QProcess* process;
};
#endif // COMMANDRUNNER_H
