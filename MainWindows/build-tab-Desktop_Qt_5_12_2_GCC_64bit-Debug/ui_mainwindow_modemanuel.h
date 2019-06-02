/********************************************************************************
** Form generated from reading UI file 'mainwindow_modemanuel.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_MODEMANUEL_H
#define UI_MAINWINDOW_MODEMANUEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow_modemanuel
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
    QSpacerItem *VSpacer_menuFichierTimer;
    QVBoxLayout *VL_menuTransaction;
    QHBoxLayout *HL_infoMontant;
    QLabel *label_montantBase;
    QLabel *label_montantContrepartie;
    QLabel *label_broker;
    QHBoxLayout *HL_infoDate;
    QLabel *label_date;
    QDateEdit *dateEdit_date;
    QLineEdit *lineEdit_montant;
    QHBoxLayout *HL_achatvente;
    QPushButton *pushButton_achat;
    QPushButton *pushButton_vente;
    QPushButton *pushButton_annulerTransaction;
    QSpacerItem *VSpacer_menuTransactionMenuOption;
    QVBoxLayout *VL_menuOptions;
    QPushButton *pushButton_tabCoursOHLCV;
    QPushButton *pushButton_tabTransaction;
    QPushButton *pushButton_prendreNote;
    QWidget *layoutWidget_2;
    QHBoxLayout *HL_indicateur;
    QCheckBox *checkBox_RSI;
    QCheckBox *checkBox_EMA;
    QCheckBox *checkBox_MACD;
    QFrame *frame_chandelier;
    QTabWidget *tabWidget_autres;
    QWidget *tab_RSI;
    QWidget *tab_coursOHLVC;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow_modemanuel)
    {
        if (MainWindow_modemanuel->objectName().isEmpty())
            MainWindow_modemanuel->setObjectName(QString::fromUtf8("MainWindow_modemanuel"));
        MainWindow_modemanuel->resize(862, 527);
        centralwidget = new QWidget(MainWindow_modemanuel);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 162, 492));
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

        VSpacer_menuFichierTimer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);

        VL_menu->addItem(VSpacer_menuFichierTimer);

        VL_menuTransaction = new QVBoxLayout();
        VL_menuTransaction->setObjectName(QString::fromUtf8("VL_menuTransaction"));
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


        VL_menuTransaction->addLayout(HL_infoMontant);

        HL_infoDate = new QHBoxLayout();
        HL_infoDate->setObjectName(QString::fromUtf8("HL_infoDate"));
        label_date = new QLabel(layoutWidget);
        label_date->setObjectName(QString::fromUtf8("label_date"));

        HL_infoDate->addWidget(label_date);

        dateEdit_date = new QDateEdit(layoutWidget);
        dateEdit_date->setObjectName(QString::fromUtf8("dateEdit_date"));

        HL_infoDate->addWidget(dateEdit_date);


        VL_menuTransaction->addLayout(HL_infoDate);

        lineEdit_montant = new QLineEdit(layoutWidget);
        lineEdit_montant->setObjectName(QString::fromUtf8("lineEdit_montant"));

        VL_menuTransaction->addWidget(lineEdit_montant);

        HL_achatvente = new QHBoxLayout();
        HL_achatvente->setObjectName(QString::fromUtf8("HL_achatvente"));
        pushButton_achat = new QPushButton(layoutWidget);
        pushButton_achat->setObjectName(QString::fromUtf8("pushButton_achat"));

        HL_achatvente->addWidget(pushButton_achat);

        pushButton_vente = new QPushButton(layoutWidget);
        pushButton_vente->setObjectName(QString::fromUtf8("pushButton_vente"));

        HL_achatvente->addWidget(pushButton_vente);


        VL_menuTransaction->addLayout(HL_achatvente);

        pushButton_annulerTransaction = new QPushButton(layoutWidget);
        pushButton_annulerTransaction->setObjectName(QString::fromUtf8("pushButton_annulerTransaction"));

        VL_menuTransaction->addWidget(pushButton_annulerTransaction);


        VL_menu->addLayout(VL_menuTransaction);

        VSpacer_menuTransactionMenuOption = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);

        VL_menu->addItem(VSpacer_menuTransactionMenuOption);

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

        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(190, 10, 171, 19));
        HL_indicateur = new QHBoxLayout(layoutWidget_2);
        HL_indicateur->setObjectName(QString::fromUtf8("HL_indicateur"));
        HL_indicateur->setContentsMargins(0, 0, 0, 0);
        checkBox_RSI = new QCheckBox(layoutWidget_2);
        checkBox_RSI->setObjectName(QString::fromUtf8("checkBox_RSI"));

        HL_indicateur->addWidget(checkBox_RSI);

        checkBox_EMA = new QCheckBox(layoutWidget_2);
        checkBox_EMA->setObjectName(QString::fromUtf8("checkBox_EMA"));

        HL_indicateur->addWidget(checkBox_EMA);

        checkBox_MACD = new QCheckBox(layoutWidget_2);
        checkBox_MACD->setObjectName(QString::fromUtf8("checkBox_MACD"));

        HL_indicateur->addWidget(checkBox_MACD);

        frame_chandelier = new QFrame(centralwidget);
        frame_chandelier->setObjectName(QString::fromUtf8("frame_chandelier"));
        frame_chandelier->setGeometry(QRect(180, 40, 671, 301));
        frame_chandelier->setFrameShape(QFrame::StyledPanel);
        frame_chandelier->setFrameShadow(QFrame::Raised);
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
        MainWindow_modemanuel->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow_modemanuel);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow_modemanuel->setStatusBar(statusbar);

        retranslateUi(MainWindow_modemanuel);

        tabWidget_autres->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow_modemanuel);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_modemanuel)
    {
        MainWindow_modemanuel->setWindowTitle(QApplication::translate("MainWindow_modemanuel", "MainWindow", nullptr));
        pushButton_retourMenu->setText(QApplication::translate("MainWindow_modemanuel", "Retour au menu", nullptr));
        pushButton_sauvegarder->setText(QApplication::translate("MainWindow_modemanuel", "Sauvegarder", nullptr));
        pushButton_parametre->setText(QApplication::translate("MainWindow_modemanuel", "Parametres", nullptr));
        pushButton_aide->setText(QApplication::translate("MainWindow_modemanuel", "Aide", nullptr));
        label_montantBase->setText(QApplication::translate("MainWindow_modemanuel", "MontantB", nullptr));
        label_montantContrepartie->setText(QApplication::translate("MainWindow_modemanuel", "MontantC", nullptr));
        label_broker->setText(QApplication::translate("MainWindow_modemanuel", "Broker", nullptr));
        label_date->setText(QApplication::translate("MainWindow_modemanuel", "Date", nullptr));
        pushButton_achat->setText(QApplication::translate("MainWindow_modemanuel", "Achat", nullptr));
        pushButton_vente->setText(QApplication::translate("MainWindow_modemanuel", "Vente", nullptr));
        pushButton_annulerTransaction->setText(QApplication::translate("MainWindow_modemanuel", "Annuler transaction", nullptr));
        pushButton_tabCoursOHLCV->setText(QApplication::translate("MainWindow_modemanuel", "Tableau des cours", nullptr));
        pushButton_tabTransaction->setText(QApplication::translate("MainWindow_modemanuel", "Tableau des transactions", nullptr));
        pushButton_prendreNote->setText(QApplication::translate("MainWindow_modemanuel", "Prendre des notes", nullptr));
        checkBox_RSI->setText(QApplication::translate("MainWindow_modemanuel", "RSI", nullptr));
        checkBox_EMA->setText(QApplication::translate("MainWindow_modemanuel", "EMA", nullptr));
        checkBox_MACD->setText(QApplication::translate("MainWindow_modemanuel", "MACD", nullptr));
        tabWidget_autres->setTabText(tabWidget_autres->indexOf(tab_RSI), QApplication::translate("MainWindow_modemanuel", "RSI", nullptr));
        tabWidget_autres->setTabText(tabWidget_autres->indexOf(tab_coursOHLVC), QApplication::translate("MainWindow_modemanuel", "coursOHLCV", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_modemanuel: public Ui_MainWindow_modemanuel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_MODEMANUEL_H
