#include "debcontrolfile.h"

DebControlFile::DebControlFile()
{
    // REQUIRED FIELDS
    _package = QString();
    _version = QString();
    _architecture = QString();
    _maintainer = QString();
    _description = QString();

    // RECOMMENDED FIELDS
    _section = QString();
    _priority = Priority::Optional;

    // OTHER FIELDS
    _essential = false;
    _source = QString();
    _installedSize = 0;
    _homepage = QString();
}

// REQUIRED FIELDS
void DebControlFile::setPackage(QString package)
{
    _package = package;
}

void DebControlFile::setVersion(QString version)
{
    _version = version;
}

void DebControlFile::setAarchitecture(QString architecture)
{
    _architecture = architecture;
}

void DebControlFile::setMaintainer(QString maintainer)
{
    _maintainer = maintainer;
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

QString DebControlFile::getArchitecture()
{
    return _architecture;
}

QString DebControlFile::getMaintainer()
{
    return _maintainer;
}

QString DebControlFile::getDescription()
{
    return _description;
}

// RECOMMENDED FIELDS
void DebControlFile::setSection(QString section)
{
    _section = section;
}

void DebControlFile::setPriority(enum Priority priority)
{
    _priority = priority;
}

QString DebControlFile::getSection()
{
    return _section;
}

enum Priority DebControlFile::getPriority()
{
    return _priority;
}

// OTHER FIELDS
void DebControlFile::setEssential(bool essential)
{
    _essential = essential;
}

void DebControlFile::setSource(QString source)
{
    _source = source;
}

void DebControlFile::setDepends(QList<LibraryPackage> depends)
{
    _depends = depends;
}

void DebControlFile::setPreDepends(QList<LibraryPackage> pre_depends)
{
    _pre_depends = pre_depends;
}

void DebControlFile::setRecommends(QList<LibraryPackage> recommends)
{
    _recommends = recommends;
}

void DebControlFile::setSuggests(QList<LibraryPackage> suggests)
{
    _suggests = suggests;
}

void DebControlFile::setBreaks(QList<LibraryPackage> breaks)
{
    _breaks = breaks;
}

void DebControlFile::setConflicts(QList<LibraryPackage> conflicts)
{
    _conflicts = conflicts;
}

void DebControlFile::setReplaces(QList<LibraryPackage> replaces)
{
    _replaces = replaces;
}

void DebControlFile::setProvides(QList<LibraryPackage> provides)
{
    _provides = provides;
}

void DebControlFile::setBuiltUsing(QList<LibraryPackage> builtUsing)
{
    _builtUsing = builtUsing;
}

void DebControlFile::setInstalledSize(ulong installedSize)
{
    _installedSize = installedSize;
}

void DebControlFile::setHomepage(QString homepage)
{
    _homepage = homepage;
}

bool DebControlFile::isEssential()
{
    return _essential;
}

QString DebControlFile::getSource()
{
    return _source;
}

QList<LibraryPackage> DebControlFile::getDepends()
{
    return _depends;
}

QList<LibraryPackage> DebControlFile::getPreDepends()
{
    return _pre_depends;
}

QList<LibraryPackage> DebControlFile::getRecommends()
{
    return _recommends;
}

QList<LibraryPackage> DebControlFile::getSuggests()
{
    return _suggests;
}

QList<LibraryPackage> DebControlFile::getBreaks()
{
    return _breaks;
}

QList<LibraryPackage> DebControlFile::getConflicts()
{
    return _conflicts;
}

QList<LibraryPackage> DebControlFile::getReplaces()
{
    return _replaces;
}

QList<LibraryPackage> DebControlFile::getProvides()
{
    return _provides;
}

QList<LibraryPackage> DebControlFile::getBuiltUsing()
{
    return _builtUsing;
}

ulong DebControlFile::getInstalledSize()
{
    return _installedSize;
}

QString DebControlFile::getHomepage()
{
    return _homepage;
}

QList<LibraryPackage> DebControlFile::getLibraryPackagesByFieldInString(QString field, QString searchString)
{
    QList<LibraryPackage> libsResult;
    if (searchString.startsWith(field)) {
        libsResult = getLibraryPackagesInString(searchString.remove(field).trimmed());
    }
    return libsResult;
}

QList<LibraryPackage> DebControlFile::getLibraryPackagesInString(QString searchString)
{
    QList<LibraryPackage> libsResult;
    QStringList libs = searchString.trimmed().split(",");

    foreach(QString currentLib, libs) {
        if (!currentLib.isEmpty()) {
            QString libName, libVersion;

            QRegExp reLibName("[^\\(\\)]+(?=)");
            if (reLibName.indexIn(currentLib) != -1)
                libName= reLibName.capturedTexts().first().trimmed();

            QRegExp reLibVersion("[^(\\)]+(?=\\))");
            if (reLibVersion.indexIn(currentLib) != -1)
                libVersion = reLibVersion.capturedTexts().first();

            libsResult.append(LibraryPackage(libName, libVersion));
        }
    }
    return libsResult;
}

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

        if (currentString.startsWith("Architecture:"))
            result->setAarchitecture(currentString.remove("Architecture:").trimmed());

        if (currentString.startsWith("Maintainer:"))
            result->setMaintainer(currentString.remove("Maintainer:").trimmed());

        if (currentString.startsWith("Description:"))
            result->setDescription(currentString.remove("Description:").trimmed());

        if (currentString.startsWith("Section:"))
            result->setSection(currentString.remove("Section:").trimmed());

        if (currentString.startsWith("Priority:")) {
            Priority pr;
            QString prStr = currentString.remove("Priority:").trimmed().toLower();

            if (prStr == "required")
                pr = Priority::Required;
            if (prStr == "important")
                pr = Priority::Important;
            if (prStr == "standard")
                pr = Priority::Standard;
            if (prStr == "optional")
                pr = Priority::Optional;
            if (prStr == "extra")
                pr = Priority::Extra;

            result->setPriority(pr);
        }

        if (currentString.startsWith("Essential:"))
            result->setEssential(currentString.remove("Essential:").trimmed() == "yes" ? true : false);

        if (currentString.startsWith("Source:"))
            result->setSource(currentString.remove("Source:").trimmed());

        if (currentString.startsWith("Depends:"))
            result->setDepends(getLibraryPackagesByFieldInString("Depends:", currentString));

        if (currentString.startsWith("Pre-Depends:"))
            result->setPreDepends(getLibraryPackagesByFieldInString("Pre-Depends:", currentString));

        if (currentString.startsWith("Recommends:"))
            result->setRecommends(getLibraryPackagesByFieldInString("Recommends:", currentString));

        if (currentString.startsWith("Suggests:"))
            result->setSuggests(getLibraryPackagesByFieldInString("Suggests:", currentString));

        if (currentString.startsWith("Breaks:"))
            result->setBreaks(getLibraryPackagesByFieldInString("Breaks:", currentString));

        if (currentString.startsWith("Conflicts:"))
            result->setConflicts(getLibraryPackagesByFieldInString("Conflicts:", currentString));

        if (currentString.startsWith("Replaces:"))
            result->setReplaces(getLibraryPackagesByFieldInString("Replaces:", currentString));

        if (currentString.startsWith("Provides:"))
            result->setProvides(getLibraryPackagesByFieldInString("Provides:", currentString));

        if (currentString.startsWith("Built-Using:"))
            result->setBuiltUsing(getLibraryPackagesByFieldInString("Built-Using:", currentString));

        if (currentString.startsWith("Installed-Size:"))
            result->setInstalledSize(currentString.remove("Installed-Size:").trimmed().toULong());

        if (currentString.startsWith("Homepage:"))
            result->setHomepage(currentString.remove("Homepage:").trimmed());

    }
    return qMakePair(true, result);
}

