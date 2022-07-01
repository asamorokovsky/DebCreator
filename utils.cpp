#include "utils.h"

Utils::Utils()
{

}

// This function determines if the selected file is a binary executable file.
bool Utils::isFileElf(QString filePath)
{
    QProcess process;
    QStringList args;
    args.append("-h");
    args.append(filePath);
    process.start("readelf", args);

    if( !process.waitForStarted() || !process.waitForFinished() )
        return false;

    if (!process.readAllStandardError().isEmpty())
        return false;

    return process.readAllStandardOutput().trimmed().toLower().contains("dyn");
}

// This function creates a list of dependencies for the selected binary executable file.
QList<LibraryPackage> Utils::getDependnciesForElf(QString filePath)
{
    QList<LibraryPackage> packages;

    QProcess process;
    QStringList args;
    args.append("-p");
    args.append(filePath);

    process.start("objdump", args);

    if( !process.waitForStarted() || !process.waitForFinished() )
        return packages;

    if (!process.readAllStandardError().isEmpty())
        return packages;

    QStringList dependnciesLibs;
    foreach (QString currentLib, QString(process.readAllStandardOutput()).split("\n")) {
        if (currentLib.toLower().contains("needed")) {
            currentLib = currentLib.remove("NEEDED").simplified().trimmed();
            if (!dependnciesLibs.contains(currentLib) && !currentLib.trimmed().isEmpty())
                dependnciesLibs.append(currentLib);
        }
    }
    process.close();

    foreach (QString currentLib, dependnciesLibs) {
        args.clear();
        args.append("-S");
        args.append(currentLib);

        process.start("dpkg", args);
        process.waitForStarted();
        process.waitForFinished();

        QStringList packagesForCurrentLib = QString(process.readAllStandardOutput()).split("\n");

        process.close();

        foreach (QString packageName, packagesForCurrentLib) {
            packageName = packageName.mid(0, packageName.indexOf(":"));

            bool isPackageInList = false;
            foreach (LibraryPackage currentPackage, packages) {
                if (currentPackage.getName() == packageName) {
                    isPackageInList = true;
                    break;
                }
            }

            if (!isPackageInList && !packageName.trimmed().isEmpty() && packageName.startsWith("lib")) {
                args.clear();
                args.append("-s");
                args.append(packageName);
                process.start("dpkg", args);
                process.waitForStarted();
                process.waitForFinished();

                QStringList packageInfo = QString(process.readAllStandardOutput()).split("\n");
                process.close();

                QString packageVersion;

                foreach (QString curentPackageInfoItem, packageInfo) {
                    if (curentPackageInfoItem.simplified().toLower().startsWith("version")) {
                        packageVersion = curentPackageInfoItem.mid(curentPackageInfoItem.indexOf(":")+1).simplified();
                        break;
                    }
                }
                packages.append(LibraryPackage(packageName, packageVersion));
            }
        }
    }
    return packages;
}

QString Utils::libraryPackageToString(QList<LibraryPackage> list)
{
    QString result;

    for (int currentIndex = 0; currentIndex < list.size(); currentIndex++) {
        LibraryPackage libPackage = list.at(currentIndex);
        QString strToInsert = libPackage.getName();
        if (!libPackage.getVersion().isEmpty()) {
            if (!libPackage.getVersion().startsWith(">="))
                strToInsert.append(QString(" (>=%1)").arg(libPackage.getVersion()));
            else
                strToInsert.append(QString(" (%1)").arg(libPackage.getVersion()));
        }
        if (currentIndex != list.size()-1)
            strToInsert.append(", ");

        result.append(strToInsert);
    }

    return result;
}

QString Utils::libraryPackageToString(LibraryPackage lib)
{
    QString result = lib.getName();

    if (!lib.getVersion().isEmpty()) {
        if (!lib.getVersion().startsWith(">="))
            result.append(QString(" (>=%1)").arg(lib.getVersion()));
        else
            result.append(QString(" (%1)").arg(lib.getVersion()));
    }

    return result;
}

QString Utils::buildDebianPackage(QString dirPath)
{
    QProcess process;
    QStringList args;
    args.append("--build");
    args.append(dirPath);

    process.start("dpkg-deb", args);

    process.waitForStarted();
    process.waitForFinished();

    QString error = QString(process.readAllStandardError());
    if (!error.isEmpty())
        return error;

    QString output = QString(process.readAllStandardOutput());

    return output;
}
