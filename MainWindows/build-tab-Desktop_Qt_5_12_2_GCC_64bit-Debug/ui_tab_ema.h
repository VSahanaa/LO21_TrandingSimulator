/********************************************************************************
** Form generated from reading UI file 'tab_ema.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB_EMA_H
#define UI_TAB_EMA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tab_EMA
{
public:
    QGraphicsView *graphicsView;

    void setupUi(QWidget *tab_EMA)
    {
        if (tab_EMA->objectName().isEmpty())
            tab_EMA->setObjectName(QString::fromUtf8("tab_EMA"));
        tab_EMA->resize(400, 300);
        graphicsView = new QGraphicsView(tab_EMA);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(5, 11, 381, 271));

        retranslateUi(tab_EMA);

        QMetaObject::connectSlotsByName(tab_EMA);
    } // setupUi

    void retranslateUi(QWidget *tab_EMA)
    {
        tab_EMA->setWindowTitle(QApplication::translate("tab_EMA", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tab_EMA: public Ui_tab_EMA {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB_EMA_H
