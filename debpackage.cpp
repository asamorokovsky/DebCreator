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

void DebPackage::setPermScriptPath(QString filePath)
{
    this->prermScriptPath = filePath;
}

void DebPackage::setPostrmScriptPath(QString filePath)
{
    this->postrmScriptPath = filePath;
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

QString DebPackage::getPermScriptPath()
{
    return this->prermScriptPath;
}

QString DebPackage::getPostrmScriptPath()
{
    return this->postrmScriptPath;
}

QString DebPackage::getPackagePath()
{
    return this->packagePath;
}

void DebPackage::setPackagePath(QString path)
{

}
