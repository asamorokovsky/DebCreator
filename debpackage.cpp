#include "debpackage.h"

DebPackage::DebPackage()
{

}

void DebPackage::setExecutableBinaryFilePath(QString filePath)
{
    this->executableBinaryFilePath = filePath;
}

void DebPackage::setAdditionalFilesPath(QStringList files)
{
    this->additionalFilesPath = files;
}

void DebPackage::setInstallationPath(QString path)
{
    this->installationPath = path;
}

void DebPackage::setControlFileData(DebControlFile file)
{
    this->controlFileData = file;

    setPackagePath(QString("%1_%2_%3").arg(controlFileData.getPackage(), controlFileData.getVersion(), controlFileData.getArchitecture()));
}

void DebPackage::setPreinstScriptPath(QString filePath)
{
    this->preinstScriptPath = filePath;
}

void DebPackage::setPostinstScriptPath(QString filePath)
{
    this->postinstScriptPath = filePath;
}

void DebPackage::setPrermScriptPath(QString filePath)
{
    this->prermScriptPath = filePath;
}

void DebPackage::setPostrmScriptPath(QString filePath)
{
    this->postrmScriptPath = filePath;
}

void DebPackage::setCopyrightPath(QString filePath)
{
    this->copyrightPath = filePath;
}

void DebPackage::setChangelogPath(QString filePath)
{
    this->changelogPath = filePath;
}

void DebPackage::setConffilesPath(QString filePath)
{
    this->conffilesPath = filePath;
}

void DebPackage::setDirsPath(QString filePath)
{
    this->dirsPath = filePath;
}

void DebPackage::setDocsPath(QString filePath)
{
    this->docsPath = filePath;
}

void DebPackage::setNewsPath(QString filePath)
{
    this->newsPath = filePath;
}

QString DebPackage::getExecutableBinaryFilePath()
{
    return this->executableBinaryFilePath;
}

QStringList DebPackage::getAdditionalFilesPath()
{
    return this->additionalFilesPath;
}

QString DebPackage::getInstallationPath()
{
    return this->installationPath;
}

DebControlFile DebPackage::getControlFileData()
{
    return this->controlFileData;
}

QString DebPackage::getPreinstScriptPath()
{
    return this->preinstScriptPath;
}

QString DebPackage::getPostinstScriptPath()
{
    return this->postinstScriptPath;
}

QString DebPackage::getPrermScriptPath()
{
    return this->prermScriptPath;
}

QString DebPackage::getPostrmScriptPath()
{
    return this->postrmScriptPath;
}

QString DebPackage::getCopyrightPath()
{
    return this->copyrightPath;
}

QString DebPackage::getChangelogPath()
{
    return this->changelogPath;
}

QString DebPackage::getConffilesPath()
{
    return this->conffilesPath;
}

QString DebPackage::getDirsPath()
{
    return this->dirsPath;
}

QString DebPackage::getDocsPath()
{
    return this->docsPath;
}

QString DebPackage::getNewsPath()
{
    return this->newsPath;
}

QString DebPackage::getPackagePath()
{
    return this->packagePath;
}

void DebPackage::setPackagePath(QString path)
{
    this->packagePath = path;
}

