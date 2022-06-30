#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QFileDialog>
#include <QPushButton>
#include <QProcess>
#include <QMessageBox>
#include <QGroupBox>
#include <QScrollArea>
#include <QComboBox>
#include <QCheckBox>
#include <QDir>

#include <QRegExp>
#include <QRegExpValidator>

#include <QFileInfo>

#include <QDebug>

#include "debcontrolfile.h"
#include "debpackage.h"

#include "utils.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTabWidget *mainWidget;

    // First tab widgets
    QWidget *firstTab_Widget;
    QLineEdit *firstTab_filePath;
    QLineEdit *firstTab_additionalFilesLE;
    QLineEdit *firstTab_installationPathLE;

    QPushButton *firstTab_filePathSelectBtn;
    QPushButton *firstTab_additionalFileSelectBtn;
    QPushButton *firstTab_additionalFileClearBtn;
    QPushButton *firstTab_quitBtn;
    QPushButton *firstTab_nextBtn;

    // Second tab widgets
    QWidget *secondTab_Widget;
    QLineEdit *secondTab_controlFile;

    QGroupBox *secondTab_controlFileGB;

    QLineEdit *secondTab_control_packageLE;
    QLineEdit *secondTab_control_versionLE;
    QLineEdit *secondTab_control_architectureLE;
    QLineEdit *secondTab_control_maintainerLE;
    QTextEdit *secondTab_control_descriptionTE;

    QLineEdit *secondTab_control_sectionLE;
    QComboBox *secondTab_control_priorityCB;

    QCheckBox *econdTab_control_essentialCB;
    QLineEdit *secondTab_control_sourceLE;
    QTextEdit *secondTab_control_dependsTE;
    QTextEdit *secondTab_control_pre_dependsTE;
    QTextEdit *secondTab_control_recommendsTE;
    QTextEdit *secondTab_control_suggestsTE;
    QTextEdit *secondTab_control_breaksTE;
    QTextEdit *secondTab_control_conflictsTE;
    QTextEdit *secondTab_control_replacesTE;
    QTextEdit *secondTab_control_providesTE;
    QTextEdit *secondTab_control_builtUsingTE;

    QLineEdit *secondTab_control_installedSizeLE;
    QLineEdit *secondTab_control_homepageLE;


    QPushButton *secondTab_selectControlFileBtn;
    QPushButton *secondTab_clearControlFileBtn;
    QPushButton *secondTab_backBtn;
    QPushButton *secondTab_nextBtn;

    // Third tab widgets
    QWidget *thirdTab_Widget;
    QLineEdit *thirdTab_preinstFilePathLE;
    QLineEdit *thirdTab_postinstFilePathLE;
    QLineEdit *thirdTab_prermFilePathLE;
    QLineEdit *thirdTab_postrmFilePathLE;
    QLineEdit *thirdTab_menusFilePathLE;
    QLineEdit *thirdTab_changelogFilePathLE;

    QPushButton *thirdTab_preinstFileSelectBtn;
    QPushButton *thirdTab_postinstFileSelectBtn;
    QPushButton *thirdTab_prermFileSelectBtn;
    QPushButton *thirdTab_postrmFileSelectBtn;
    QPushButton *thirdTab_menusFileSelectBtn;
    QPushButton *thirdTab_changelogFileSelectBtn;
    QPushButton *thirdTab_preinstFileClearBtn;
    QPushButton *thirdTab_postinstFileClearBtn;
    QPushButton *thirdTab_prermFileClearBtn;
    QPushButton *thirdTab_postrmFileClearBtn;
    QPushButton *thirdTab_menusFileClearBtn;
    QPushButton *thirdTab_changelogFileClearBtn;

    QPushButton *thirdTab_backBtn;
    QPushButton *thirdTab_nextBtn;

    void createUI();
    void connectUI();

private slots:
    // First tab slots
    void slot_firstTab_filePathSelectBtn_clicked();
    void slot_firstTab_additionalFileSelectBtn_clicked();
    void slot_firstTab_additionalFileClearBtn_clicked();
    void slot_firstTab_quitBtn_clicked();
    void slot_firstTab_nextBtn_clicked();

    // Second tab slots
    void slot_secondTab_selectControlFileBtn_clicked();
    void slot_secondTab_clearControlFileBtn_clicked();
    void slot_secondTab_backBtn_clicked();
    void slot_secondTab_nextBtn_clicked();

    // Third tab slots
    void slot_thirdTab_preinstFileSelectBtn_clicked();
    void slot_thirdTab_postinstFileSelectBtn_clicked();
    void slot_thirdTab_prermFileSelectBtn_clicked();
    void slot_thirdTab_postrmFileSelectBtn_clicked();
    void slot_thirdTab_menusFileSelectBtn_clicked();
    void slot_thirdTab_changelogFileSelectBtn_clicked();

    void slot_thirdTab_preinstFileClearBtn_clicked();
    void slot_thirdTab_postinstFileClearBtn_clicked();
    void slot_thirdTab_prermFileClearBtn_clicked();
    void slot_thirdTab_postrmFileClearBtn_clicked();
    void slot_thirdTab_menusFileClearBtn_clicked();
    void slot_thirdTab_changelogFileClearBtn_clicked();

    void slot_thirdTab_backBtn_clicked();
    void slot_thirdTab_nextBtn_clicked();
};

#endif // MAINWINDOW_H
