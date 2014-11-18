#ifndef COMMANDRUNNER_H
#define COMMANDRUNNER_H
#include <QStringList>

class CommandRunner
{
public:
    CommandRunner();
    bool runCommand(QString command, QStringList arguments);
};

#endif // COMMANDRUNNER_H
