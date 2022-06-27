#ifndef DEBPACKAGE_H
#define DEBPACKAGE_H

#include <QString>
#include <QStringList>

#include "debcontrolfile.h"

class DebPackage
{
public:
    DebPackage();
private:
    QString name;
    QString version;

    QString executableBinaryFilePath;
    QStringList additionalFilesPath;

    DebControlFile controlFileData;

    // Debian scripts path - preins, postinst, prerm, postrm
    QString preinstScriptPath;
    QString postinstScriptPath;
    QString prermScriptPath;
    QString postrmScriptPath;
};

#endif // DEBPACKAGE_H
