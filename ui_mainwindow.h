/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *create;
    QAction *open;
    QAction *save;
    QAction *save_as;
    QAction *setting;
    QAction *exit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 476);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resource/Text.icon"), QSize(), QIcon::Active, QIcon::On);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("color:white; background-color:#051B2B;"));
        create = new QAction(MainWindow);
        create->setObjectName(QString::fromUtf8("create"));
        open = new QAction(MainWindow);
        open->setObjectName(QString::fromUtf8("open"));
        save = new QAction(MainWindow);
        save->setObjectName(QString::fromUtf8("save"));
        save_as = new QAction(MainWindow);
        save_as->setObjectName(QString::fromUtf8("save_as"));
        setting = new QAction(MainWindow);
        setting->setObjectName(QString::fromUtf8("setting"));
        exit = new QAction(MainWindow);
        exit->setObjectName(QString::fromUtf8("exit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        textEdit->setFont(font);
        textEdit->setStyleSheet(QString::fromUtf8("background-color:black;color:cyan;"));

        verticalLayout_2->addWidget(textEdit);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 24));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(create);
        menu->addAction(open);
        menu->addAction(save);
        menu->addAction(save_as);
        menu->addAction(exit);
        menu_2->addSeparator();
        menu_2->addSeparator();
        menu_2->addAction(setting);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        create->setText(QApplication::translate("MainWindow", "\321\201\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\276\320\262\321\213\320\271 \321\204\320\260\320\271\320\273", nullptr));
#ifndef QT_NO_SHORTCUT
        create->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        open->setText(QApplication::translate("MainWindow", "\320\276\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
#ifndef QT_NO_SHORTCUT
        open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        save->setText(QApplication::translate("MainWindow", "\321\201\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
#ifndef QT_NO_SHORTCUT
        save->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        save_as->setText(QApplication::translate("MainWindow", "\321\201\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272...", nullptr));
#ifndef QT_NO_SHORTCUT
        save_as->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_NO_SHORTCUT
        setting->setText(QApplication::translate("MainWindow", "\320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));
        exit->setText(QApplication::translate("MainWindow", "\320\262\321\213\321\205\320\276\320\264", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\321\204\320\260\320\271\320\273", nullptr));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\270\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\321\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
