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
    this->setWindowIcon(QIcon(":/Icons/Res/Icon/app.ico"));
    this->mainWidget = new QTabWidget();

    // First tab - select file
    {
        this->firstTab_Widget = new QWidget();
        QVBoxLayout *widgetLayout = new QVBoxLayout(this->firstTab_Widget);

        QGridLayout *centralLayout = new QGridLayout();
        centralLayout->setAlignment(Qt::AlignCenter);
        centralLayout->addWidget(new QLabel(tr("Please select file:")), 0, 0);
        this->firstTab_filePath = new QLineEdit("");
        this->firstTab_filePath->setReadOnly(true);
        centralLayout->addWidget(this->firstTab_filePath, 1, 0);
        this->firstTab_filePathSelectBtn = new QPushButton(tr("Select file"));
        this->firstTab_filePathSelectBtn ->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        centralLayout->addWidget(this->firstTab_filePathSelectBtn, 1, 1, Qt::AlignLeft);
        widgetLayout->addLayout(centralLayout);

        QHBoxLayout *controlButtonsLayout = new QHBoxLayout();
        controlButtonsLayout->setAlignment(Qt::AlignBottom);
        this->firstTab_quitBtn = new QPushButton(tr("Quit"));
        this->firstTab_quitBtn->setIcon(QIcon(":/Icons/Res/Icon/close.ico"));
        this->firstTab_nextBtn = new QPushButton(tr("Next"));
        this->firstTab_nextBtn->setIcon(QIcon(":/Icons/Res/Icon/arrow_right.ico"));
        controlButtonsLayout->addWidget(this->firstTab_quitBtn, 0, Qt::AlignLeft);
        controlButtonsLayout->addWidget(this->firstTab_nextBtn, 0, Qt::AlignRight);

        widgetLayout->addLayout(controlButtonsLayout);

        this->mainWidget->addTab(this->firstTab_Widget, tr("1. Select file"));
    }
    // Second tab - package name
    {
        this->secondTab_Widget = new QWidget();
        this->mainWidget->addTab(this->secondTab_Widget, tr("2. Package name"));

        QVBoxLayout *widgetLayout = new QVBoxLayout(this->secondTab_Widget);
        QGridLayout *centralLayout = new QGridLayout();
        centralLayout->setAlignment(Qt::AlignCenter);
        centralLayout->addWidget(new QLabel(tr("Please select additional files:")), 0, 0);
        this->secondTab_additionalFilesLE = new QLineEdit(tr(""));
        this->secondTab_additionalFilesLE->setReadOnly(true);
        centralLayout->addWidget(this->secondTab_additionalFilesLE, 1, 0);
        this->secondTab_additionalFileSelectBtn = new QPushButton(tr("Select files"));
        this->secondTab_additionalFileSelectBtn ->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        centralLayout->addWidget(this->secondTab_additionalFileSelectBtn, 1, 1, Qt::AlignRight);

        widgetLayout->addLayout(centralLayout);

        QHBoxLayout *controlButtonsLayout = new QHBoxLayout();
        controlButtonsLayout->setAlignment(Qt::AlignBottom);
        this->secondTab_backBtn = new QPushButton(tr("Back"));
        this->secondTab_backBtn->setIcon(QIcon(":/Icons/Res/Icon/arrow_left.ico"));
        this->secondTab_nextBtn = new QPushButton(tr("Next"));
        this->secondTab_nextBtn->setIcon(QIcon(":/Icons/Res/Icon/arrow_right.ico"));
        controlButtonsLayout->addWidget(this->secondTab_backBtn, 0, Qt::AlignLeft);
        controlButtonsLayout->addWidget(this->secondTab_nextBtn, 0, Qt::AlignRight);

        widgetLayout->addLayout(controlButtonsLayout);
    }
    // Third tab - DEB/control
    {
        this->thirdTab_Widget = new QWidget();
        this->mainWidget->addTab(this->thirdTab_Widget, tr("3. DEB/control"));

        QVBoxLayout *widgetLayout = new QVBoxLayout(this->thirdTab_Widget);
        QGridLayout *headerLayout = new QGridLayout();
        headerLayout->addWidget(new QLabel(tr("Select an existing file:")), 0, 0, Qt::AlignLeft);
        this->thirdTab_controlFile = new QLineEdit("");
        thirdTab_controlFile->setReadOnly(true);

        headerLayout->addWidget(this->thirdTab_controlFile, 1, 0);

        this->thirdTab_selectControlFileBtn = new QPushButton(tr("Select file"));
        this->thirdTab_selectControlFileBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        headerLayout->addWidget(this->thirdTab_selectControlFileBtn, 1, 1, Qt::AlignRight);
        this->thirdTab_clearControlFileBtn = new QPushButton(tr(""));
        this->thirdTab_clearControlFileBtn->setIcon(QIcon(":/Icons/Res/Icon/delete.ico"));
        headerLayout->addWidget(this->thirdTab_clearControlFileBtn, 1, 2, Qt::AlignRight);

        widgetLayout->addLayout(headerLayout);

        this->thirdTab_controlFileGB = new QGroupBox(tr("Control file data:"));
        this->thirdTab_controlFileGB->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        QGridLayout *controlFileGBLayout = new QGridLayout(thirdTab_controlFileGB);
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

        this->thirdTab_control_packageLE = new QLineEdit(tr(""));
        this->thirdTab_control_packageLE->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9-]+"), this));
        this->thirdTab_control_versionLE = new QLineEdit(tr(""));
        this->thirdTab_control_versionLE->setValidator(new QRegExpValidator(QRegExp("[0-9.]+"), this));
        this->thirdTab_control_priorityLE = new QLineEdit(tr(""));
        this->thirdTab_control_priorityLE->setValidator(new QRegExpValidator(QRegExp("[a-z]+"), this));
        this->thirdTab_control_sectionLE = new QLineEdit(tr(""));
        this->thirdTab_control_sectionLE->setValidator(new QRegExpValidator(QRegExp("[a-z]+"), this));
        this->thirdTab_control_maintainerTE = new QTextEdit(tr(""));
        this->thirdTab_control_installed_sizeLE = new QLineEdit(tr(""));
        this->thirdTab_control_installed_sizeLE->setValidator(new QRegExpValidator(QRegExp("[0-9]+"), this));
        this->thirdTab_control_dependsTE = new QTextEdit(tr(""));
        this->thirdTab_control_suggestsTE = new QTextEdit(tr(""));
        this->thirdTab_control_conflictsTE = new QTextEdit(tr(""));
        this->thirdTab_control_descriptionTE = new QTextEdit(tr(""));

        controlFileGBLayout->addWidget(this->thirdTab_control_packageLE, 0, 1);
        controlFileGBLayout->addWidget(this->thirdTab_control_versionLE, 1, 1);
        controlFileGBLayout->addWidget(this->thirdTab_control_priorityLE, 2, 1);
        controlFileGBLayout->addWidget(this->thirdTab_control_sectionLE, 3, 1);
        controlFileGBLayout->addWidget(this->thirdTab_control_maintainerTE, 4, 1);
        controlFileGBLayout->addWidget(this->thirdTab_control_installed_sizeLE, 5, 1);
        controlFileGBLayout->addWidget(this->thirdTab_control_dependsTE, 6, 1);
        controlFileGBLayout->addWidget(this->thirdTab_control_suggestsTE, 7, 1);
        controlFileGBLayout->addWidget(this->thirdTab_control_conflictsTE, 8, 1);
        controlFileGBLayout->addWidget(this->thirdTab_control_descriptionTE, 9, 1);

        widgetLayout->addWidget(this->thirdTab_controlFileGB);

        QHBoxLayout *controlButtonsLayout = new QHBoxLayout();
        controlButtonsLayout->setAlignment(Qt::AlignBottom);
        this->thirdTab_backBtn = new QPushButton(tr("Back"));
        this->thirdTab_backBtn->setIcon(QIcon(":/Icons/Res/Icon/arrow_left.ico"));
        this->thirdTab_nextBtn = new QPushButton(tr("Next"));
        this->thirdTab_nextBtn->setIcon(QIcon(":/Icons/Res/Icon/arrow_right.ico"));
        controlButtonsLayout->addWidget(this->thirdTab_backBtn, 0, Qt::AlignLeft);
        controlButtonsLayout->addWidget(this->thirdTab_nextBtn, 0, Qt::AlignRight);

        widgetLayout->addLayout(controlButtonsLayout);
    }
    // Fourth tab - DEB/scripts
    {
        this->fourthTab_Widget = new QWidget();
        this->mainWidget->addTab(this->fourthTab_Widget, tr("4. DEB/other"));

        QVBoxLayout *widgetLayout = new QVBoxLayout(this->fourthTab_Widget);
        QGridLayout *centralLayout = new QGridLayout();
        centralLayout->addWidget(new QLabel(tr("Preinst:")), 0, 0);
        centralLayout->addWidget(new QLabel(tr("Postinst:")), 1, 0);
        centralLayout->addWidget(new QLabel(tr("Prerm:")), 2, 0);
        centralLayout->addWidget(new QLabel(tr("Postrm:")), 3, 0);
        centralLayout->addWidget(new QLabel(tr("Menu:")), 4, 0);
        centralLayout->addWidget(new QLabel(tr("Changelog:")), 5, 0);

        this->fourthTab_preinstFilePathLE = new QLineEdit(tr(""));
        this->fourthTab_preinstFilePathLE->setReadOnly(true);
        this->fourthTab_postinstFilePathLE = new QLineEdit(tr(""));
        this->fourthTab_postinstFilePathLE->setReadOnly(true);
        this->fourthTab_prermFilePathLE = new QLineEdit(tr(""));
        this->fourthTab_prermFilePathLE->setReadOnly(true);
        this->fourthTab_postrmFilePathLE = new QLineEdit(tr(""));
        this->fourthTab_postrmFilePathLE->setReadOnly(true);
        this->foruthTab_menusFilePathLE = new QLineEdit(tr(""));
        this->foruthTab_menusFilePathLE->setReadOnly(true);
        this->foruthTab_changelogFilePathLE = new QLineEdit(tr(""));
        this->foruthTab_changelogFilePathLE->setReadOnly(true);

        centralLayout->addWidget(this->fourthTab_preinstFilePathLE, 0, 1);
        centralLayout->addWidget(this->fourthTab_postinstFilePathLE, 1, 1);
        centralLayout->addWidget(this->fourthTab_prermFilePathLE, 2, 1);
        centralLayout->addWidget(this->fourthTab_postrmFilePathLE, 3, 1);
        centralLayout->addWidget(this->foruthTab_menusFilePathLE, 4, 1);
        centralLayout->addWidget(this->foruthTab_changelogFilePathLE, 5, 1);

        this->fourthTab_preinstFileSelectBtn = new QPushButton(tr(""));
        this->fourthTab_preinstFileSelectBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        this->fourthTab_postinstFileSelectBtn = new QPushButton(tr(""));
        this->fourthTab_postinstFileSelectBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        this->fourthTab_prermFileSelectBtn = new QPushButton(tr(""));
        this->fourthTab_prermFileSelectBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        this->fourthTab_postrmFileSelectBtn = new QPushButton(tr(""));
        this->fourthTab_postrmFileSelectBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        this->foruthTab_menusFileSelectBtn = new QPushButton(tr(""));
        this->foruthTab_menusFileSelectBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        this->foruthTab_changelogFileSelectBtn = new QPushButton(tr(""));
        this->foruthTab_changelogFileSelectBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));

        centralLayout->addWidget(this->fourthTab_preinstFileSelectBtn, 0, 2);
        centralLayout->addWidget(this->fourthTab_postinstFileSelectBtn, 1, 2);
        centralLayout->addWidget(this->fourthTab_prermFileSelectBtn, 2, 2);
        centralLayout->addWidget(this->fourthTab_postrmFileSelectBtn, 3, 2);
        centralLayout->addWidget(this->foruthTab_menusFileSelectBtn, 4, 2);
        centralLayout->addWidget(this->foruthTab_changelogFileSelectBtn, 5, 2);

        this->fourthTab_preinstFileClearBtn = new QPushButton(tr(""));
        this->fourthTab_preinstFileClearBtn->setIcon(QIcon(":/Icons/Res/Icon/close.ico"));
        this->fourthTab_postinstFileClearBtn = new QPushButton(tr(""));
        this->fourthTab_postinstFileClearBtn->setIcon(QIcon(":/Icons/Res/Icon/close.ico"));
        this->fourthTab_prermFileClearBtn = new QPushButton(tr(""));
        this->fourthTab_prermFileClearBtn->setIcon(QIcon(":/Icons/Res/Icon/close.ico"));
        this->fourthTab_postrmFileClearBtn = new QPushButton(tr(""));
        this->fourthTab_postrmFileClearBtn->setIcon(QIcon(":/Icons/Res/Icon/close.ico"));
        this->foruthTab_menusFileClearBtn = new QPushButton(tr(""));
        this->foruthTab_menusFileClearBtn->setIcon(QIcon(":/Icons/Res/Icon/close.ico"));
        this->foruthTab_changelogFileClearBtn = new QPushButton(tr(""));
        this->foruthTab_changelogFileClearBtn->setIcon(QIcon(":/Icons/Res/Icon/close.ico"));

        centralLayout->addWidget(this->fourthTab_preinstFileClearBtn, 0, 3);
        centralLayout->addWidget(this->fourthTab_postinstFileClearBtn, 1, 3);
        centralLayout->addWidget(this->fourthTab_prermFileClearBtn, 2, 3);
        centralLayout->addWidget(this->fourthTab_postrmFileClearBtn, 3, 3);
        centralLayout->addWidget(this->foruthTab_menusFileClearBtn, 4, 3);
        centralLayout->addWidget(this->foruthTab_changelogFileClearBtn, 5, 3);


        widgetLayout->addLayout(centralLayout);

        QHBoxLayout *controlButtonsLayout = new QHBoxLayout();
        controlButtonsLayout->setAlignment(Qt::AlignBottom);
        this->fourthTab_backBtn = new QPushButton(tr("Back"));
        this->fourthTab_backBtn->setIcon(QIcon(":/Icons/Res/Icon/arrow_left.ico"));
        this->fourthTab_nextBtn = new QPushButton(tr("Next"));
        this->fourthTab_nextBtn->setIcon(QIcon(":/Icons/Res/Icon/arrow_right.ico"));
        controlButtonsLayout->addWidget(this->fourthTab_backBtn, 0, Qt::AlignLeft);
        controlButtonsLayout->addWidget(this->fourthTab_nextBtn, 0, Qt::AlignRight);

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
    connect(this->secondTab_additionalFileSelectBtn, &QPushButton::clicked, this, &MainWindow::slot_secondTab_additionalFileSelectBtn_clicked);
    connect(this->secondTab_backBtn, &QPushButton::clicked, this, &MainWindow::slot_secondTab_backBtn_clicked);
    connect(this->secondTab_nextBtn, &QPushButton::clicked, this, &MainWindow::slot_secondTab_nextBtn_clicked);

    // Connect third tab widgets to their slots
    connect(this->thirdTab_backBtn, &QPushButton::clicked, this, &MainWindow::slot_thirdTab_backBtn_clicked);
    connect(this->thirdTab_nextBtn, &QPushButton::clicked, this, &MainWindow::slot_thirdTab_nextBtn_clicked);

    // Connect fourth tab widgets to thier slots
    connect(this->fourthTab_backBtn, &QPushButton::clicked, this, &MainWindow::slot_fourthTab_backBtn_clicked);
    connect(this->fourthTab_nextBtn, &QPushButton::clicked, this, &MainWindow::slot_fourthTab_nextBtn_clicked);

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

