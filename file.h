#pragma once

#include <QString>
#include <QFile>
#include <QTextStream>

class File
{
public:
    File();
    explicit File(QString& name) noexcept;
    ~File();

    void save (QString&& text) noexcept;
    void open(QString& path) noexcept;
    void change() noexcept;
    void create(QString& path) noexcept;
    void setFileName(QString path) noexcept;

    bool isConserved() const noexcept;
    bool isExist() const noexcept;

    QString type() const noexcept;
    QString getText() const noexcept;
    QString getFileName() const noexcept;
    QString getPath() const noexcept;

private:
    void CountWord(QString &Text) const noexcept;

    bool exist;
    bool conserved;

    mutable size_t words;

    QTextStream input;
    QTextStream output;

    QString path;
    QString fileName;
    QString suffix;
};
