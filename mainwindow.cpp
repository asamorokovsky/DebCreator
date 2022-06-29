#include "mainwindow.h"

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

    // Select executable file & additional files
    {
        this->firstTab_Widget = new QWidget();
        QVBoxLayout *widgetLayout = new QVBoxLayout(this->firstTab_Widget);

        QGridLayout *centralLayout = new QGridLayout();
        centralLayout->setAlignment(Qt::AlignTop);
        centralLayout->addWidget(new QLabel(tr("1. Please select executable file:")), 0, 0);
        this->firstTab_filePath = new QLineEdit("");
        this->firstTab_filePath->setReadOnly(true);
        centralLayout->addWidget(this->firstTab_filePath, 1, 0);
        this->firstTab_filePathSelectBtn = new QPushButton(tr("Select file"));
        this->firstTab_filePathSelectBtn ->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        centralLayout->addWidget(this->firstTab_filePathSelectBtn, 1, 1);

        centralLayout->addWidget(new QLabel(tr("2. Please select additional files:")), 2, 0);
        this->firstTab_additionalFilesLE = new QLineEdit(tr(""));
        this->firstTab_additionalFilesLE->setReadOnly(true);
        centralLayout->addWidget(this->firstTab_additionalFilesLE, 3, 0);
        this->firstTab_additionalFileSelectBtn = new QPushButton(tr("Select files"));
        this->firstTab_additionalFileSelectBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        centralLayout->addWidget(this->firstTab_additionalFileSelectBtn, 3, 1, Qt::AlignRight);
        this->firstTab_additionalFileClearBtn = new QPushButton(tr(""));
        this->firstTab_additionalFileClearBtn->setIcon(QIcon(":/Icons/Res/Icon/delete.ico"));
        centralLayout->addWidget(this->firstTab_additionalFileClearBtn, 3, 2, Qt::AlignRight);

        widgetLayout->addLayout(centralLayout);

        QVBoxLayout *installPathLayout = new QVBoxLayout();
        installPathLayout->setAlignment(Qt::AlignTop);
        installPathLayout->addWidget(new QLabel(tr("3. Please enter installation path:")));
        this->firstTab_installationPathLE = new QLineEdit(tr(""));
        this->firstTab_installationPathLE->setValidator(new QRegExpValidator(QRegExp("/[a-zA-Z0-9-/()]+"), this));
        installPathLayout->addWidget(this->firstTab_installationPathLE);

        widgetLayout->addLayout(installPathLayout);

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

    // DEB/control tab
    {
        this->secondTab_Widget = new QWidget();
        this->mainWidget->addTab(this->secondTab_Widget, tr("2. DEB/control"));

        QVBoxLayout *widgetLayout = new QVBoxLayout(this->secondTab_Widget);
        QGridLayout *headerLayout = new QGridLayout();
        headerLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        headerLayout->addWidget(new QLabel(tr("Select an existing file:")), 0, 0);
        this->secondTab_controlFile = new QLineEdit("");
        secondTab_controlFile->setReadOnly(true);

        headerLayout->addWidget(this->secondTab_controlFile, 1, 0);

        this->secondTab_selectControlFileBtn = new QPushButton(tr("Select file"));
        this->secondTab_selectControlFileBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        headerLayout->addWidget(this->secondTab_selectControlFileBtn, 1, 1, Qt::AlignRight);
        this->secondTab_clearControlFileBtn = new QPushButton(tr(""));
        this->secondTab_clearControlFileBtn->setIcon(QIcon(":/Icons/Res/Icon/delete.ico"));
        headerLayout->addWidget(this->secondTab_clearControlFileBtn, 1, 2, Qt::AlignRight);

        widgetLayout->addLayout(headerLayout);

        QScrollArea *scrollArea = new QScrollArea();
        scrollArea->setWidgetResizable(true);

        this->secondTab_controlFileGB = new QGroupBox(tr("Control file data:"));
        this->secondTab_controlFileGB->setFlat(true);
        this->secondTab_controlFileGB->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        QGridLayout *controlFileGBLayout = new QGridLayout(this->secondTab_controlFileGB);
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

        controlFileGBLayout->addWidget(this->secondTab_control_packageLE, 0, 1, Qt::AlignTop);
        controlFileGBLayout->addWidget(this->secondTab_control_versionLE, 1, 1, Qt::AlignTop);
        controlFileGBLayout->addWidget(this->secondTab_control_priorityLE, 2, 1, Qt::AlignTop);
        controlFileGBLayout->addWidget(this->secondTab_control_sectionLE, 3, 1, Qt::AlignTop);
        controlFileGBLayout->addWidget(this->secondTab_control_maintainerTE, 4, 1, Qt::AlignTop);
        controlFileGBLayout->addWidget(this->secondTab_control_installed_sizeLE, 5, 1, Qt::AlignTop);
        controlFileGBLayout->addWidget(this->secondTab_control_dependsTE, 6, 1, Qt::AlignTop);
        controlFileGBLayout->addWidget(this->secondTab_control_suggestsTE, 7, 1, Qt::AlignTop);
        controlFileGBLayout->addWidget(this->secondTab_control_conflictsTE, 8, 1, Qt::AlignTop);
        controlFileGBLayout->addWidget(this->secondTab_control_descriptionTE, 9, 1, Qt::AlignTop);

        scrollArea->setWidget(this->secondTab_controlFileGB);

        widgetLayout->addWidget(scrollArea);

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
    // DEB/scripts tab
    {
        this->thirdTab_Widget = new QWidget();
        this->mainWidget->addTab(this->thirdTab_Widget, tr("3. DEB/other"));

        QVBoxLayout *widgetLayout = new QVBoxLayout(this->thirdTab_Widget);
        QGridLayout *centralLayout = new QGridLayout();
        centralLayout->addWidget(new QLabel(tr("Select preinst script file:")), 0, 0);
        centralLayout->addWidget(new QLabel(tr("Select postinst script file:")), 2, 0);
        centralLayout->addWidget(new QLabel(tr("Select prerm script file:")), 4, 0);
        centralLayout->addWidget(new QLabel(tr("Select postrm script file:")), 6, 0);
        centralLayout->addWidget(new QLabel(tr("Select menu file:")), 8, 0);
        centralLayout->addWidget(new QLabel(tr("Select changelog file:")), 10, 0);

        this->thirdTab_preinstFilePathLE = new QLineEdit(tr(""));
        this->thirdTab_preinstFilePathLE->setReadOnly(true);
        this->thirdTab_postinstFilePathLE = new QLineEdit(tr(""));
        this->thirdTab_postinstFilePathLE->setReadOnly(true);
        this->thirdTab_prermFilePathLE = new QLineEdit(tr(""));
        this->thirdTab_prermFilePathLE->setReadOnly(true);
        this->thirdTab_postrmFilePathLE = new QLineEdit(tr(""));
        this->thirdTab_postrmFilePathLE->setReadOnly(true);
        this->thirdTab_menusFilePathLE = new QLineEdit(tr(""));
        this->thirdTab_menusFilePathLE->setReadOnly(true);
        this->thirdTab_changelogFilePathLE = new QLineEdit(tr(""));
        this->thirdTab_changelogFilePathLE->setReadOnly(true);

        centralLayout->addWidget(this->thirdTab_preinstFilePathLE, 1, 0);
        centralLayout->addWidget(this->thirdTab_postinstFilePathLE, 3, 0);
        centralLayout->addWidget(this->thirdTab_prermFilePathLE, 5, 0);
        centralLayout->addWidget(this->thirdTab_postrmFilePathLE, 7, 0);
        centralLayout->addWidget(this->thirdTab_menusFilePathLE, 9, 0);
        centralLayout->addWidget(this->thirdTab_changelogFilePathLE, 11, 0);

        this->thirdTab_preinstFileSelectBtn = new QPushButton(tr(""));
        this->thirdTab_preinstFileSelectBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        this->thirdTab_postinstFileSelectBtn = new QPushButton(tr(""));
        this->thirdTab_postinstFileSelectBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        this->thirdTab_prermFileSelectBtn = new QPushButton(tr(""));
        this->thirdTab_prermFileSelectBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        this->thirdTab_postrmFileSelectBtn = new QPushButton(tr(""));
        this->thirdTab_postrmFileSelectBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        this->thirdTab_menusFileSelectBtn = new QPushButton(tr(""));
        this->thirdTab_menusFileSelectBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));
        this->thirdTab_changelogFileSelectBtn = new QPushButton(tr(""));
        this->thirdTab_changelogFileSelectBtn->setIcon(QIcon(":/Icons/Res/Icon/add.ico"));

        centralLayout->addWidget(this->thirdTab_preinstFileSelectBtn, 1, 1);
        centralLayout->addWidget(this->thirdTab_postinstFileSelectBtn, 3, 1);
        centralLayout->addWidget(this->thirdTab_prermFileSelectBtn, 5, 1);
        centralLayout->addWidget(this->thirdTab_postrmFileSelectBtn, 7, 1);
        centralLayout->addWidget(this->thirdTab_menusFileSelectBtn, 9, 1);
        centralLayout->addWidget(this->thirdTab_changelogFileSelectBtn, 11, 1);

        this->thirdTab_preinstFileClearBtn = new QPushButton(tr(""));
        this->thirdTab_preinstFileClearBtn->setIcon(QIcon(":/Icons/Res/Icon/close.ico"));
        this->thirdTab_postinstFileClearBtn = new QPushButton(tr(""));
        this->thirdTab_postinstFileClearBtn->setIcon(QIcon(":/Icons/Res/Icon/close.ico"));
        this->thirdTab_prermFileClearBtn = new QPushButton(tr(""));
        this->thirdTab_prermFileClearBtn->setIcon(QIcon(":/Icons/Res/Icon/close.ico"));
        this->thirdTab_postrmFileClearBtn = new QPushButton(tr(""));
        this->thirdTab_postrmFileClearBtn->setIcon(QIcon(":/Icons/Res/Icon/close.ico"));
        this->thirdTab_menusFileClearBtn = new QPushButton(tr(""));
        this->thirdTab_menusFileClearBtn->setIcon(QIcon(":/Icons/Res/Icon/close.ico"));
        this->thirdTab_changelogFileClearBtn = new QPushButton(tr(""));
        this->thirdTab_changelogFileClearBtn->setIcon(QIcon(":/Icons/Res/Icon/close.ico"));

        centralLayout->addWidget(this->thirdTab_preinstFileClearBtn, 1, 2);
        centralLayout->addWidget(this->thirdTab_postinstFileClearBtn, 3, 2);
        centralLayout->addWidget(this->thirdTab_prermFileClearBtn, 5, 2);
        centralLayout->addWidget(this->thirdTab_postrmFileClearBtn, 7, 2);
        centralLayout->addWidget(this->thirdTab_menusFileClearBtn, 9, 2);
        centralLayout->addWidget(this->thirdTab_changelogFileClearBtn, 11, 2);

        widgetLayout->addLayout(centralLayout);

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
    this->setCentralWidget(this->mainWidget);
}