// Second tab slots
void MainWindow::slot_secondTab_additionalFileSelectBtn_clicked()
{
    QStringList additionalFiles = QFileDialog::getOpenFileNames(this, tr("Select additional files"));

    if (additionalFiles.isEmpty()) {
        return;
    }
}

void MainWindow::slot_secondTab_backBtn_clicked()
{
    this->mainWidget->setCurrentIndex(this->mainWidget->indexOf(this->firstTab_Widget));
}

void MainWindow::slot_secondTab_nextBtn_clicked()
{
    /*if (this->secondTab_packageName->text().trimmed().isEmpty())
        return;

    //this->mainWidget->setCurrentIndex(this->mainWidget->indexOf(this->thirdTab_Widget));
    getDependnciesForElf(this->firstTab_filePath->text().trimmed());
    */
}

// Third tab slots
void MainWindow::slot_thirdTab_backBtn_clicked()
{
    this->mainWidget->setCurrentIndex(this->mainWidget->indexOf(this->secondTab_Widget));
}

void MainWindow::slot_thirdTab_nextBtn_clicked()
{

}

// Fourth tab slots
void MainWindow::slot_fourthTab_preinstFileSelectBtn_clicked()
{

}

void MainWindow::slot_fourthTab_postinstFileSelectBtn_clicked()
{

}

void MainWindow::slot_fourthTab_prermFileSelectBtn_clicked()
{

}

void MainWindow::slot_fourthTab_postrmFileSelectBtn_clicked()
{

}

void MainWindow::slot_fourthTab_backBtn_clicked()
{

}

void MainWindow::slot_fourthTab_nextBtn_clicked()
{

}
