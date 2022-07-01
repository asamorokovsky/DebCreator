#ifndef DEBPACKAGE_H
#define DEBPACKAGE_H

#include <QString>
#include <QStringList>

#include <QDir>
#include <QFile>
#include <QTextStream>

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
    void setPrermScriptPath(QString filePath);
    void setPostrmScriptPath(QString filePath);

    void setCopyrightPath(QString filePath);
    void setChangelogPath(QString filePath);

    void setConffilesPath(QString filePath);
    void setDirsPath(QString filePath);
    void setDocsPath(QString filePath);
    void setNewsPath(QString filePath);

    QString getExecutableBinaryFilePath();
    QStringList getAdditionalFilesPath();

    QString getInstallationPath();

    DebControlFile getControlFileData();

    QString getPreinstScriptPath();
    QString getPostinstScriptPath();
    QString getPrermScriptPath();
    QString getPostrmScriptPath();

    QString getCopyrightPath();
    QString getChangelogPath();

    QString getConffilesPath();
    QString getDirsPath();
    QString getDocsPath();
    QString getNewsPath();

    QString getPackagePath();

    void createPackage();

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

    QString copyrightPath;
    QString changelogPath;

    QString conffilesPath;
    QString dirsPath;
    QString docsPath;
    QString newsPath;

    QString packagePath;

    void setPackagePath(QString path);
};

#endif // DEBPACKAGE_H
