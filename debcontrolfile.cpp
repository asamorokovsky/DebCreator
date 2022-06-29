#include "debcontrolfile.h"

DebControlFile::DebControlFile()
{
    _package = QString();
    _version = QString();
    _priority = QString();
    _section = QString();
    _architecture = QString();
    _maintainer = QString();
    _installedSize = 0;
    _description = QString();
    _essential = false;
}

void DebControlFile::setPackage(QString package)
{
    _package = package;
}

void DebControlFile::setVersion(QString version)
{
    _version = version;
}

void DebControlFile::setPriority(QString priority)
{
    _priority = priority;
}

void DebControlFile::setSection(QString section)
{
    _section = section;
}

void DebControlFile::setArchitecture(QString architecture)
{
    _architecture = architecture;
}

void DebControlFile::setMaintainer(QString maintainer)
{
    _maintainer = maintainer;
}

void DebControlFile::setInstalledSize(ulong installedSize)
{
    _installedSize = installedSize;
}

void DebControlFile::setDependPackages(QList<LibraryPackage> depends)
{
    _depends = depends;
}

void DebControlFile::setSuggestPackages(QList<LibraryPackage> suggests)
{
    _suggests = suggests;
}

void DebControlFile::setConflictPackages(QList<LibraryPackage> conflicts)
{
    _conflicts = conflicts;
}

void DebControlFile::setDescription(QString description)
{
    _description = description;
}

void DebControlFile::setEssential(bool essential)
{
    _essential = essential;
}

QString DebControlFile::getPackage()
{
    return _package;
}

QString DebControlFile::getVersion()
{
    return _version;
}

QString DebControlFile::getPriority()
{
    return _priority;
}

QString DebControlFile::getSection()
{
    return _section;
}

QString DebControlFile::getArchitecture()
{
    return _architecture;
}

QString DebControlFile::getMaintainer()
{
    return _maintainer;
}

ulong DebControlFile::getInstalledSize()
{
    return _installedSize;
}

QList<LibraryPackage> DebControlFile::getDependPackages()
{
    return _depends;
}

QList<LibraryPackage> DebControlFile::getSuggestPackages()
{
    return _suggests;
}

QList<LibraryPackage> DebControlFile::getConflictPackages()
{
    return _conflicts;
}

QString DebControlFile::getDescription()
{
    return _description;
}

bool DebControlFile::isEssential()
{
    return _essential;
}

#include <QDebug>
QPair<bool, DebControlFile*> DebControlFile::fromFile(QString filePath)
{
    DebControlFile *result = new DebControlFile();
    if (filePath.trimmed().isEmpty())
        return qMakePair(false, result);

    QFile file(filePath);

    if (!file.exists())
        return qMakePair(false, result);

    if (!file.open(QIODevice::ReadOnly))
        return qMakePair(false, result);

    QByteArray filedataBuffer = file.readAll();

    file.close();

    QTextStream fileDataStream(&filedataBuffer, QIODevice::ReadOnly);
    QStringList fileData = fileDataStream.readAll().split("\n");

    foreach (QString currentString, fileData) {
        if (currentString.startsWith("Package:"))
            result->setPackage(currentString.remove("Package:").trimmed());

        if (currentString.startsWith("Version:"))
            result->setVersion(currentString.remove("Version:").trimmed());

        if (currentString.startsWith("Priority:"))
            result->setPriority(currentString.remove("Priority:").trimmed());

        if (currentString.startsWith("Section:"))
            result->setSection(currentString.remove("Section:").trimmed());

        if (currentString.startsWith("Architecture:"))
            result->setArchitecture(currentString.remove("Architecture:").trimmed());

        if (currentString.startsWith("Maintainer:"))
            result->setMaintainer(currentString.remove("Maintainer:").trimmed());

        if (currentString.startsWith("Installed-Size:"))
            result->setInstalledSize(currentString.remove("Installed-Size:").trimmed().toULong());

        if (currentString.startsWith("Depends:")) {
            QList<LibraryPackage> depends;
            QStringList libs = currentString.remove("Depends:").trimmed().split(",");

            foreach(QString currentLib, libs) {
                QString libName, libVersion;

                QRegExp reLibName("[^\\(\\)]+(?=)");
                if (reLibName.indexIn(currentLib) != -1)
                    libName= reLibName.capturedTexts().first().trimmed();

                QRegExp reLibVersion("[^(\\)]+(?=\\))");
                if (reLibVersion.indexIn(currentLib) != -1)
                    libVersion = reLibVersion.capturedTexts().first();

                depends.append(LibraryPackage(libName, libVersion));
            }
            result->setDependPackages(depends);
        }

        if (currentString.startsWith("Suggests:")) {
            QList<LibraryPackage> suggests;
            QStringList libs = currentString.remove("Suggests:").trimmed().split(",");

            foreach(QString currentLib, libs) {
                QString libName, libVersion;

                QRegExp reLibName("[^\\(\\)]+(?=)");
                if (reLibName.indexIn(currentLib) != -1)
                    libName= reLibName.capturedTexts().first().trimmed();

                QRegExp reLibVersion("[^(\\)]+(?=\\))");
                if (reLibVersion.indexIn(currentLib) != -1)
                    libVersion = reLibVersion.capturedTexts().first();

                suggests.append(LibraryPackage(libName, libVersion));
            }
            result->setSuggestPackages(suggests);
        }

        if (currentString.startsWith("Conflicts:")) {
            QList<LibraryPackage> conflicts;
            QStringList libs = currentString.remove("Conflicts:").trimmed().split(",");

            foreach(QString currentLib, libs) {
                QString libName, libVersion;

                QRegExp reLibName("[^\\(\\)]+(?=)");
                if (reLibName.indexIn(currentLib) != -1)
                    libName= reLibName.capturedTexts().first().trimmed();

                QRegExp reLibVersion("[^(\\)]+(?=\\))");
                if (reLibVersion.indexIn(currentLib) != -1)
                    libVersion = reLibVersion.capturedTexts().first();

                conflicts.append(LibraryPackage(libName, libVersion));
            }
            result->setConflictPackages(conflicts);
        }

        if (currentString.startsWith("Description:"))
            result->setDescription(currentString.remove("Description:").trimmed());

        if (currentString.startsWith("Essential:"))
            result->setEssential(currentString.remove("Description:").trimmed() == "yes" ? true : false);
    }
    return qMakePair(true, result);
}

void DebControlFile::toFile(QString filePath, DebControlFile* data)
{
    if (filePath.isEmpty())
        return;

    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly))
        return;

    // TODO create metod

    file.close();
}
