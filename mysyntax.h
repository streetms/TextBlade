#pragma once
#include <QSyntaxHighlighter>

class MySyntax : public QSyntaxHighlighter
{
    Q_OBJECT
private:
    virtual void highlightBlock(const QString &str);

    QString getKeyWord(int nPos , const QString& str,const QStringList& list) const;

    enum {NormalState = -1,InsideCStyleComment,InsideCString};

    QStringList red;
    QStringList cyan;
    QStringList yellow;
    QString syntax;

public:
    MySyntax(QString syntax, QTextDocument* parent = 0);
};
