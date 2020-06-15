#ifndef FILE_H
#define FILE_H
#include <QString>
#include <QFile>
#include <QTextStream>

class File
{
public:
    File();
    explicit File(QString& name) noexcept;
    void save (QString text) noexcept;
    void open(QString& path) noexcept;
    void change() noexcept;
    void create(QString& path) noexcept;
    void setFileName(QString path) noexcept;
    bool isConserved() const noexcept;
    bool isExist() const noexcept;
    QString getText() const noexcept;
    QString getFileName() const noexcept;
    QString getPath() const noexcept;
    ~File();

private:
    void CountWord(QString &Text) const noexcept;
    bool exist;
    bool conserved;
    mutable unsigned int words;
    QTextStream input;
    QTextStream output;
    QString path;
    QString fileName;
};

#endif // FILE_H
