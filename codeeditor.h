#pragma once

#include <QPlainTextEdit>

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = 0);
    ~CodeEditor();
    void showLineNumberArea();
    void hideLineNumberArea();
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    void enableLineWrap();
    void disableLineWrap();
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);

private:
    bool visible;
    int fontSize;
    LineWrapMode enable;
    QWidget *lineNumberArea;
};
