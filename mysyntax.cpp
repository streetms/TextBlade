#include "mysyntax.h"
#include <algorithm>
#include <QTextStream>
#include <QDebug>
MySyntax::MySyntax(QString Syntax, QTextDocument* parent)
    :QSyntaxHighlighter(parent)
{

    syntax = Syntax;

    if(syntax == "python")
    {
        red
            << "return" << "continue" << "break" << "None" << "and" << "or" << "in"
            << "if" << "else" <<"while"<< "not" << "for"  << "elif" << "import" << "from"
            << "True" << "False" << "continue" << "break" << "except" << "try" << "is";
        cyan
            << "list" << "dict" << "set" <<  "str" << "int" << "float" << "class" << "def"
            << "abs" << "all" << "any" << "asci" <<"bin" << "callable" << "chr" << "compile"
            << "classmethod" << "delattr" << "dir" << "divmod" << "enumerate" << "eval"
            << "staticmethod" << "sum" << "super" << "vars" << "zip" << "range" << "sorted"
            << "print" << "repr" << "reversed" << "round" << "tuple" << "setattr" << "ord"
            << "pow" << "len" << "locals" << "map" << "max" << "min" << "next" << "oct"
            << "open" << "hash" << "help" << "id"<< "input" << "isinstance"<<"iter" << "exec"
            << "issubclass" << "filter" << "format" <<"gettar" << "global" << "shasattr";
    }

    if(syntax == "C++")
    {
        red
            << "case" << "return" << "true" << "false" << "continue" << "break" << "NULL" << "and" << "or"
            << "if" << "else"<<"while" << "using" << "namespace" << "switch" << "#include" << "not"
            << "#define" << "const" <<"for" << "#ifdef" << "#endif" << "try" << "catch" << "throw"
            << "static"  << "#ifndef" << "#pragma" << "public" << "private" << "protected" ;
        cyan
            << "float" << "int" << "bool" << "void" << "enum" << "typename" << "size_t"
            << "typedef " << "class" << "struct" << "double" << "long"
            << "char" << "short" << "signed" << "unsigned" << "union";
        yellow
            << "delete" << "new" << "virtual" << "throw" << "override" << "template" << "mutable" << "this"
            << "auto" <<"catch" << "nullptr" << "constexpr" << "explicit" << "delete[]" << "operator"
            << "noexcept";
    }
}

