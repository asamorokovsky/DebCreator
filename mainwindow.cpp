#include "mainwindow.h"

Package::Package(QString name, QString version)
{
    _name = name;
    _version = version;
}

QString Package::getName()
{
    return _name.trimmed();
}

QString Package::getVersion()
{
    return _version.trimmed();
}



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    createUI();
    connectUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createUI()
{
    this->mainWidget = new QTabWidget();

    // First tab - select file
    {
        this->firstTab_Widget = new QWidget();
        QVBoxLayout *widgetLayout = new QVBoxLayout(this->firstTab_Widget);

        QGridLayout *centralLayout = new QGridLayout();
        //centralLayout->setAlignment(Qt::AlignCenter);
        centralLayout->addWidget(new QLabel(tr("Please select file:")), 0, 0);
        this->firstTab_filePath = new QLineEdit("");
        this->firstTab_filePath->setReadOnly(true);
        centralLayout->addWidget(this->firstTab_filePath, 1, 0);
        this->firstTab_filePathSelectBtn = new QPushButton(tr("Select file"));
        centralLayout->addWidget(this->firstTab_filePathSelectBtn, 1, 1);
        widgetLayout->addLayout(centralLayout);

        QHBoxLayout *controlButtonsLayout = new QHBoxLayout();
        controlButtonsLayout->setAlignment(Qt::AlignBottom);
        this->firstTab_quitBtn = new QPushButton(tr("Quit"));
        this->firstTab_nextBtn = new QPushButton(tr("Next"));
        controlButtonsLayout->addWidget(this->firstTab_quitBtn, 0, Qt::AlignLeft);
        controlButtonsLayout->addWidget(this->firstTab_nextBtn, 0, Qt::AlignRight);

        widgetLayout->addLayout(controlButtonsLayout);

        this->mainWidget->addTab(this->firstTab_Widget, tr("1. Select file"));
    }
    /*
    // Second tab - package name
    {
        this->secondTab_Widget = new QWidget();
        this->mainWidget->addTab(this->secondTab_Widget, tr("2. Package name"));

        QVBoxLayout *widgetLayout = new QVBoxLayout(this->secondTab_Widget);
        QGridLayout *centralLayout = new QGridLayout();
        centralLayout->addWidget(new QLabel(tr("Please enter package name:")), 0, 0);
        this->secondTab_packageName = new QLineEdit("");
        QRegExp rx;
        rx.setPattern("[a-zA-Z0-9-]+");

        QValidator *validator = new QRegExpValidator(rx, this);
        secondTab_packageName->setValidator(validator);
        centralLayout->addWidget(this->secondTab_packageName);
        widgetLayout->addLayout(centralLayout);

        QHBoxLayout *controlButtonsLayout = new QHBoxLayout();
        controlButtonsLayout->setAlignment(Qt::AlignBottom);
        this->secondTab_backBtn = new QPushButton(tr("Back"));
        this->secondTab_nextBtn = new QPushButton(tr("Next"));
        controlButtonsLayout->addWidget(this->secondTab_backBtn, 0, Qt::AlignLeft);
        controlButtonsLayout->addWidget(this->secondTab_nextBtn, 0, Qt::AlignRight);

        widgetLayout->addLayout(controlButtonsLayout);
    }
*/
    // Second tab - DEB/control
    {
        this->secondTab_Widget = new QWidget();
        this->mainWidget->addTab(this->secondTab_Widget, tr("2. DEB/control"));

        QVBoxLayout *widgetLayout = new QVBoxLayout(this->secondTab_Widget);
        QGridLayout *headerLayout = new QGridLayout();
        headerLayout->addWidget(new QLabel(tr("Select an existing file:")), 0, 0, Qt::AlignLeft);
        this->secondTab_controlFile = new QLineEdit("");
        secondTab_controlFile->setReadOnly(true);
        /*
        QRegExp rx;
        rx.setPattern("[a-zA-Z0-9-]+");
        QValidator *validator = new QRegExpValidator(rx, this);*/

        headerLayout->addWidget(this->secondTab_controlFile, 1, 0);

        this->secondTab_selectControlFileBtn = new QPushButton(tr("Select file"));
        headerLayout->addWidget(this->secondTab_selectControlFileBtn, 1, 1, Qt::AlignRight);

        widgetLayout->addLayout(headerLayout);

        this->secondTab_controlFileGB = new QGroupBox(tr("Control file data:"));
        this->secondTab_controlFileGB->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        QGridLayout *controlFileGBLayout = new QGridLayout(secondTab_controlFileGB);
        controlFileGBLayout->addWidget(new QLabel("Package:"), 0, 0, Qt::AlignLeft | Qt::AlignTop);
        controlFileGBLayout->addWidget(new QLabel("Version:"), 1, 0, Qt::AlignLeft | Qt::AlignTop);
        controlFileGBLayout->addWidget(new QLabel("Priority:"), 2, 0, Qt::AlignLeft | Qt::AlignTop);
        controlFileGBLayout->addWidget(new QLabel("Section:"), 3, 0, Qt::AlignLeft | Qt::AlignTop);
        controlFileGBLayout->addWidget(new QLabel("Maintainer:"), 4, 0, Qt::AlignLeft | Qt::AlignTop);
        controlFileGBLayout->addWidget(new QLabel("Installed-Size:"), 5, 0, Qt::AlignLeft | Qt::AlignTop);
        controlFileGBLayout->addWidget(new QLabel("Depends:"), 6, 0, Qt::AlignLeft | Qt::AlignTop);
        controlFileGBLayout->addWidget(new QLabel("Suggests:"), 7, 0, Qt::AlignLeft | Qt::AlignTop);
        controlFileGBLayout->addWidget(new QLabel("Conflicts:"), 8, 0, Qt::AlignLeft | Qt::AlignTop);
        controlFileGBLayout->addWidget(new QLabel("Description:"), 9, 0, Qt::AlignLeft | Qt::AlignTop);

        this->secondTab_control_packageLE = new QLineEdit(tr(""));
        this->secondTab_control_packageLE->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9-]+"), this));
        this->secondTab_control_versionLE = new QLineEdit(tr(""));
        this->secondTab_control_versionLE->setValidator(new QRegExpValidator(QRegExp("[0-9.]+"), this));
        this->secondTab_control_priorityLE = new QLineEdit(tr(""));
        this->secondTab_control_priorityLE->setValidator(new QRegExpValidator(QRegExp("[a-z]+"), this));
        this->secondTab_control_sectionLE = new QLineEdit(tr(""));
        this->secondTab_control_sectionLE->setValidator(new QRegExpValidator(QRegExp("[a-z]+"), this));
        this->secondTab_control_maintainerTE = new QTextEdit(tr(""));
        this->secondTab_control_installed_sizeLE = new QLineEdit(tr(""));
        this->secondTab_control_installed_sizeLE->setValidator(new QRegExpValidator(QRegExp("[0-9]+"), this));
        this->secondTab_control_dependsTE = new QTextEdit(tr(""));
        this->secondTab_control_suggestsTE = new QTextEdit(tr(""));
        this->secondTab_control_conflictsTE = new QTextEdit(tr(""));
        this->secondTab_control_descriptionTE = new QTextEdit(tr(""));

        controlFileGBLayout->addWidget(this->secondTab_control_packageLE, 0, 1);
        controlFileGBLayout->addWidget(this->secondTab_control_versionLE, 1, 1);
        controlFileGBLayout->addWidget(this->secondTab_control_priorityLE, 2, 1);
        controlFileGBLayout->addWidget(this->secondTab_control_sectionLE, 3, 1);
        controlFileGBLayout->addWidget(this->secondTab_control_maintainerTE, 4, 1);
        controlFileGBLayout->addWidget(this->secondTab_control_installed_sizeLE, 5, 1);
        controlFileGBLayout->addWidget(this->secondTab_control_dependsTE, 6, 1);
        controlFileGBLayout->addWidget(this->secondTab_control_suggestsTE, 7, 1);
        controlFileGBLayout->addWidget(this->secondTab_control_conflictsTE, 8, 1);
        controlFileGBLayout->addWidget(this->secondTab_control_descriptionTE, 9, 1);


        widgetLayout->addWidget(this->secondTab_controlFileGB);

        QHBoxLayout *controlButtonsLayout = new QHBoxLayout();
        controlButtonsLayout->setAlignment(Qt::AlignBottom);
        this->secondTab_backBtn = new QPushButton(tr("Back"));
        this->secondTab_nextBtn = new QPushButton(tr("Next"));
        controlButtonsLayout->addWidget(this->secondTab_backBtn, 0, Qt::AlignLeft);
        controlButtonsLayout->addWidget(this->secondTab_nextBtn, 0, Qt::AlignRight);

        widgetLayout->addLayout(controlButtonsLayout);
    }


    this->setCentralWidget(this->mainWidget);
}

