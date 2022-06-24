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
    QLineEdit *secondTab_controlFile;

    QGroupBox *secondTab_controlFileGB;
    QLineEdit *secondTab_control_packageLE;
    QLineEdit *secondTab_control_versionLE;
    QLineEdit *secondTab_control_priorityLE;
    QLineEdit *secondTab_control_sectionLE;
    QTextEdit *secondTab_control_maintainerTE;
    QLineEdit *secondTab_control_installed_sizeLE;
    QTextEdit *secondTab_control_dependsTE;
    QTextEdit *secondTab_control_suggestsTE;
    QTextEdit *secondTab_control_conflictsTE;
    QTextEdit *secondTab_control_descriptionTE;



    QPushButton *secondTab_selectControlFileBtn;
    QPushButton *secondTab_backBtn;
    QPushButton *secondTab_nextBtn;



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
    void slot_secondTab_backBtn_clicked();
    void slot_secondTab_nextBtn_clicked();

};

#endif // MAINWINDOW_H