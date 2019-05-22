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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedPages;
    QWidget *Welcome;
    QPushButton *enter;
    QLabel *label;
    QWidget *MainMenu;
    QPushButton *Funct1;
    QPushButton *Funct2;
    QPushButton *Funct3;
    QPushButton *Funct4;
    QWidget *Display;
    QPushButton *Show;
    QLabel *label_2;
    QToolButton *searchFile;
    QLineEdit *filePath;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QComboBox *currency1;
    QComboBox *currency2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(480, 360);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        stackedPages = new QStackedWidget(centralWidget);
        stackedPages->setObjectName(QString::fromUtf8("stackedPages"));
        stackedPages->setGeometry(QRect(0, 0, 480, 298));
        sizePolicy.setHeightForWidth(stackedPages->sizePolicy().hasHeightForWidth());
        stackedPages->setSizePolicy(sizePolicy);
        Welcome = new QWidget();
        Welcome->setObjectName(QString::fromUtf8("Welcome"));
        sizePolicy.setHeightForWidth(Welcome->sizePolicy().hasHeightForWidth());
        Welcome->setSizePolicy(sizePolicy);
        enter = new QPushButton(Welcome);
        enter->setObjectName(QString::fromUtf8("enter"));
        enter->setGeometry(QRect(300, 240, 111, 32));
        label = new QLabel(Welcome);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 80, 101, 51));
        label->setTextFormat(Qt::PlainText);
        label->setScaledContents(false);
        label->setMargin(20);
        stackedPages->addWidget(Welcome);
        MainMenu = new QWidget();
        MainMenu->setObjectName(QString::fromUtf8("MainMenu"));
        sizePolicy.setHeightForWidth(MainMenu->sizePolicy().hasHeightForWidth());
        MainMenu->setSizePolicy(sizePolicy);
        Funct1 = new QPushButton(MainMenu);
        Funct1->setObjectName(QString::fromUtf8("Funct1"));
        Funct1->setGeometry(QRect(80, 10, 140, 140));
        Funct2 = new QPushButton(MainMenu);
        Funct2->setObjectName(QString::fromUtf8("Funct2"));
        Funct2->setGeometry(QRect(260, 10, 140, 140));
        Funct3 = new QPushButton(MainMenu);
        Funct3->setObjectName(QString::fromUtf8("Funct3"));
        Funct3->setGeometry(QRect(80, 150, 140, 140));
        Funct4 = new QPushButton(MainMenu);
        Funct4->setObjectName(QString::fromUtf8("Funct4"));
        Funct4->setGeometry(QRect(260, 150, 140, 140));
        stackedPages->addWidget(MainMenu);
        Display = new QWidget();
        Display->setObjectName(QString::fromUtf8("Display"));
        sizePolicy.setHeightForWidth(Display->sizePolicy().hasHeightForWidth());
        Display->setSizePolicy(sizePolicy);
        Show = new QPushButton(Display);
        Show->setObjectName(QString::fromUtf8("Show"));
        Show->setGeometry(QRect(340, 240, 111, 32));
        label_2 = new QLabel(Display);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 150, 81, 16));
        searchFile = new QToolButton(Display);
        searchFile->setObjectName(QString::fromUtf8("searchFile"));
        searchFile->setGeometry(QRect(330, 150, 25, 22));
        filePath = new QLineEdit(Display);
        filePath->setObjectName(QString::fromUtf8("filePath"));
        filePath->setGeometry(QRect(150, 150, 161, 21));
        label_3 = new QLabel(Display);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 64, 57, 16));
        label_4 = new QLabel(Display);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 106, 71, 16));
        label_5 = new QLabel(Display);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 10, 121, 16));
        currency1 = new QComboBox(Display);
        currency1->setObjectName(QString::fromUtf8("currency1"));
        currency1->setGeometry(QRect(150, 60, 91, 32));
        currency2 = new QComboBox(Display);
        currency2->setObjectName(QString::fromUtf8("currency2"));
        currency2->setGeometry(QRect(150, 100, 91, 32));
        stackedPages->addWidget(Display);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 480, 22));
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
        enter->setText(QApplication::translate("MainWindow", "Continue", nullptr));
        label->setText(QApplication::translate("MainWindow", "Welcome", nullptr));
        Funct1->setText(QApplication::translate("MainWindow", "Funct1", nullptr));
        Funct2->setText(QApplication::translate("MainWindow", "Funct2", nullptr));
        Funct3->setText(QApplication::translate("MainWindow", "Funct3", nullptr));
        Funct4->setText(QApplication::translate("MainWindow", "Funct4", nullptr));
        Show->setText(QApplication::translate("MainWindow", "Go", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Select File", nullptr));
        searchFile->setText(QApplication::translate("MainWindow", "...", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Currency", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Currency2", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Candle stick display", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
