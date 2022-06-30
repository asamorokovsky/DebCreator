#ifndef DEBCONTROLFILE_H
#define DEBCONTROLFILE_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QRegExp>

#include <QDebug>

#include "librarypackage.h"
#include "utils.h"

enum Priority{None, Required, Important, Standard, Optional, Extra};
static const char* PriorityToString[] __attribute__((unused)) = {"", "required", "important", "standard", "optional", "extra"};


class DebControlFile
{
public:
    DebControlFile();

    // REQUIRED FIELDS
    void setPackage(QString package);
    void setVersion(QString version);
    void setAarchitecture(QString architecture);
    void setMaintainer(QString maintainer);
    void setDescription(QString description);

    QString getPackage();
    QString getVersion();
    QString getArchitecture();
    QString getMaintainer();
    QString getDescription();

    // RECOMMENDED FIELDS
    void setSection(QString section);
    void setPriority(enum Priority priority);

    QString getSection();
    enum Priority getPriority();

    // OTHER FIELDS
    void setEssential(bool essential);
    void setSource(QString source);
    void setDepends(QList<LibraryPackage> depends);
    void setPreDepends(QList<LibraryPackage> pre_depends);
    void setRecommends(QList<LibraryPackage> recommends);
    void setSuggests(QList<LibraryPackage> suggests);
    void setBreaks(QList<LibraryPackage> breaks);
    void setConflicts(QList<LibraryPackage> conflicts);
    void setReplaces(QList<LibraryPackage> replaces);
    void setProvides(QList<LibraryPackage> provides);
    void setBuiltUsing(QList<LibraryPackage> builtUsing);
    void setInstalledSize(ulong installedSize);
    void setHomepage(QString homepage);

    bool isEssential();
    QString getSource();
    QList<LibraryPackage> getDepends();
    QList<LibraryPackage> getPreDepends();
    QList<LibraryPackage> getRecommends();
    QList<LibraryPackage> getSuggests();
    QList<LibraryPackage> getBreaks();
    QList<LibraryPackage> getConflicts();
    QList<LibraryPackage> getReplaces();
    QList<LibraryPackage> getProvides();
    QList<LibraryPackage> getBuiltUsing();
    ulong getInstalledSize();
    QString getHomepage();

    static QList<LibraryPackage> getLibraryPackagesByFieldInString(QString field, QString searchString);
    static QList<LibraryPackage> getLibraryPackagesInString(QString searchString);
    static QPair<bool, DebControlFile*> fromFile(QString filePath);
    static void toFile(QString filePath, DebControlFile *data);

private:
    // REQUIRED FIELDS
    QString _package;
    QString _version;
    QString _architecture;
    QString _maintainer;
    QString _description;

    // RECOMMENDED FIELDS
    QString _section;
    enum Priority _priority;

    // OTHER FIELDS
    bool _essential;
    QString _source;
    QList<LibraryPackage> _depends;
    QList<LibraryPackage> _pre_depends;
    QList<LibraryPackage> _recommends;
    QList<LibraryPackage> _suggests;
    QList<LibraryPackage> _breaks;
    QList<LibraryPackage> _conflicts;
    QList<LibraryPackage> _replaces;
    QList<LibraryPackage> _provides;
    QList<LibraryPackage> _builtUsing;
    ulong _installedSize;
    QString _homepage;
};

#endif // DEBCONTROLFILE_H
