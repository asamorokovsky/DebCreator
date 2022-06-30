#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QList>
#include <QStringList>

#include <QFile>
#include <QProcess>

#include "librarypackage.h"

class Utils
{
public:
    Utils();

    static bool isFileElf(QString filePath);
    static QList<LibraryPackage> getDependnciesForElf(QString filePath);

    static QString libraryPackageToString(QList<LibraryPackage> list);
    static QString libraryPackageToString(LibraryPackage lib);
};

#endif // UTILS_H
