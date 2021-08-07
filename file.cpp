#include "file.h"
#include <QFileInfo>

File::File() : QFile::QFile()
{
    conserved = true;
}

File::File(const QString &name) : QFile::QFile(name)
{
    QFileInfo FileName(name);
    suffix = FileName.completeSuffix();
    conserved = true;
}

File::File(QObject* parent) : QFile::QFile(parent)
{
    conserved = true;
}

File::File(const QString& name,QObject* parent)
    : QFile::QFile(name,parent)
{
    suffix = QFileInfo(name).completeSuffix();
    conserved = true;
}

File::File(QFilePrivate& add, QObject* parent)
    : QFile::QFile(add,parent)
{
    conserved = true;
}

QString File::type()
{
    if(suffix == "cpp" || suffix == "h")
        return "C++";
    else if(suffix == "py")
        return "python";
    else
        return "plain text";
}

void File::change() noexcept
{
    conserved = false;
}

void File::createEmptyFile(QString& name) noexcept
{
    this->setFileName(name);
    this->open(QIODevice::WriteOnly);
    suffix = QFileInfo(name).completeSuffix();
    conserved = true;
    this->close();
}

bool File::isConserved() noexcept
{
    return conserved;
}
