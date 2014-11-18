#include "commandrunner.h"
#include "QProcess"

CommandRunner::CommandRunner()
{   
}


bool CommandRunner::runCommand(QString command, QStringList arguments) {
    QProcess process;
    process.start(command, arguments);

    if (!process.waitForFinished()) {
        return false;
    }
    return process.exitCode() == 0;
}