void MySyntax::highlightBlock(const QString &str)
{
    int nState = previousBlockState();
    int nStart = 0;
    if(syntax != "No")
    {
        for(int i = 0; i < str.length();++i)
        {
            if(nState == InsideCStyleComment)
            {
                if((syntax == "C++"  && str.mid(i,2) == "*/")  || (syntax == "python" && str.mid(i,3) == "\"\"\""))
                {
                    nState = NormalState;
                    if(syntax == "python")
                    {
                         setFormat(nStart,i-nStart+3,Qt::darkGray);
                         i+=3;
                    }
                    else
                    {
                        setFormat(nStart,i-nStart+2,Qt::darkGray);
                        i+=2;
                    }
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
                if((syntax == "C++" && str.mid(i,2) == "//") || (syntax == "python" && str.mid(i,1) == "#"))
                {
                    setFormat(i,str.length()-i,Qt::darkGray);
                    break;
                }

                else if((syntax == "C++" && str.mid(i,2) == "/*") || (syntax == "python" && str.mid(i,3) == "\"\"\""))
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
                        if(wred == "true" || wred == "false" || wred == "True" || wred == "False" || wred == "NULL" || wred == "None")
                            setFormat(i,wred.length(),6235520);
                        else
                            setFormat(i,wred.length(),Qt::red);
                        i += wred.length() -1;
                        while(str.at(i+1).isSpace() || str.at(i+1) == QChar('('))
                            i++;
                        if(str.at(i) == QChar('('))
                            i++;
                    }
                    if(!wcyan.isEmpty())
                    {
                        setFormat(i,wcyan.length(),Qt::cyan);
                        i += wcyan.length() -1;
                        while(str.at(i+1).isSpace() || str.at(i+1) == QChar('('))
                            i++;
                        if(str.at(i) == QChar('('))
                            i++;
                    }
                    if(!wyellow.isEmpty())
                    {
                        setFormat(i,wyellow.length(),Qt::yellow);
                        i += wyellow.length() -1;
                        while(str.at(i+1).isSpace() || str.at(i+1) == QChar('('))
                            i++;
                       if(str.at(i) == QChar('('))
                            i++;
                    }
                    if(str.at(i) == QChar('('))
                    {
                        int j = i-1;
                        while(true)
                        {
                            if(str.at(j).isSpace())
                                j--;
                            else
                                break;
                        }
                        while (!str.at(j).isSpace() && j >0 && str.at(j-1) != QChar('.') && (str.at(j-1) != QChar('-') && str.at(j-1) != QChar('>')))
                            j--;
                        for(int k = j; k < i; k++)
                        {
                            if(str.at(k) != QChar('[') && str.at(k) != QChar(']') && str.at(k) != QChar('(') && str.at(k) != QChar('+') && str.at(k) != QChar('-') && str.at(k) != QChar('*') && str.at(k) != QChar('/') && str.at(k) != QChar('%'))
                                setFormat(k,1,Qt::green);
                            else
                                break;
                        }
                    }
                    if(!wred.isEmpty() || !wcyan.isEmpty() || !wyellow.isEmpty())
                        i--;
                }
            }
            if(str.at(i).isNumber())
            {
                int j = i;
                if(str.at(j-1).isSpace() || str.at(j-1).isNull() || str.at(j-1) == QChar('/')
                        || str.at(j-1) == QChar('%') || str.at(j-1) == QChar('*')
                        || str.at(j-1) == QChar('+') || str.at(j-1) == QChar('-')
                        || str.at(j-1) == QChar('(') || str.at(j-1) == QChar(')')
                        || str.at(j-1) == QChar('>') || str.at(j-1) == QChar('<')
                        || str.at(j-1) == QChar('=') || str.at(j-1) == QChar('[')
                        || str.at(j-1) == QChar(']') || str.at(j-1) == QChar(',')
                        || str.at(j-1) == QChar('{') || str.at(j-1) == QChar('}'))
                {
                    while(true)
                    {
                        j++;
                        if((str.at(j).isNull() || str.at(j).isSpace()) || str.at(j) == QChar(';')
                        || str.at(j) == QChar(':') || str.at(j) == QChar('*') || str.at(j) == QChar('+')
                        || str.at(j) == QChar('-') || str.at(j) == QChar('/') || str.at(j) == QChar('%')
                        || str.at(j) == QChar('(') || str.at(j) == QChar(')') || str.at(j) == QChar('>')
                        || str.at(j) == QChar('<') || str.at(j) == QChar('=') || str.at(j) == QChar(']')
                        || str.at(j) == QChar('[') || str.at(j) == QChar(',') || str.at(j) == QChar('{')
                        || str.at(j) == QChar('}'))
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
        }
    }
    if(nState == InsideCString)
        setFormat(nStart,str.length()-nStart,Qt::cyan);

    if(nState == InsideCStyleComment)
        setFormat(nStart,str.length()- nStart,Qt::darkGray);

    setCurrentBlockState(nState);
}

QString MySyntax::getKeyWord(int nPos , const QString& str,const QStringList& list) const
{
    QString strTemp = "";

    for(const QString& strKeyWord : list)
    {
        QString temp = str.mid(nPos,strKeyWord.length());
        int end = nPos+temp.length();
        int begin = nPos-1;

        if(temp == strKeyWord && (str.at(end).isSpace() || str.at(end).isNull()
                || str.at(end) == QChar('(') || str.at(end) == QChar(')') || str.at(end) == QChar('[')
                || str.at(end) == QChar(']') || str.at(end) == QChar('>')|| str.at(end) == QChar('-')
                || str.at(end) == QChar('&') || str.at(end) == QChar(',')|| str.at(end) == QChar(':')
                || str.at(end) == QChar('*') || str.at(end) == QChar(';')))
        {
                if(str.at(begin) == QChar('<') || str.at(begin) == QChar(':') || str.at(begin) == QChar(',')
                    || str.at(begin) == QChar('(') || str.at(begin) == QChar('[') || str.at(begin).isSpace()
                    || !str.at(begin).isPrint())
                {
                    strTemp = strKeyWord;
                    break;
                }
        }
    }

    return strTemp;
}
