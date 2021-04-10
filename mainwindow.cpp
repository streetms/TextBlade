#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mysyntax.h"
#include "codeeditor.h"
#include <map>
#include <QMessageBox>
#include <QString>
#include <QTextEdit>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextCursor>


MainWindow::MainWindow(QString& fileName , QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) , factor(1)
{
    QFile fin;
    ui->setupUi(this);
    ui->findEdit->hide();
    settingMap.emplace(std::pair("font-size",""));
    settingMap.emplace(std::pair("font-family",""));
    settingMap.emplace(std::pair("color-theme",""));
    settingMap.emplace(std::pair("syntax-highlighting",""));
    settingMap.emplace(std::pair("wrap-mode",""));


    settingFile =  QCoreApplication::applicationDirPath()+"/.setting.dat";
    fin.setFileName(settingFile);
    this->setWindowTitle("Text Blade");

    if(!fin.open(QIODevice::ReadOnly))
    {
        fin.open(QIODevice::WriteOnly);
        createSettingFile(fin);
        fin.close();
    }
    else
    {
        readSettingFile(fin);
        fin.close();
    }


    if(settingMap["font-size"] == "font-family:")
    {
        fin.open(QIODevice::WriteOnly);
        createSettingFile(fin);
        fin.close();
        fin.open(QIODevice::ReadOnly);
        readSettingFile(fin);
        fin.close();
    }

    QFont font;
    font.setFamily(settingMap["font-family"]);
    font.setPixelSize(settingMap["font-size"].toInt());
    font.setBold(ui->textEdit->font().bold());
    ui->textEdit->setFont(font);
    setColorTheme(settingMap["color-theme"]);
    fileType = settingMap["syntax-highlighting"];
    syntax = new MySyntax(fileType,ui->textEdit->document());

    if(!fileName.isNull())
    {
        file.open(fileName);

        if(file.type() != fileType)
        {
            fileType = file.type();
            delete syntax;
            syntax = new MySyntax(fileType,ui->textEdit->document());
            settingMap["syntax-highlighting"] = fileType;
        }

        ui->textEdit->setPlainText(file.getText());
        file.save(ui->textEdit->toPlainText());
        setWindowTitle("Text Blade - " + file.getFileName());
    }

    setWindowTitle("Text Blade - " + file.getFileName());
    int fontWidth = QFontMetrics(ui->textEdit->currentCharFormat().font()).averageCharWidth();
    ui->textEdit->setTabStopWidth( 4 * fontWidth );

    if(settingMap["wrap-mode"] == "Off")
    {
        ui->textEdit->showLineNumberArea();
    }
    else
    {
        ui->textEdit->hideLineNumberArea();
        ui->textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    }
    ui->textEdit->update();

    settingWindow = new SettingWindow(settingMap,factor);
    settingWindow->setModal(true);
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
    output << "syntax-highlighting: " + settingMap["syntax-highlighting"] + "\n";
    output << "wrap-mode: " + settingMap["wrap-mode"] + "\n";
    delete syntax;
    delete settingWindow;
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
    QString oldSyntaxType = settingMap["syntax-highlighting"];
    QString oldWrapMode = settingMap["wrap-mode"];
    settingWindow->exec();

    if(oldWrapMode != settingMap["wrap-mode"])
    {
        if(settingMap["wrap-mode"] == "Off")
        {
            ui->textEdit->showLineNumberArea();
        }
        else
        {
            ui->textEdit->hideLineNumberArea();
            ui->textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        }
        ui->textEdit->update();
    }

    QFont font;
    font.setFamily(settingMap["font-family"]);
    font.setPixelSize(settingMap["font-size"].toInt()*factor);
    font.setBold(ui->textEdit->font().bold());
    ui->textEdit->setFont(font);
    setColorTheme(settingMap["color-theme"]);

    if(settingMap["syntax-highlighting"] != oldSyntaxType)
    {
        delete syntax;
        syntax = new MySyntax(settingMap["syntax-highlighting"],ui->textEdit->document());
        fileType = settingMap["syntax-highlighting"];
    }

    int fontWidth = QFontMetrics(ui->textEdit->currentCharFormat().font()).averageCharWidth();
    ui->textEdit->setTabStopWidth( 4 * fontWidth );
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int answer = -200;
    QMessageBox quit(
    QMessageBox::Question,
    "Text Blade",
    "",
    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel ,
    this);

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
    if (answer == QMessageBox::Cancel)
    {
        event->ignore();
        return;
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
        }
    }
    else
        QApplication::quit();
}

