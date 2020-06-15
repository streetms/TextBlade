#include "mainwindow.h"
#include <iostream>
#include <map>
#include "ui_mainwindow.h"
#include "settingwindow.h"
#include <QMessageBox>
#include <QString>
#include <iostream>
#include <QTextEdit>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextCursor>
#include <iostream>
MainWindow::MainWindow(QString& fileName , QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QFile fin;
    settingMap.emplace(std::make_pair("font-size",""));
    settingMap.emplace(std::make_pair("font-family",""));
    settingMap.emplace(std::make_pair("color-theme",""));
    settingFile =  QCoreApplication::applicationDirPath()+"/setting.dat";
    fin.setFileName(settingFile);
    ui->setupUi(this);
    this->setWindowTitle("Text Blade");
    if(!fin.open(QIODevice::ReadOnly))
    {
        fin.open(QIODevice::WriteOnly);
        fin.close();
    }
    else
    {
        QTextStream input;
        QString temp;
        input.setDevice(&fin);
        input >> temp;
        input >> settingMap["font-size"];
        input >> temp;
        settingMap["font-family"] = input.readLine();
        input >> temp;
        input >> settingMap["color-theme"];
        input >> temp;
    }
    QFont font;
    font.setFamily(settingMap["font-family"]);
    font.setPixelSize(settingMap["font-size"].toInt());
    font.setBold(ui->textEdit->font().bold());
    ui->textEdit->setFont(font);
    setColorTheme(settingMap["color-theme"]);
    fin.close();
    if(!fileName.isEmpty())
    {
        file.open(fileName);
        ui->textEdit->setText(file.getText());
        file.save(ui->textEdit->toPlainText());
        setWindowTitle("Text Blade - " + file.getFileName());
    }
    setWindowTitle("Text Blade - " + file.getFileName());
}
MainWindow::~MainWindow()
{
    QFile fout;
    fout.setFileName(settingFile);
    fout.open(QIODevice::WriteOnly);
    QTextStream output;
    output.setDevice(&fout);
    output << "font-size: " + settingMap["font-size"] + "\n";
    output << "font-family: " + settingMap["font-family"] + "\n";
    output << "color-theme: " + settingMap["color-theme"] + "\n";
    fout.close();
    delete ui;
}

void MainWindow::on_save_triggered()
{
    if(file.isExist())
        file.save(ui->textEdit->toPlainText());
    else
        on_save_as_triggered();
    setWindowTitle("Text Blade - " + file.getFileName());
}

void MainWindow::on_setting_triggered()
{
    SettingWindow settingWindow(settingMap);
    settingWindow.setModal(true);
    settingWindow.exec();
    QFont font;
    font.setFamily(settingMap["font-family"]);
    font.setPixelSize(settingMap["font-size"].toInt());
    font.setBold(ui->textEdit->font().bold());
    ui->textEdit->setFont(font);
    setColorTheme(settingMap["color-theme"]);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
        QMessageBox quit(
        QMessageBox::Question,
        "Text Blade",
        "",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel ,
        this);
        int answer = -200;
        if(!file.isExist() && !ui->textEdit->toPlainText().isEmpty())
        {
            quit.setText("создать новый файл?");
            quit.setButtonText(QMessageBox::Yes, "создать");
            quit.setButtonText(QMessageBox::No, "выход");
            quit.setButtonText(QMessageBox::Cancel,"отмена");
            answer = quit.exec();
        }
        if(!file.isConserved() && ui->textEdit->toPlainText().isEmpty())
        {
            quit.setText("Сохранить изменения в файле " +file.getPath() + "?");
            quit.setButtonText(QMessageBox::Yes, "сохранить");
            quit.setButtonText(QMessageBox::No, "не сохраненять");
            quit.setButtonText(QMessageBox::Cancel,"отмена");
            answer = quit.exec();
        }
        if(answer != -200)
        {
            switch (answer)
            {
                case QMessageBox::No :
                    QApplication::quit();
                    break;
                case QMessageBox::Yes :
                    if(file.isExist())
                        on_save_triggered();
                    else
                        on_save_as_triggered();
                    QApplication::quit();
                    break;
                default :
                    event->ignore();
            }
        }
}

void MainWindow::on_textEdit_textChanged()
{
    QTextCursor dc(ui->textEdit->textCursor());
    QString temp = ui->textEdit->toPlainText();
    if(temp.length() > charCount)
    {
        if(temp[dc.position()-1] == QChar('('))
            closePair(dc,')');
        if(temp[dc.position()-1] == QChar('\"'))
            closePair(dc,'\"');
        if(temp[dc.position()-1] == QChar('{'))
            closePair(dc,'}');
        if(temp[dc.position()-1] == QChar('['))
            closePair(dc,']');
        if(temp[dc.position()-1] == QChar('\''))
            closePair(dc,'\'');
    }
    if(!(ui->textEdit->toPlainText().isEmpty() && !file.isExist()))
        setWindowTitle("Text Blade - " + file.getFileName() + "*");
    file.change();
    int size = temp.split(QRegExp("[\\s]+\\w")).size();
        if(temp[0] == QChar(' ') || temp[0] == QChar('\t') || temp[0] == QChar('\n') || temp.isEmpty() )
            size--;
    QString message = "слов:";
    message += std::to_string(size).data();
    message += "\nсимволов:";
    message += std::to_string(temp.length()).data();
    ui->statusbar->showMessage(message);
    charCount = temp.length();
}

void MainWindow::on_open_triggered()
{
    QString path = QFileDialog::getOpenFileName(0,"выбор файла", "", "");
    file.open(path);
    ui->textEdit->setText(file.getText());
    file.save(ui->textEdit->toPlainText());
    setWindowTitle("Text Blade - " + file.getFileName());
}

void MainWindow::on_create_triggered()
{
    QString path = QFileDialog::getSaveFileName(0, "создание файла", "", "");
    file.create(path);
    setWindowTitle("Text Blade - "+ file.getFileName());
}

void MainWindow::on_save_as_triggered()
{
    QString path = QFileDialog::getSaveFileName(0, "сохранение файла", "", "");
    if(!path.isEmpty())
    {
        file.create(path);
        file.save(ui->textEdit->toPlainText());
        setWindowTitle("Text Blade - " + file.getFileName());
    }
}
void MainWindow::setColorTheme(const QString& colorTheme)
{
    if(colorTheme == "Dark")
    {
        this->setStyleSheet("color:white;background-color:#051B2B;");
        ui->textEdit->setStyleSheet("background-color:#06151a;color:#D6B5F5;");
    }
    if(colorTheme == "Classic")
    {
        this->setStyleSheet("color:black;background-color:white");
        ui->textEdit->setStyleSheet("color:black;background-color:white");
    }
}

void MainWindow::on_exit_triggered()
{
   QCloseEvent event;
   closeEvent(&event);
}

void MainWindow::closePair(QTextCursor& dc ,char ch)
{
    QChar c(ch);
    QString temp = ui->textEdit->toPlainText();
    int pos = dc.position();
    if((temp[pos] == QChar(' ') || temp.length() == pos))
        temp[pos] = c;
    ui->textEdit->setText(temp);
    dc.setPosition(pos);
    ui->textEdit->setTextCursor(dc);
}
