#ifndef COMMANDRUNNER_H
#define COMMANDRUNNER_H
#include <QStringList>
#include <QProcess>
#include <QObject>

class CommandRunner //: public QObject
{
public:
    CommandRunner();

    void runCommand(QString command, QStringList arguments);
    void runCommandAsRoot(QString sudoPassword, QString command);
};
#endif // COMMANDRUNNER_H
