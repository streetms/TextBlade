#pragma once

#include <QDialog>
#include <map>
#include <QString>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingWindow(std::map<QString,QString>&,double factor,QWidget *parent = 0);
    ~SettingWindow();

private slots:
    void on_fontSize_valueChanged(int arg1);
    void on_fontComboBox_currentTextChanged(const QString &arg1);
    void on_colorTheme_currentTextChanged(const QString &arg1);
    void on_syntax_currentTextChanged(const QString &arg1);
    void on_wrapMode_currentTextChanged(const QString &arg1);

private:
    std::map<QString,QString>& settingMap;

    Ui::SettingWindow *ui;
};
