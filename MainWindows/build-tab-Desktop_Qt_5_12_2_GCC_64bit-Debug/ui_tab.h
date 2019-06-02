/********************************************************************************
** Form generated from reading UI file 'tab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB_H
#define UI_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TAB
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TAB)
    {
        if (TAB->objectName().isEmpty())
            TAB->setObjectName(QString::fromUtf8("TAB"));
        TAB->resize(400, 300);
        menuBar = new QMenuBar(TAB);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        TAB->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TAB);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TAB->addToolBar(mainToolBar);
        centralWidget = new QWidget(TAB);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        TAB->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TAB);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TAB->setStatusBar(statusBar);

        retranslateUi(TAB);

        QMetaObject::connectSlotsByName(TAB);
    } // setupUi

    void retranslateUi(QMainWindow *TAB)
    {
        TAB->setWindowTitle(QApplication::translate("TAB", "TAB", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TAB: public Ui_TAB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB_H
