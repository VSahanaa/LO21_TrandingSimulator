/********************************************************************************
** Form generated from reading UI file 'mainwindow_modeauto.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_MODEAUTO_H
#define UI_MAINWINDOW_MODEAUTO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow_modeauto
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *VL_menu;
    QVBoxLayout *VL_menuFichier;
    QPushButton *pushButton_retourMenu;
    QPushButton *pushButton_sauvegarder;
    QPushButton *pushButton_parametre;
    QPushButton *pushButton_aide;
    QSpacerItem *VSpacer_menuFichierSimulation;
    QVBoxLayout *VL_menuSimulation;
    QLabel *label_strategie;
    QHBoxLayout *HL_infoMontant;
    QLabel *label_montantBase;
    QLabel *label_montantContrepartie;
    QLabel *label_broker;
    QLabel *label_date;
    QComboBox *comboBox_timer;
    QSpacerItem *VSpacer_menuSimulationMenuOption;
    QVBoxLayout *VL_menuOptions;
    QPushButton *pushButton_tabCoursOHLCV;
    QPushButton *pushButton_tabTransaction;
    QPushButton *pushButton_prendreNote;
    QFrame *frame_chandelier;
    QWidget *layoutWidget1;
    QHBoxLayout *HL_indicateur;
    QCheckBox *checkBox_RSI;
    QCheckBox *checkBox_EMA;
    QCheckBox *checkBox_MACD;
    QTabWidget *tabWidget_autres;
    QWidget *tab_RSI;
    QWidget *tab_coursOHLVC;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow_modeauto)
    {
        if (MainWindow_modeauto->objectName().isEmpty())
            MainWindow_modeauto->setObjectName(QString::fromUtf8("MainWindow_modeauto"));
        MainWindow_modeauto->resize(863, 525);
        centralwidget = new QWidget(MainWindow_modeauto);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 161, 491));
        VL_menu = new QVBoxLayout(layoutWidget);
        VL_menu->setObjectName(QString::fromUtf8("VL_menu"));
        VL_menu->setContentsMargins(0, 0, 0, 0);
        VL_menuFichier = new QVBoxLayout();
        VL_menuFichier->setObjectName(QString::fromUtf8("VL_menuFichier"));
        pushButton_retourMenu = new QPushButton(layoutWidget);
        pushButton_retourMenu->setObjectName(QString::fromUtf8("pushButton_retourMenu"));

        VL_menuFichier->addWidget(pushButton_retourMenu);

        pushButton_sauvegarder = new QPushButton(layoutWidget);
        pushButton_sauvegarder->setObjectName(QString::fromUtf8("pushButton_sauvegarder"));

        VL_menuFichier->addWidget(pushButton_sauvegarder);

        pushButton_parametre = new QPushButton(layoutWidget);
        pushButton_parametre->setObjectName(QString::fromUtf8("pushButton_parametre"));

        VL_menuFichier->addWidget(pushButton_parametre);

        pushButton_aide = new QPushButton(layoutWidget);
        pushButton_aide->setObjectName(QString::fromUtf8("pushButton_aide"));

        VL_menuFichier->addWidget(pushButton_aide);


        VL_menu->addLayout(VL_menuFichier);

        VSpacer_menuFichierSimulation = new QSpacerItem(20, 80, QSizePolicy::Minimum, QSizePolicy::Fixed);

        VL_menu->addItem(VSpacer_menuFichierSimulation);

        VL_menuSimulation = new QVBoxLayout();
        VL_menuSimulation->setObjectName(QString::fromUtf8("VL_menuSimulation"));
        label_strategie = new QLabel(layoutWidget);
        label_strategie->setObjectName(QString::fromUtf8("label_strategie"));
        label_strategie->setLayoutDirection(Qt::LeftToRight);

        VL_menuSimulation->addWidget(label_strategie);

        HL_infoMontant = new QHBoxLayout();
        HL_infoMontant->setObjectName(QString::fromUtf8("HL_infoMontant"));
        label_montantBase = new QLabel(layoutWidget);
        label_montantBase->setObjectName(QString::fromUtf8("label_montantBase"));

        HL_infoMontant->addWidget(label_montantBase);

        label_montantContrepartie = new QLabel(layoutWidget);
        label_montantContrepartie->setObjectName(QString::fromUtf8("label_montantContrepartie"));

        HL_infoMontant->addWidget(label_montantContrepartie);

        label_broker = new QLabel(layoutWidget);
        label_broker->setObjectName(QString::fromUtf8("label_broker"));

        HL_infoMontant->addWidget(label_broker);


        VL_menuSimulation->addLayout(HL_infoMontant);

        label_date = new QLabel(layoutWidget);
        label_date->setObjectName(QString::fromUtf8("label_date"));

        VL_menuSimulation->addWidget(label_date);

        comboBox_timer = new QComboBox(layoutWidget);
        comboBox_timer->addItem(QString());
        comboBox_timer->addItem(QString());
        comboBox_timer->addItem(QString());
        comboBox_timer->addItem(QString());
        comboBox_timer->setObjectName(QString::fromUtf8("comboBox_timer"));

        VL_menuSimulation->addWidget(comboBox_timer);


        VL_menu->addLayout(VL_menuSimulation);

        VSpacer_menuSimulationMenuOption = new QSpacerItem(20, 80, QSizePolicy::Minimum, QSizePolicy::Fixed);

        VL_menu->addItem(VSpacer_menuSimulationMenuOption);

        VL_menuOptions = new QVBoxLayout();
        VL_menuOptions->setObjectName(QString::fromUtf8("VL_menuOptions"));
        pushButton_tabCoursOHLCV = new QPushButton(layoutWidget);
        pushButton_tabCoursOHLCV->setObjectName(QString::fromUtf8("pushButton_tabCoursOHLCV"));

        VL_menuOptions->addWidget(pushButton_tabCoursOHLCV);

        pushButton_tabTransaction = new QPushButton(layoutWidget);
        pushButton_tabTransaction->setObjectName(QString::fromUtf8("pushButton_tabTransaction"));

        VL_menuOptions->addWidget(pushButton_tabTransaction);

        pushButton_prendreNote = new QPushButton(layoutWidget);
        pushButton_prendreNote->setObjectName(QString::fromUtf8("pushButton_prendreNote"));

        VL_menuOptions->addWidget(pushButton_prendreNote);


        VL_menu->addLayout(VL_menuOptions);

        frame_chandelier = new QFrame(centralwidget);
        frame_chandelier->setObjectName(QString::fromUtf8("frame_chandelier"));
        frame_chandelier->setGeometry(QRect(180, 40, 671, 301));
        frame_chandelier->setFrameShape(QFrame::StyledPanel);
        frame_chandelier->setFrameShadow(QFrame::Raised);
        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(180, 10, 171, 19));
        HL_indicateur = new QHBoxLayout(layoutWidget1);
        HL_indicateur->setObjectName(QString::fromUtf8("HL_indicateur"));
        HL_indicateur->setContentsMargins(0, 0, 0, 0);
        checkBox_RSI = new QCheckBox(layoutWidget1);
        checkBox_RSI->setObjectName(QString::fromUtf8("checkBox_RSI"));

        HL_indicateur->addWidget(checkBox_RSI);

        checkBox_EMA = new QCheckBox(layoutWidget1);
        checkBox_EMA->setObjectName(QString::fromUtf8("checkBox_EMA"));

        HL_indicateur->addWidget(checkBox_EMA);

        checkBox_MACD = new QCheckBox(layoutWidget1);
        checkBox_MACD->setObjectName(QString::fromUtf8("checkBox_MACD"));

        HL_indicateur->addWidget(checkBox_MACD);

        tabWidget_autres = new QTabWidget(centralwidget);
        tabWidget_autres->setObjectName(QString::fromUtf8("tabWidget_autres"));
        tabWidget_autres->setGeometry(QRect(180, 350, 671, 141));
        tabWidget_autres->setTabsClosable(true);
        tabWidget_autres->setMovable(true);
        tabWidget_autres->setTabBarAutoHide(false);
        tab_RSI = new QWidget();
        tab_RSI->setObjectName(QString::fromUtf8("tab_RSI"));
        tabWidget_autres->addTab(tab_RSI, QString());
        tab_coursOHLVC = new QWidget();
        tab_coursOHLVC->setObjectName(QString::fromUtf8("tab_coursOHLVC"));
        tabWidget_autres->addTab(tab_coursOHLVC, QString());
        MainWindow_modeauto->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow_modeauto);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow_modeauto->setStatusBar(statusbar);

        retranslateUi(MainWindow_modeauto);

        tabWidget_autres->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow_modeauto);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_modeauto)
    {
        MainWindow_modeauto->setWindowTitle(QApplication::translate("MainWindow_modeauto", "MainWindow", nullptr));
        pushButton_retourMenu->setText(QApplication::translate("MainWindow_modeauto", "Retour au menu", nullptr));
        pushButton_sauvegarder->setText(QApplication::translate("MainWindow_modeauto", "Sauvegarder", nullptr));
        pushButton_parametre->setText(QApplication::translate("MainWindow_modeauto", "Parametres", nullptr));
        pushButton_aide->setText(QApplication::translate("MainWindow_modeauto", "Aide", nullptr));
        label_strategie->setText(QApplication::translate("MainWindow_modeauto", "Strategie", nullptr));
        label_montantBase->setText(QApplication::translate("MainWindow_modeauto", "MontantB", nullptr));
        label_montantContrepartie->setText(QApplication::translate("MainWindow_modeauto", "MontantC", nullptr));
        label_broker->setText(QApplication::translate("MainWindow_modeauto", "Broker", nullptr));
        label_date->setText(QApplication::translate("MainWindow_modeauto", "Date", nullptr));
        comboBox_timer->setItemText(0, QApplication::translate("MainWindow_modeauto", "Pause", nullptr));
        comboBox_timer->setItemText(1, QApplication::translate("MainWindow_modeauto", "Avancer", nullptr));
        comboBox_timer->setItemText(2, QApplication::translate("MainWindow_modeauto", "Reculer", nullptr));
        comboBox_timer->setItemText(3, QApplication::translate("MainWindow_modeauto", "D\303\251filer", nullptr));

        pushButton_tabCoursOHLCV->setText(QApplication::translate("MainWindow_modeauto", "Tableau des cours", nullptr));
        pushButton_tabTransaction->setText(QApplication::translate("MainWindow_modeauto", "Tableau des transactions", nullptr));
        pushButton_prendreNote->setText(QApplication::translate("MainWindow_modeauto", "Prendre des notes", nullptr));
        checkBox_RSI->setText(QApplication::translate("MainWindow_modeauto", "RSI", nullptr));
        checkBox_EMA->setText(QApplication::translate("MainWindow_modeauto", "EMA", nullptr));
        checkBox_MACD->setText(QApplication::translate("MainWindow_modeauto", "MACD", nullptr));
        tabWidget_autres->setTabText(tabWidget_autres->indexOf(tab_RSI), QApplication::translate("MainWindow_modeauto", "RSI", nullptr));
        tabWidget_autres->setTabText(tabWidget_autres->indexOf(tab_coursOHLVC), QApplication::translate("MainWindow_modeauto", "coursOHLCV", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_modeauto: public Ui_MainWindow_modeauto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_MODEAUTO_H
