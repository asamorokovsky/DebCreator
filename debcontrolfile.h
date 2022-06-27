#ifndef DEBCONTROLFILE_H
#define DEBCONTROLFILE_H

#include <QString>
#include <QStringList>

class DebControlFile
{
public:
    DebControlFile();

    void setPackage(QString package);
    void setVersion(QString version);
    void setPriority(QString priority);
    void setSection(QString section);
    void setMaintainer(QString maintainer);
    void setInstalledSize(ulong installedSize);
    void setDependPackages(QString depends);
    void setSuggestPackages(QString suggests);
    void setConflictPackages(QString conflicts);
    void setDescription(QString description);

    QString getPackage();
    QString getVersion();
    QString getPriority();
    QString getSection();
    QString getMaintainer();
    ulong getInstalledSize();
    QString getDependPackages();
    QString getSuggestPackages();
    QString getConflictPackages();
    QString getDescription();

    void parceFromFile(QString filePath);

private:
    QString _package;
    QString _version;
    QString _priority;
    QString _section;
    QString _maintainer;
    ulong _installedSize;
    QString _depends;
    QString _suggests;
    QString _conflicts;
    QString _description;
};

#endif // DEBCONTROLFILE_H
