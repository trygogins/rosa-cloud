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

    void runCommand(const QString &command, const QStringList &arguments);
    void runCommandAsRoot(const QString& sudoPassword, const QString& command);

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

};
#endif // COMMANDRUNNER_H
