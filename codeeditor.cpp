#include "codeeditor.h"
#include <QPainter>
#include <linenumberarea.h>
#include <QTextBlock>
#include <QDebug>

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    enable = this->lineWrapMode();
    lineNumberArea = new LineNumberArea(this);
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    updateLineNumberAreaWidth(0);
}

CodeEditor::~CodeEditor()
{
    delete lineNumberArea;
}

int CodeEditor::lineNumberAreaWidth()
{
    if(!visible)
        return 0;

    int digits = 1;
    int line = blockCount();

    while(line > 10)
    {
        line /= 10;
        digits++;
    }
    int space = fontMetrics().xHeight()*digits;
    return space+10;
}

void CodeEditor::updateLineNumberAreaWidth(int)
{
   setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy != 0)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), 2381691);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.setFont(this->font());
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void CodeEditor::hideLineNumberArea()
{
    visible = false;
    this->lineNumberArea->hide();
}

void CodeEditor::showLineNumberArea()
{
    visible = true;
    this->lineNumberArea->show();
}

void CodeEditor::enableLineWrap()
{
    this->setLineWrapMode(enable);
}

void CodeEditor::disableLineWrap()
{
    this->setLineWrapMode(QPlainTextEdit::NoWrap);
}
