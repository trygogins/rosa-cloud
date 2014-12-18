#ifndef UTILS_H
#define UTILS_H

#include <QFile>
#include <QTextStream>

static void markClientMounted(QString name) {
    QFile config("/home/" + qgetenv("USER") + "/.rosa-cloud");
    if (config.open(QFile::WriteOnly | QFile::Append | QFile::Text)) {
        QTextStream stream(&config);
        stream << name << endl;
        config.close();
    }
}

static void markClientUnmounted(QString name) {
    // stub for Gosha
}

#endif // UTILS_H
