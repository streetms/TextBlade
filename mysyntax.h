#pragma once
#include <QSyntaxHighlighter>
class MySyntax : public QSyntaxHighlighter
{
    Q_OBJECT
private:
    QStringList red;
    QStringList cyan;
    QStringList yellow;
    int syntax;
protected:
    enum {NormalState = -1,InsideCStyleComment,InsideCString};
    virtual void highlightBlock(const QString &str);
    QString getKeyWord(int nPos , const QString& str,const QStringList& list) const;
public:
    MySyntax(QTextDocument* parent = 0);
};

