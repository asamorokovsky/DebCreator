#include "librarypackage.h"

LibraryPackage::LibraryPackage(QString name, QString version)
{
    _name = name;
    _version = version;
}

QString LibraryPackage::getName()
{
    return _name;
}

QString LibraryPackage::getVersion()
{
    return _version;
}
