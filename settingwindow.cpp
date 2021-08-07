#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QFont>
#include <QMessageBox>
#include <QDebug>

SettingWindow::SettingWindow(std::map<QString,QString>& settingMap, QWidget *parent) :
    QDialog(parent),settingMap(settingMap),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    ui->fontSize->setValue(settingMap["font-size"].toInt());
    ui->fontComboBox->setCurrentText(settingMap["font-family"]);
    ui->colorTheme->setCurrentText(settingMap["color-theme"]);
    if(settingMap["wrap-mode"] == "On")
        ui->wrapMode->setCurrentText("вкл");
    else
        ui->wrapMode->setCurrentText("выкл");
    if((settingMap["syntax-highlighting"]) == "No")
        ui->syntax->setCurrentText("обычный текст");
    else
        ui->syntax->setCurrentText(settingMap["syntax-highlighting"]);

    ui->fontSize->setMinimum(12);
}

SettingWindow::~SettingWindow()
{
    delete ui;
}

void SettingWindow::on_fontSize_valueChanged(int arg1)
{
    if(arg1 >= 12 && arg1 <= 50)
        settingMap["font-size"] = QString::number(arg1);
}

void SettingWindow::on_fontComboBox_currentTextChanged(const QString &arg1)
{
    settingMap["font-family"] = arg1;
}

void SettingWindow::on_colorTheme_currentTextChanged(const QString &arg1)
{
    settingMap["color-theme"] = arg1;
}

void SettingWindow::on_syntax_currentTextChanged(const QString &arg1)
{
    if(arg1 == "обычный текст")
        settingMap["syntax-highlighting"] = "No";
    else
        settingMap["syntax-highlighting"] = arg1;
}

void SettingWindow::on_wrapMode_currentTextChanged(const QString &arg1)
{
    if(arg1 == "вкл")
        settingMap["wrap-mode"] = "On";
    else
        settingMap["wrap-mode"] = "Off";
}