void DebControlFile::toFile(QString filePath, DebControlFile data)
{
    if (filePath.isEmpty())
        return;

    if (data.getPackage().isEmpty() ||
            data.getVersion().isEmpty() ||
            data.getArchitecture().isEmpty() ||
            data.getMaintainer().isEmpty() ||
            data.getDescription().isEmpty())
        return;

    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly))
        return;

    QTextStream fileDataStream(&file);
    fileDataStream.setCodec("UTF-8");

    fileDataStream<<QString("Package: %1\n").arg(data.getPackage());
    fileDataStream<<QString("Version: %1\n").arg(data.getVersion());
    fileDataStream<<QString("Architecture: %1\n").arg(data.getArchitecture());
    fileDataStream<<QString("Maintainer: %1\n").arg(data.getMaintainer());
    fileDataStream<<QString("Description: %1\n").arg(data.getDescription());

    if (!data.getSection().isEmpty())
        fileDataStream<<QString("Section: %1\n").arg(data.getSection());

    if (data.getPackage() != Priority::None)
        fileDataStream<<QString("Priority: %1\n").arg(PriorityToString[data.getPriority()]);

    fileDataStream<<QString("Essential: %1\n").arg(data.isEssential() ? "yes": "no");

    if (!data.getSource().isEmpty())
        fileDataStream<<QString("Source: %1\n").arg(data.getSource());

    if (!data.getDepends().isEmpty())
        fileDataStream<<QString("Depends: %1\n").arg(Utils::libraryPackageToString(data.getDepends()));

    if (!data.getPreDepends().isEmpty())
        fileDataStream<<QString("Pre-Depends: %1\n").arg(Utils::libraryPackageToString(data.getPreDepends()));

    if (!data.getRecommends().isEmpty())
        fileDataStream<<QString("Recommends: %1\n").arg(Utils::libraryPackageToString(data.getRecommends()));

    if (!data.getSuggests().isEmpty())
        fileDataStream<<QString("Suggests: %1\n").arg(Utils::libraryPackageToString(data.getSuggests()));

    if (!data.getBreaks().isEmpty())
        fileDataStream<<QString("Breaks: %1\n").arg(Utils::libraryPackageToString(data.getBreaks()));

    if (!data.getConflicts().isEmpty())
        fileDataStream<<QString("Conflicts: %1\n").arg(Utils::libraryPackageToString(data.getConflicts()));

    if (!data.getReplaces().isEmpty())
        fileDataStream<<QString("Replaces: %1\n").arg(Utils::libraryPackageToString(data.getReplaces()));

    if (!data.getProvides().isEmpty())
        fileDataStream<<QString("Provides: %1\n").arg(Utils::libraryPackageToString(data.getProvides()));

    if (!data.getBuiltUsing().isEmpty())
        fileDataStream<<QString("Built-Using: %1\n").arg(Utils::libraryPackageToString(data.getBuiltUsing()));

    if (data.getInstalledSize() != 0)
        fileDataStream<<QString("Installed-Size: %1\n").arg(data.getInstalledSize());

    if (!data.getHomepage().isEmpty())
        fileDataStream<<QString("Homepage: %1\n").arg(data.getHomepage());

    file.close();
}
