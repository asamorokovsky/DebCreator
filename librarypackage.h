#ifndef LIBRARYPACKAGE_H
#define LIBRARYPACKAGE_H

#include <QString>

class LibraryPackage
{
public:
    LibraryPackage(QString name, QString version = QString());

    QString getName();
    QString getVersion();

private:
    QString _name;
    QString _version;
};

#endif // LIBRARYPACKAGE_H