void DebPackage::createPackage()
{
    if (controlFileData.getPackage().isEmpty() || controlFileData.getVersion().isEmpty() || controlFileData.getArchitecture().isEmpty())
        return;

    // Create package folder
    if (!QDir().mkpath(this->packagePath))
        return; // Create packagePath error, exit.

    if (this->installationPath.isEmpty())
        this->setInstallationPath(QString("/var/%1").arg(controlFileData.getPackage())); // Installation path must not be empty!

    if (!QDir().mkpath(QString("%1/%2").arg(this->getPackagePath(), this->getInstallationPath())))
        return; // Create packagePath/installation error, exit.

    if (this->getExecutableBinaryFilePath().isEmpty())
        return; // Executable binary file is empty!

    if (!QFile(this->getExecutableBinaryFilePath()).exists())
        return; // Executable binary file does not exists!

    // Copy executable binary file to packagePath/installation
    {
        if (!QFile(QString("%1/%2/%3").arg(this->getPackagePath(), this->getInstallationPath(), QFileInfo(this->getExecutableBinaryFilePath()).fileName())).exists())
            if (!QFile::copy(this->getExecutableBinaryFilePath(), QString("%1/%2/%3").arg(this->getPackagePath(), this->getInstallationPath(), QFileInfo(this->getExecutableBinaryFilePath()).fileName())))
                return; // Copy error
    }

    // copy additional files to packagePath/installation
    {
        foreach (QString additionFilePath, this->getAdditionalFilesPath()) {
            if (!additionFilePath.isEmpty())
                QFile::copy(additionFilePath, QString("%1/%2/%3").arg(this->getPackagePath(), this->getInstallationPath(), QFileInfo(additionFilePath).fileName()));
        }
    }

    // Create DEBIAN dir
    {
        if (!QDir().mkpath(QString("%1/DEBIAN").arg(this->getPackagePath())))
            return; // Create DEBIAN folder error, exit.
    }

    // Create DEBIAN/compat file
    {
        QFile compatFile(QString("%1/DEBIAN/compat").arg(this->getPackagePath()));
        if (!compatFile.open(QIODevice::WriteOnly))
            return; // Cannot create DEBIAN/compat file.

        QTextStream compatStram(&compatFile);
        compatStram.setCodec("UTF-8");
        compatStram<<QString::number(10);

        compatFile.close();
    }

    // Create DEBIAN/control
    {
        DebControlFile::toFile(QString("%1/DEBIAN/control").arg(this->getPackagePath()), this->getControlFileData());
    }

    // Copy scripts (preinst, postinst, prerm, postrm) ad set permissions 555
    {
        if (!this->getPreinstScriptPath().isEmpty()) {
            QFile::copy(this->getPreinstScriptPath(), QString("%1/DEBIAN/preinst").arg(this->getPackagePath()));
            QFile::setPermissions(QString("%1/DEBIAN/preinst").arg(this->getPackagePath()), QFile::ReadOwner | QFile::ReadUser | QFile::ReadGroup | QFile::ReadOther |
                                  QFile::ExeOwner | QFile::ExeUser | QFile::ExeGroup | QFile::ExeOther);
        }
        if (!this->getPostinstScriptPath().isEmpty()) {
            QFile::copy(this->getPostinstScriptPath(), QString("%1/DEBIAN/postinst").arg(this->getPackagePath()));
            QFile::setPermissions(QString("%1/DEBIAN/postinst").arg(this->getPackagePath()), QFile::ReadOwner | QFile::ReadUser | QFile::ReadGroup | QFile::ReadOther |
                                  QFile::ExeOwner | QFile::ExeUser | QFile::ExeGroup | QFile::ExeOther);
        }
        if (!this->getPrermScriptPath().isEmpty()) {
            QFile::copy(this->getPrermScriptPath(), QString("%1/DEBIAN/prerm").arg(this->getPackagePath()));
            QFile::setPermissions(QString("%1/DEBIAN/prerm").arg(this->getPackagePath()), QFile::ReadOwner | QFile::ReadUser | QFile::ReadGroup | QFile::ReadOther |
                                  QFile::ExeOwner | QFile::ExeUser | QFile::ExeGroup | QFile::ExeOther);
        }
        if (!this->getPostrmScriptPath().isEmpty()) {
            QFile::copy(this->getPostrmScriptPath(), QString("%1/DEBIAN/postrm").arg(this->getPackagePath()));
            QFile::setPermissions(QString("%1/DEBIAN/postrm").arg(this->getPackagePath()), QFile::ReadOwner | QFile::ReadUser | QFile::ReadGroup | QFile::ReadOther |
                                  QFile::ExeOwner | QFile::ExeUser | QFile::ExeGroup | QFile::ExeOther);
        }
    }

    // Copy copyright, changelog, conffiles, dirs, docs, news
    {
        if (!this->getCopyrightPath().isEmpty())
            QFile::copy(this->getCopyrightPath(), QString("%1/DEBIAN/copyright").arg(this->getPackagePath()));
        if (!this->getChangelogPath().isEmpty())
            QFile::copy(this->getChangelogPath(), QString("%1/DEBIAN/changelog").arg(this->getPackagePath()));
        if (!this->getConffilesPath().isEmpty())
            QFile::copy(this->getConffilesPath(), QString("%1/DEBIAN/conffiles").arg(this->getPackagePath()));
        if (!this->getDirsPath().isEmpty())
            QFile::copy(this->getDirsPath(), QString("%1/DEBIAN/dirs").arg(this->getPackagePath()));
        if (!this->getDocsPath().isEmpty())
            QFile::copy(this->getDocsPath(), QString("%1/DEBIAN/docs").arg(this->getPackagePath()));
        if (!this->getNewsPath().isEmpty())
            QFile::copy(this->getNewsPath(), QString("%1/DEBIAN/news").arg(this->getPackagePath()));
    }
}
