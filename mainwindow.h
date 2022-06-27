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

#include <QRegExp>
#include <QRegExpValidator>

#include <QDebug>


class Package {

public:
    Package(QString name, QString version);

    QString getName();
    QString getVersion();

private:
    QString _name;
    QString _version;
};

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
    QPushButton *firstTab_filePathSelectBtn;
    QPushButton *firstTab_quitBtn;
    QPushButton *firstTab_nextBtn;

    // Second tab widgets
    QWidget *secondTab_Widget;
    QLineEdit *secondTab_additionalFilesLE;
    QPushButton *secondTab_additionalFileSelectBtn;

    QPushButton *secondTab_backBtn;
    QPushButton *secondTab_nextBtn;

    // Thirtd tab widgets
    QWidget *thirdTab_Widget;
    QLineEdit *thirdTab_controlFile;

    QGroupBox *thirdTab_controlFileGB;
    QLineEdit *thirdTab_control_packageLE;
    QLineEdit *thirdTab_control_versionLE;
    QLineEdit *thirdTab_control_priorityLE;
    QLineEdit *thirdTab_control_sectionLE;
    QTextEdit *thirdTab_control_maintainerTE;
    QLineEdit *thirdTab_control_installed_sizeLE;
    QTextEdit *thirdTab_control_dependsTE;
    QTextEdit *thirdTab_control_suggestsTE;
    QTextEdit *thirdTab_control_conflictsTE;
    QTextEdit *thirdTab_control_descriptionTE;

    QPushButton *thirdTab_selectControlFileBtn;
    QPushButton *thirdTab_clearControlFileBtn;
    QPushButton *thirdTab_backBtn;
    QPushButton *thirdTab_nextBtn;

    // Fourth tab widgets
    QWidget *fourthTab_Widget;
    QLineEdit *fourthTab_preinstFilePathLE;
    QLineEdit *fourthTab_postinstFilePathLE;
    QLineEdit *fourthTab_prermFilePathLE;
    QLineEdit *fourthTab_postrmFilePathLE;
    QLineEdit *foruthTab_menusFilePathLE;
    QLineEdit *foruthTab_changelogFilePathLE;

    QPushButton *fourthTab_preinstFileSelectBtn;
    QPushButton *fourthTab_postinstFileSelectBtn;
    QPushButton *fourthTab_prermFileSelectBtn;
    QPushButton *fourthTab_postrmFileSelectBtn;
    QPushButton *foruthTab_menusFileSelectBtn;
    QPushButton *foruthTab_changelogFileSelectBtn;
    QPushButton *fourthTab_preinstFileClearBtn;
    QPushButton *fourthTab_postinstFileClearBtn;
    QPushButton *fourthTab_prermFileClearBtn;
    QPushButton *fourthTab_postrmFileClearBtn;
    QPushButton *foruthTab_menusFileClearBtn;
    QPushButton *foruthTab_changelogFileClearBtn;

    QPushButton *fourthTab_backBtn;
    QPushButton *fourthTab_nextBtn;



    void createUI();
    void connectUI();

    bool isFileElf(QString filePath);
    QList<Package> getDependnciesForElf(QString filePath);

private slots:
    // First tab slots
    void slot_firstTab_filePathSelectBtn_clicked();
    void slot_firstTab_quitBtn_clicked();
    void slot_firstTab_nextBtn_clicked();

    // Second tab slots

    void slot_secondTab_additionalFileSelectBtn_clicked();
    void slot_secondTab_backBtn_clicked();
    void slot_secondTab_nextBtn_clicked();

    // Third tab slots
    void slot_thirdTab_backBtn_clicked();
    void slot_thirdTab_nextBtn_clicked();

    // Fourth tab slots
    void slot_fourthTab_preinstFileSelectBtn_clicked();
    void slot_fourthTab_postinstFileSelectBtn_clicked();
    void slot_fourthTab_prermFileSelectBtn_clicked();
    void slot_fourthTab_postrmFileSelectBtn_clicked();

    void slot_fourthTab_backBtn_clicked();
    void slot_fourthTab_nextBtn_clicked();


};

#endif // MAINWINDOW_H
