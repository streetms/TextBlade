#ifndef FILE_H
#define FILE_H

#include <QFile>

class File : public QFile
{
public:
    File();
    File(const QString& name);
    File(QObject* parent);
    File(const QString& name,QObject* parent);
    File(QFilePrivate& add, QObject* parent = nullptr);

    QString type();

    void change() noexcept;
    void createEmptyFile(QString& name) noexcept;

    bool isConserved() noexcept;
private:
    QString suffix;
    bool conserved;
};

#endif // FILE_H
