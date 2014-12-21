#ifndef COMMANDRUNNER_H
#define COMMANDRUNNER_H
#include <QStringList>
#include <QProcess>
#include <QObject>

class CommandRunner : public QObject
{
    Q_OBJECT

public:
    explicit CommandRunner(bool async = false) : QObject(), async(async) {}

    int runCommand(const QString &command, const QStringList &arguments);
    int runCommandAsRoot(const QString& sudoPassword, const QString& command);
    void runCommandDetached(const QString& command);

    QString* getLastOutput() { return lastOutput; }

public slots:
    void readyReadStandardOutput();
    void readyReadStandardError();
    void finished(int);
    void stateChanged(QProcess::ProcessState);
    void error(QProcess::ProcessError);

signals:
    void complete(int responseCode);

private:
    QProcess* process;
    bool async;
    QString* lastOutput;

};
#endif // COMMANDRUNNER_H