void MainWindow::connectUI()
{
    // Connect first tab widgets to their slots
    connect(this->firstTab_filePathSelectBtn, &QPushButton::clicked, this, &MainWindow::slot_firstTab_filePathSelectBtn_clicked);
    connect(this->firstTab_additionalFileSelectBtn, &QPushButton::clicked, this, &MainWindow::slot_firstTab_additionalFileSelectBtn_clicked);
    connect(this->firstTab_quitBtn, &QPushButton::clicked, this, &MainWindow::slot_firstTab_quitBtn_clicked);
    connect(this->firstTab_nextBtn, &QPushButton::clicked, this, &MainWindow::slot_firstTab_nextBtn_clicked);

    // Connect second tab widgets to their slots
    connect(this->secondTab_selectControlFileBtn, &QPushButton::clicked, this, &MainWindow::slot_secondTab_selectControlFileBtn_clicked);
    connect(this->secondTab_backBtn, &QPushButton::clicked, this, &MainWindow::slot_secondTab_backBtn_clicked);
    connect(this->secondTab_nextBtn, &QPushButton::clicked, this, &MainWindow::slot_secondTab_nextBtn_clicked);

    // Connect third tab widgets to thier slots
    connect(this->thirdTab_backBtn, &QPushButton::clicked, this, &MainWindow::slot_thirdTab_backBtn_clicked);
    connect(this->thirdTab_nextBtn, &QPushButton::clicked, this, &MainWindow::slot_thirdTab_nextBtn_clicked);

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
QList<LibraryPackage> MainWindow::getDependnciesForElf(QString filePath)
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

void MainWindow::slot_firstTab_additionalFileSelectBtn_clicked()
{
    QStringList additionalFiles = QFileDialog::getOpenFileNames(this, tr("Select additional files"));

    if (additionalFiles.isEmpty()) {
        return;
    }
}

void MainWindow::slot_firstTab_quitBtn_clicked()
{
    close();
}

void MainWindow::slot_firstTab_nextBtn_clicked()
{
    if (this->firstTab_filePath->text().trimmed().isEmpty() && this->firstTab_installationPathLE->text().trimmed().isEmpty())
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
void MainWindow::slot_secondTab_selectControlFileBtn_clicked()
{
    QString filter = "control";
    QString selectedFile = QFileDialog::getOpenFileName(this, tr("Select file"), QString(), QString(), &filter);
    if (selectedFile.isEmpty())
        return;

    this->secondTab_controlFile->setText(selectedFile);


    QPair<bool, DebControlFile*> result = DebControlFile::fromFile(this->secondTab_controlFile->text().trimmed());
    if (result.first) {
        DebControlFile *controlFile = result.second;

        this->secondTab_control_packageLE->setText(controlFile->getPackage());
        this->secondTab_control_versionLE->setText(controlFile->getVersion());
        this->secondTab_control_priorityLE->setText(controlFile->getPriority());
        this->secondTab_control_sectionLE->setText(controlFile->getSection());
        this->secondTab_control_maintainerTE->setText(controlFile->getMaintainer());
        this->secondTab_control_installed_sizeLE->setText(QString::number(controlFile->getInstalledSize()));

        QList<LibraryPackage> dependPackages = controlFile->getDependPackages();
        for (int currentIndex = 0; currentIndex < dependPackages.size(); currentIndex++) {
            LibraryPackage libPackage = dependPackages.at(currentIndex);
            QString strToInsert = libPackage.getName();
            if (!libPackage.getVersion().isEmpty())
                strToInsert.append(QString(" (%1)").arg(libPackage.getVersion()));
            if (currentIndex != dependPackages.size()-1)
                strToInsert.append(", ");
            this->secondTab_control_dependsTE->insertPlainText(strToInsert);
        }

        QList<LibraryPackage> suggestsPackages = controlFile->getSuggestPackages();
        for (int currentIndex = 0; currentIndex < suggestsPackages.size(); currentIndex++) {
            LibraryPackage libPackage = dependPackages.at(currentIndex);
            QString strToInsert = libPackage.getName();
            if (!libPackage.getVersion().isEmpty())
                strToInsert.append(QString(" (%1)").arg(libPackage.getVersion()));
            if (currentIndex != suggestsPackages.size()-1)
                strToInsert.append(", ");
            this->secondTab_control_suggestsTE->insertPlainText(strToInsert);
        }

        QList<LibraryPackage> conflictPackages = controlFile->getConflictPackages();
        for (int currentIndex = 0; currentIndex < conflictPackages.size(); currentIndex++) {
            LibraryPackage libPackage = conflictPackages.at(currentIndex);
            QString strToInsert = libPackage.getName();
            if (!libPackage.getVersion().isEmpty())
                strToInsert.append(QString(" (%1)").arg(libPackage.getVersion()));
            if (currentIndex != conflictPackages.size()-1)
                strToInsert.append(", ");
            this->secondTab_control_conflictsTE->insertPlainText(strToInsert);
        }
        this->secondTab_control_descriptionTE->setText(controlFile->getDescription());
    }
}

void MainWindow::slot_secondTab_backBtn_clicked()
{
    this->mainWidget->setCurrentIndex(this->mainWidget->indexOf(this->secondTab_Widget));
}

void MainWindow::slot_secondTab_nextBtn_clicked()
{

}

// Third tab slots
void MainWindow::slot_thirdTab_preinstFileSelectBtn_clicked()
{

}

void MainWindow::slot_thirdTab_postinstFileSelectBtn_clicked()
{

}

void MainWindow::slot_thirdTab_prermFileSelectBtn_clicked()
{

}

void MainWindow::slot_thirdTab_postrmFileSelectBtn_clicked()
{

}

void MainWindow::slot_thirdTab_backBtn_clicked()
{

}

void MainWindow::slot_thirdTab_nextBtn_clicked()
{

}
