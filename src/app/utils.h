#ifndef UTILS_H
#define UTILS_H

#include <QFile>
#include <QTextStream>
#include <QProcess>

static void markClientMounted(QString name) {
    QFile config("/home/" + qgetenv("USER") + "/.rosa-cloud");
    if (config.open(QFile::WriteOnly | QFile::Append | QFile::Text)) {
        QTextStream stream(&config);
        stream << name << " 1" << endl;
        config.close();
    }
}

static void markMountInFile(QString name, QString state) {
    QString notState = state == "1" ? "0" : "1";
    CommandRunner runner;
    runner.runCommand("sed", QStringList() << "-i"
                      << "/" + name + " " + notState + "/c\\" + name + " " + state
                      << "/home/" + qgetenv("USER") + "/.rosa-cloud");
}

static void markClientUnmounted(QString sudoPassword, QString name) {
    //unmount
    QString username = qgetenv("USER");
    QString mountPoint = "/home/" + username + "/" + name + "_folder";
    CommandRunner runner;
    runner.runCommandAsRoot(sudoPassword, "umount " + mountPoint);
    markMountInFile(name, "0");
}

static bool correct(QString rootPassword) {
    QProcess proc;
    // check if the password correct by checking process exitCode
    proc.start("sh", QStringList() << "-c" << "echo '" + rootPassword + "' | sudo -kS ls");
    proc.waitForFinished();

    return proc.exitCode() == 0;
}

#endif // UTILS_H
