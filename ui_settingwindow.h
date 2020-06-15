/********************************************************************************
** Form generated from reading UI file 'settingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGWINDOW_H
#define UI_SETTINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingWindow
{
public:
    QFormLayout *formLayout;
    QLabel *label_2;
    QFontComboBox *fontComboBox;
    QLabel *label;
    QSpinBox *fontSize;
    QLabel *label_3;
    QComboBox *colorTheme;

    void setupUi(QDialog *SettingWindow)
    {
        if (SettingWindow->objectName().isEmpty())
            SettingWindow->setObjectName(QString::fromUtf8("SettingWindow"));
        SettingWindow->resize(559, 300);
        formLayout = new QFormLayout(SettingWindow);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_2 = new QLabel(SettingWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        fontComboBox = new QFontComboBox(SettingWindow);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, fontComboBox);

        label = new QLabel(SettingWindow);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        fontSize = new QSpinBox(SettingWindow);
        fontSize->setObjectName(QString::fromUtf8("fontSize"));

        formLayout->setWidget(1, QFormLayout::FieldRole, fontSize);

        label_3 = new QLabel(SettingWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        colorTheme = new QComboBox(SettingWindow);
        colorTheme->addItem(QString());
        colorTheme->addItem(QString());
        colorTheme->setObjectName(QString::fromUtf8("colorTheme"));

        formLayout->setWidget(2, QFormLayout::FieldRole, colorTheme);


        retranslateUi(SettingWindow);

        QMetaObject::connectSlotsByName(SettingWindow);
    } // setupUi

    void retranslateUi(QDialog *SettingWindow)
    {
        SettingWindow->setWindowTitle(QApplication::translate("SettingWindow", "\320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        label_2->setText(QApplication::translate("SettingWindow", "\321\210\321\200\320\270\321\204\321\202 ", nullptr));
        label->setText(QApplication::translate("SettingWindow", "\321\200\320\260\320\267\320\274\320\265\321\200 \321\210\321\200\320\270\321\204\321\202\320\260", nullptr));
        label_3->setText(QApplication::translate("SettingWindow", "\321\202\320\265\320\274\320\260", nullptr));
        colorTheme->setItemText(0, QApplication::translate("SettingWindow", "Dark", nullptr));
        colorTheme->setItemText(1, QApplication::translate("SettingWindow", "Classic", nullptr));

    } // retranslateUi

};

namespace Ui {
    class SettingWindow: public Ui_SettingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWINDOW_H
