/********************************************************************************
** Form generated from reading UI file 'tab_rsi.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB_RSI_H
#define UI_TAB_RSI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tab_RSI
{
public:

    void setupUi(QWidget *tab_RSI)
    {
        if (tab_RSI->objectName().isEmpty())
            tab_RSI->setObjectName(QString::fromUtf8("tab_RSI"));
        tab_RSI->resize(400, 300);

        retranslateUi(tab_RSI);

        QMetaObject::connectSlotsByName(tab_RSI);
    } // setupUi

    void retranslateUi(QWidget *tab_RSI)
    {
        tab_RSI->setWindowTitle(QApplication::translate("tab_RSI", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tab_RSI: public Ui_tab_RSI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB_RSI_H
