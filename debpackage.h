#ifndef DEBPACKAGE_H
#define DEBPACKAGE_H

#include <QString>
#include <QStringList>

#include "debcontrolfile.h"

class DebPackage
{
public:
    DebPackage();

    void setExecutableBinaryFilePath(QString filePath);
    void setAdditionalFilesPath(QStringList files);

    void setInstallationPath(QString path);

    void setControlFileData(DebControlFile file);

    void setPreinstScriptPath(QString filePath);
    void setPostinstScriptPath(QString filePath);
    void setPermScriptPath(QString filePath);
    void setPostrmScriptPath(QString filePath);

    QString getExecutableBinaryFilePath();
    QStringList getAdditionalFilesPath();

    QString getInstallationPath();

    DebControlFile getControlFileData();

    QString getPreinstScriptPath();
    QString getPostinstScriptPath();
    QString getPermScriptPath();
    QString getPostrmScriptPath();

    QString getPackagePath();

private:
    QString executableBinaryFilePath;
    QStringList additionalFilesPath;

    QString installationPath;

    DebControlFile controlFileData;

    // Debian scripts path - preins, postinst, prerm, postrm
    QString preinstScriptPath;
    QString postinstScriptPath;
    QString prermScriptPath;
    QString postrmScriptPath;

    QString packagePath;



    void setPackagePath(QString path);
};

#endif // DEBPACKAGE_H
