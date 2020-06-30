#include "mysyntax.h"
#include <QtAlgorithms>
#include <QDebug>
MySyntax::MySyntax(QTextDocument* parent)
    :QSyntaxHighlighter(parent)
{
    red
        << "case" << "return" << "&" << "+" << "-" << "=" << "|"
        <<"if"  << "else"<<"while" << "using " << "namespace" << "switch" << "#include"
        << "#define" << "const" <<"for" << "#ifdef" << "#endif";
    cyan
        << "float" << "int" << "bool" << "void" << "enum"
        << "typedef " << "class " << "struct" << "double" << "long"
        << "char" << "short " << "signed " << "unsigned " << "union";
    yellow
        << "delete" << "new" << "virtual" << "throw " << "override" << "template" << "mutable" << "this"
        << "auto" <<"catch";
}
void MySyntax::highlightBlock(const QString &str)
{
    int nState = previousBlockState();
    int nStart = 0;
    for(int i = 0; i < str.length();++i)
    {
        if(nState == InsideCStyleComment)
        {
            if(str.mid(i,2) == "*/")
            {
                nState = NormalState;
                setFormat(nStart,i-nStart+2,Qt::darkGray);
            }
        }
        else if(nState == InsideCString)
        {
            if(str.mid(i,1) == "\"" || str.mid(i,1) == "\'")
            {
                if(str.mid(i-1,2) != "\\\"" && str.mid(i-1,2) != "\\\'")
                {
                    nState = NormalState;
                    setFormat(nStart,i-nStart+1,15207566);
                }
            }
        }
        else
        {
            if(str.mid(i,2) == "//")
            {
                setFormat(i,str.length()-i,Qt::darkGray);
                break;
            }
            else if(str.at(i).isNumber())
            {
                int j = i;
                if(str.at(j-1).isSpace() || str.at(j-1).isNull())
                {
                    while(true)
                    {
                        j++;
                        if((str.at(j).isNull() || str.at(j).isSpace()))
                        {
                            setFormat(i,j-i,6235520);
                            i += (j-i);
                            break;
                        }
                        if(!str.at(j).isNumber())
                        {
                            i += (j-i);
                            break;
                        }
                    }
                }
            }
            else if(str.mid(i,2) == "/*")
            {
                nStart = i;
                nState = InsideCStyleComment;
            }
            else if(str.mid(i,1) == "\"" || str.mid(i,1) == "\'")
            {
                nStart = i;
                nState = InsideCString;
            }
            else
            {
                QString wred = getKeyWord(i,str,red);
                QString wcyan = getKeyWord(i,str,cyan);
                QString wyellow = getKeyWord(i,str,yellow);
                if(!wred.isEmpty())
                {
                    setFormat(i,wred.length(), Qt::red);
                    i += wred.length() -1;
                }
                else if(!wcyan.isEmpty())
                {
                    setFormat(i,wcyan.length(),Qt::cyan);
                    i += wcyan.length() -1;
                }
                else if(!wyellow.isEmpty())
                {
                    setFormat(i,wyellow.length(),Qt::yellow);
                    i += wyellow.length() -1;
                }
                else if(str.at(i) == QChar('('))
                {
                    int j = i;
                    while (!str.at(j).isSpace())
                        j--;
                    setFormat(j,i-j,Qt::green);
                }
            }
            if(str.mid(i,1) == ")" || str.mid(i,1) == "(")
                setFormat(i,1,Qt::white);
        }
    }
    if(nState == InsideCStyleComment)
        setFormat(nStart,str.length()- nStart,Qt::darkGray);

    if(nState == InsideCString)
        setFormat(nStart,str.length()-nStart,Qt::cyan);

    setCurrentBlockState(nState);
}

QString MySyntax::getKeyWord(int nPos , const QString& str,const QStringList& list) const
{
    QString strTemp = "";
    for(QString strKeyWord : list)
    {
        QString temp = str.mid(nPos,strKeyWord.length());
        int end = nPos+temp.length();
        int begin = nPos-1;
        if(temp == strKeyWord && (str.at(end).isSpace() || str.at(end).isNull() || str.at(end) == QChar('(') || str.at(end) == QChar(')')))
                if(str.at(begin).isSpace() || str.at(begin) == QChar('(') || !str.at(begin).isPrint())
                {
                    strTemp = strKeyWord;
                    break;
                }
    }
    return strTemp;
}
