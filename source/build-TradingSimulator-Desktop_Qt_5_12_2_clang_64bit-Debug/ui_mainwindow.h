/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *Modes;
    QWidget *simuM;
    QLabel *label;
    QWidget *simuA;
    QLabel *label_2;
    QWidget *simuS;
    QLabel *label_3;
    QWidget *cdStk;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(720, 540);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        Modes = new QStackedWidget(centralWidget);
        Modes->setObjectName(QString::fromUtf8("Modes"));
        Modes->setGeometry(QRect(0, 0, 720, 478));
        simuM = new QWidget();
        simuM->setObjectName(QString::fromUtf8("simuM"));
        label = new QLabel(simuM);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 200, 141, 16));
        Modes->addWidget(simuM);
        simuA = new QWidget();
        simuA->setObjectName(QString::fromUtf8("simuA"));
        label_2 = new QLabel(simuA);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(320, 190, 131, 16));
        Modes->addWidget(simuA);
        simuS = new QWidget();
        simuS->setObjectName(QString::fromUtf8("simuS"));
        label_3 = new QLabel(simuS);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(300, 200, 171, 16));
        Modes->addWidget(simuS);
        cdStk = new QWidget();
        cdStk->setObjectName(QString::fromUtf8("cdStk"));
        label_4 = new QLabel(cdStk);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(290, 210, 161, 16));
        Modes->addWidget(cdStk);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 720, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Trading Simulator", nullptr));
        label->setText(QApplication::translate("MainWindow", "Here's Manuel Mode", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Here's Auto Mode", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Here's step by step mode", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Here's candlestick display", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