void MainWindow::on_open_triggered()
{
    QString path = QFileDialog::getOpenFileName(0,"выбор файла", "", "");
    file.open(path);

    if(file.type() != fileType)
    {
        fileType = file.type();
        delete syntax;
        syntax = new MySyntax(fileType,ui->textEdit->document());
        settingMap["syntax-highlighting"] = fileType;
    }

    ui->textEdit->setPlainText(file.getText());
    file.save(ui->textEdit->toPlainText());
    setWindowTitle("Text Blade - " + file.getFileName());
}

void MainWindow::on_create_triggered()
{
    QString path = QFileDialog::getSaveFileName(0, "создание файла", "", "");
    file.create(path);

    if(file.type() != fileType)
    {
        fileType = file.type();
        delete syntax;
        syntax = new MySyntax(fileType,ui->textEdit->document());
        settingMap["syntax-highlighting"] = fileType;
    }

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

    temp.insert(pos,c);

    ui->textEdit->setPlainText(temp);
    dc.setPosition(pos);
    ui->textEdit->setTextCursor(dc);

}

void MainWindow::on_reset_triggered()
{
    ui->findEdit->hide();
}

void MainWindow::on_findEdit_returnPressed()
{
    ui->findEdit->hide();
    int index = 0;
    index = ui->textEdit->toPlainText().indexOf(ui->findEdit->text(),0);

    if(index != -1)
    {
        QTextCursor dc(ui->textEdit->textCursor());
        dc.setPosition(index);
        ui->textEdit->setTextCursor(dc);
    }

    ui->findEdit->clear();
}

void MainWindow::on_aboutQt_triggered()
{
    QMessageBox::aboutQt(this,"About Qt");
}

void MainWindow::on_findText_triggered()
{
    ui->findEdit->setFocus();
    ui->findEdit->show();
}

void MainWindow::readSettingFile(QFile &fin)
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
    input >> settingMap["syntax-highlighting"];
    input >> temp;
    input >> settingMap["wrap-mode"];
    input >> temp;
}

void MainWindow::createSettingFile(QFile &fin)
{
    QTextStream output;
    output.setDevice(&fin);
    settingMap["font-size"] = "15";
    QString font = ui->textEdit->font().toString();
    int index = font.indexOf(',');
    settingMap["font-family"] = font.left(index);
    settingMap["color-theme"] = "Dark";
    settingMap["syntax-highlighting"] = "No";
    output << "font-size: " + settingMap["font-size"] + "\n";
    output << "font-family: " + settingMap["font-family"] + "\n";
    output << "syntax-highlighting: " + settingMap["syntax-highlighting"] + "\n";
}

void MainWindow::on_up_triggered()
{
    QFont font;
    factor += 0.1;
    font.setPixelSize(settingMap["font-size"].toInt()*factor);
    font.setFamily(settingMap["font-family"]);
    ui->textEdit->setFont(font);
    int fontWidth = QFontMetrics(ui->textEdit->currentCharFormat().font()).averageCharWidth();
    ui->textEdit->setTabStopWidth( 4 * fontWidth );
}

void MainWindow::on_down_triggered()
{
    QFont font;

    if(factor > 0.4)
        factor -= 0.1;

    font.setPixelSize(settingMap["font-size"].toInt()*factor);
    font.setFamily(settingMap["font-family"]);
    ui->textEdit->setFont(font);
    int fontWidth = QFontMetrics(ui->textEdit->currentCharFormat().font()).averageCharWidth();
    ui->textEdit->setTabStopWidth( 4 * fontWidth );
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

    QString message = settingMap["syntax-highlighting"];
    message += "                   слов:";
    message += std::to_string(size).data();
    message += "\nсимволов:";
    message += std::to_string(temp.length()).data();
    ui->statusbar->showMessage(message);
    charCount = temp.length();
}