void MainWindow::connectUI()
{
    // Connect first tab widgets to their slots
    connect(this->firstTab_filePathSelectBtn, &QPushButton::clicked, this, &MainWindow::slot_firstTab_filePathSelectBtn_clicked);
    connect(this->firstTab_quitBtn, &QPushButton::clicked, this, &MainWindow::slot_firstTab_quitBtn_clicked);
    connect(this->firstTab_nextBtn, &QPushButton::clicked, this, &MainWindow::slot_firstTab_nextBtn_clicked);

    // Connect second tab widgets to their slots
    connect(this->secondTab_backBtn, &QPushButton::clicked, this, &MainWindow::slot_secondTab_backBtn_clicked);
    connect(this->secondTab_nextBtn, &QPushButton::clicked, this, &MainWindow::slot_secondTab_nextBtn_clicked);

}

// This function determines if the selected file is a binary executable file.
bool MainWindow::isFileElf(QString filePath)
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
QList<Package> MainWindow::getDependnciesForElf(QString filePath)
{
    QList<Package> packages;

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
            foreach (Package currentPackage, packages) {
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
                packages.append(Package(packageName, packageVersion));
            }
        }
    }
    return packages;
}

// Private slots

// First tab slots
void MainWindow::slot_firstTab_filePathSelectBtn_clicked()
{
    QString selectedFile = QFileDialog::getOpenFileName(this, tr("Select file"));
    if (selectedFile.isEmpty()) {
        return;
    }
    if (!isFileElf(selectedFile))
        QMessageBox::warning(this, tr("Wrong file"), tr("Selected file is not DYN (Shared object file)!"));
    else
        this->firstTab_filePath->setText(selectedFile);
}

void MainWindow::slot_firstTab_quitBtn_clicked()
{
    close();
}

void MainWindow::slot_firstTab_nextBtn_clicked()
{
    if (this->firstTab_filePath->text().trimmed().isEmpty())
        return;

    this->mainWidget->setCurrentIndex(this->mainWidget->indexOf(this->secondTab_Widget));
}
/*
// Second tab slots
void MainWindow::slot_secondTab_backBtn_clicked()
{
    this->mainWidget->setCurrentIndex(this->mainWidget->indexOf(this->firstTab_Widget));
}

void MainWindow::slot_secondTab_nextBtn_clicked()
{
    if (this->secondTab_packageName->text().trimmed().isEmpty())
        return;

    //this->mainWidget->setCurrentIndex(this->mainWidget->indexOf(this->thirdTab_Widget));
    getDependnciesForElf(this->firstTab_filePath->text().trimmed());
}
*/

// Second tab slots
void MainWindow::slot_secondTab_backBtn_clicked()
{
    this->mainWidget->setCurrentIndex(this->mainWidget->indexOf(this->secondTab_Widget));
}

void MainWindow::slot_secondTab_nextBtn_clicked()
{

}
