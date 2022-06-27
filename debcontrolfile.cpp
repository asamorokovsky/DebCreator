#include "debcontrolfile.h"

DebControlFile::DebControlFile()
{

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

void DebControlFile::setMaintainer(QString maintainer)
{
    _maintainer = maintainer;
}

void DebControlFile::setInstalledSize(ulong installedSize)
{
    _installedSize = installedSize;
}

void DebControlFile::setDependPackages(QString depends)
{
    _depends = depends;
}

void DebControlFile::setSuggestPackages(QString suggests)
{
    _suggests = suggests;
}

void DebControlFile::setConflictPackages(QString conflicts)
{
    _conflicts = conflicts;
}

void DebControlFile::setDescription(QString description)
{
    _description = description;
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

QString DebControlFile::getMaintainer()
{
    return _maintainer;
}

ulong DebControlFile::getInstalledSize()
{
    return _installedSize;
}

QString DebControlFile::getDependPackages()
{
    return _depends;
}

QString DebControlFile::getSuggestPackages()
{
    return _suggests;
}

QString DebControlFile::getConflictPackages()
{
    return _conflicts;
}

QString DebControlFile::getDescription()
{
    return _description;
}

void DebControlFile::parceFromFile(QString filePath)
{

}
