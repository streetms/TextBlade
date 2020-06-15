#include "file.h"
#include <QFileInfo>
File::File(QString& name) noexcept
    : path(name)
{
    conserved = true;
    exist = true;
    QFileInfo FileName(path);
    fileName = FileName.fileName();
}

File::File() : exist(false)
{
    conserved = true;
}

File::~File()
{
}

void File::open(QString &name) noexcept
{
    exist = true;
    conserved = true;
    path = name;
    QFileInfo FileName(path);
    fileName = FileName.fileName();
}

void File::save(QString newText) noexcept
{
    conserved = true;
    QFile fout;
    fout.setFileName(path);
    //std::cout << path.toStdString() << std::endl;
    fout.open(QIODevice::WriteOnly);
    output.setDevice(&fout);
    output << newText.toUtf8();
    fout.close();
}

QString File::getText() const noexcept
{
    QString Text;
    QFile fin;
    QTextStream input;
    fin.setFileName(path);
    fin.open(QIODevice::ReadOnly);
    input.setDevice(&fin);
    while(!input.atEnd())
        Text += input.readLine() + "\n";
    fin.close();
    return Text;

}

QString File::getFileName() const noexcept
{
    return fileName;
}

void File::change() noexcept
{
    conserved = false;
}

bool File::isConserved() const noexcept
{
  return conserved;
}

QString File::getPath() const noexcept
{
    return path;
}

bool File::isExist() const  noexcept
{
    return exist;
}

void File::create(QString& path) noexcept
{
    this->path = path;
    conserved = true;
    exist = true;
    QFile fout;
    fout.setFileName(path);
    fout.open(QIODevice::WriteOnly);
    fout.close();
    QFileInfo FileName(path);
    fileName = FileName.fileName();
}

void File::setFileName(QString path) noexcept
{
    fileName = path;
}
