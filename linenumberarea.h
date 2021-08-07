#pragma once

#include <QWidget>
#include <codeeditor.h>

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor);
    void hide();
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    CodeEditor *codeEditor;
};
