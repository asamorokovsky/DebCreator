#ifndef DEBCONTROLFILE_H
#define DEBCONTROLFILE_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QRegExp>

#include "librarypackage.h"

class DebControlFile
{
public:
    DebControlFile();

    void setPackage(QString package);
    void setVersion(QString version);
    void setPriority(QString priority);
    void setSection(QString section);
    void setArchitecture(QString architecture);
    void setMaintainer(QString maintainer);
    void setInstalledSize(ulong installedSize);
    void setDependPackages(QList<LibraryPackage> depends);
    void setSuggestPackages(QList<LibraryPackage> suggests);
    void setConflictPackages(QList<LibraryPackage> conflicts);
    void setDescription(QString description);
    void setEssential(bool essential);

    QString getPackage();
    QString getVersion();
    QString getPriority();
    QString getSection();
    QString getArchitecture();
    QString getMaintainer();
    ulong getInstalledSize();
    QList<LibraryPackage> getDependPackages();
    QList<LibraryPackage> getSuggestPackages();
    QList<LibraryPackage> getConflictPackages();
    QString getDescription();
    bool isEssential();

    static QPair<bool, DebControlFile*> fromFile(QString filePath);
    static void toFile(QString filePath, DebControlFile *data);

private:
    QString _package;
    QString _version;
    QString _priority;
    QString _section;
    QString _architecture;
    QString _maintainer;
    ulong _installedSize;
    QList<LibraryPackage> _depends;
    QList<LibraryPackage> _suggests;
    QList<LibraryPackage> _conflicts;
    QString _description;
    bool _essential;
};

#endif // DEBCONTROLFILE_H
