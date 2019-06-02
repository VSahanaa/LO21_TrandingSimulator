/********************************************************************************
** Form generated from reading UI file 'tab_macd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB_MACD_H
#define UI_TAB_MACD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tab_MACD
{
public:

    void setupUi(QWidget *tab_MACD)
    {
        if (tab_MACD->objectName().isEmpty())
            tab_MACD->setObjectName(QString::fromUtf8("tab_MACD"));
        tab_MACD->resize(400, 300);

        retranslateUi(tab_MACD);

        QMetaObject::connectSlotsByName(tab_MACD);
    } // setupUi

    void retranslateUi(QWidget *tab_MACD)
    {
        tab_MACD->setWindowTitle(QApplication::translate("tab_MACD", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tab_MACD: public Ui_tab_MACD {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB_MACD_H
