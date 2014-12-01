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
//private slots:
  //  void readyReadStandardOutput(QProcess process);
  //void readyReadStandardError(QProcess process);
};
#endif // COMMANDRUNNER_H
