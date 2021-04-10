#include "file.h"
#include <QFileInfo>
#include <QFile>

File::File(QString& name) noexcept
    : path(name)
{
    open(name);
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
    suffix = FileName.completeSuffix();
}

void File::save(QString &&newText) noexcept
{
    conserved = true;
    QFile fout;
    fout.setFileName(path);
    fout.open(QIODevice::WriteOnly);
    output.setDevice(&fout);
    output << newText.toUtf8();
}

QString File::getText() const noexcept
{
    QFile fin;
    QTextStream input;
    fin.setFileName(path);
    fin.open(QIODevice::ReadOnly);
    input.setDevice(&fin);

    return input.readAll();
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
    QFileInfo FileName(path);
    fileName = FileName.fileName();
    suffix = FileName.completeSuffix();
}

void File::setFileName(QString path) noexcept
{
    fileName = path;
}

QString File::type() const noexcept
{
    if(suffix == "cpp" || suffix == "h")
        return "C++";
    else if(suffix == "py")
        return "python";
    else
        return "Plain";
}
