#pragma once
#include <QMainWindow>
#include <QCloseEvent>
#include <map>
#include <QTextCursor>
#include "file.h"
#include "mysyntax.h"
#include "settingwindow.h"
#include <QList>
#include <QSignalMapper>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QString& FileName, QWidget *parent = nullptr);
    ~MainWindow();

    void closePair(QTextCursor&, char ch);
    void closeEvent(QCloseEvent *event);
    void setColorTheme(const QString& );
    void readSettingFile(QFile& fin);
    void createSettingFile(QFile& fin);

    Ui::MainWindow *ui;

private slots:
    void on_save_triggered();
    void on_setting_triggered();
    void on_open_triggered();
    void on_create_triggered();
    void on_save_as_triggered();
    void on_exit_triggered();
    void on_reset_triggered();
    void on_findEdit_returnPressed();
    void on_aboutQt_triggered();
    void on_findText_triggered();
    void on_up_triggered();
    void on_down_triggered();
    void on_textEdit_textChanged();

private:    
    int charCount;
    double factor;
    MySyntax* syntax = nullptr;
    SettingWindow* settingWindow;
    std::map<QString,QString> settingMap;

    QString fileType;
    QString settingFile;

    File file;

};
