/********************************************************************************
** Form generated from reading UI file 'mainwindow_modepas.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_MODEPAS_H
#define UI_MAINWINDOW_MODEPAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
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

class Ui_MainWindow_modepas
{
public:
    QWidget *centralwidget;
    QFrame *frame_chandelier;
    QWidget *layoutWidget;
    QVBoxLayout *VL_menu;
    QVBoxLayout *VL_menuFichier;
    QPushButton *pushButton_retourMenu;
    QPushButton *pushButton_sauvegarder;
    QPushButton *pushButton_parametre;
    QPushButton *pushButton_aide;
    QSpacerItem *VSpacer_menuFichierTimer;
    QComboBox *comboBox_timer;
    QSpacerItem *VSpacer_TimerMenuTransaction;
    QVBoxLayout *VL_menuTransaction;
    QHBoxLayout *HL_infoMontant;
    QLabel *label_montantBase;
    QLabel *label_montantContrepartie;
    QLabel *label_broker;
    QHBoxLayout *HL_infoOpen;
    QLabel *label_date;
    QLabel *label_openPrice;
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
    QWidget *layoutWidget1;
    QHBoxLayout *HL_menuIndicateur;
    QCheckBox *checkBox_RSI;
    QCheckBox *checkBox_EMA;
    QCheckBox *checkBox_MACD;
    QTabWidget *tabWidget_autres;
    QWidget *tab_RSI;
    QWidget *tab_coursOHLVC;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow_modepas)
    {
        if (MainWindow_modepas->objectName().isEmpty())
            MainWindow_modepas->setObjectName(QString::fromUtf8("MainWindow_modepas"));
        MainWindow_modepas->resize(858, 524);
        centralwidget = new QWidget(MainWindow_modepas);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame_chandelier = new QFrame(centralwidget);
        frame_chandelier->setObjectName(QString::fromUtf8("frame_chandelier"));
        frame_chandelier->setGeometry(QRect(180, 40, 671, 301));
        frame_chandelier->setFrameShape(QFrame::StyledPanel);
        frame_chandelier->setFrameShadow(QFrame::Raised);
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

        VSpacer_menuFichierTimer = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Fixed);

        VL_menu->addItem(VSpacer_menuFichierTimer);

        comboBox_timer = new QComboBox(layoutWidget);
        comboBox_timer->addItem(QString());
        comboBox_timer->addItem(QString());
        comboBox_timer->addItem(QString());
        comboBox_timer->addItem(QString());
        comboBox_timer->setObjectName(QString::fromUtf8("comboBox_timer"));

        VL_menu->addWidget(comboBox_timer);

        VSpacer_TimerMenuTransaction = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Fixed);

        VL_menu->addItem(VSpacer_TimerMenuTransaction);

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

        HL_infoOpen = new QHBoxLayout();
        HL_infoOpen->setObjectName(QString::fromUtf8("HL_infoOpen"));
        label_date = new QLabel(layoutWidget);
        label_date->setObjectName(QString::fromUtf8("label_date"));

        HL_infoOpen->addWidget(label_date);

        label_openPrice = new QLabel(layoutWidget);
        label_openPrice->setObjectName(QString::fromUtf8("label_openPrice"));

        HL_infoOpen->addWidget(label_openPrice);


        VL_menuTransaction->addLayout(HL_infoOpen);

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

        VSpacer_menuTransactionMenuOption = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Fixed);

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

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(190, 10, 181, 19));
        HL_menuIndicateur = new QHBoxLayout(layoutWidget1);
        HL_menuIndicateur->setObjectName(QString::fromUtf8("HL_menuIndicateur"));
        HL_menuIndicateur->setContentsMargins(0, 0, 0, 0);
        checkBox_RSI = new QCheckBox(layoutWidget1);
        checkBox_RSI->setObjectName(QString::fromUtf8("checkBox_RSI"));

        HL_menuIndicateur->addWidget(checkBox_RSI);

        checkBox_EMA = new QCheckBox(layoutWidget1);
        checkBox_EMA->setObjectName(QString::fromUtf8("checkBox_EMA"));

        HL_menuIndicateur->addWidget(checkBox_EMA);

        checkBox_MACD = new QCheckBox(layoutWidget1);
        checkBox_MACD->setObjectName(QString::fromUtf8("checkBox_MACD"));

        HL_menuIndicateur->addWidget(checkBox_MACD);

        tabWidget_autres = new QTabWidget(centralwidget);
        tabWidget_autres->setObjectName(QString::fromUtf8("tabWidget_autres"));
        tabWidget_autres->setGeometry(QRect(176, 349, 671, 141));
        tabWidget_autres->setTabsClosable(true);
        tabWidget_autres->setMovable(true);
        tabWidget_autres->setTabBarAutoHide(false);
        tab_RSI = new QWidget();
        tab_RSI->setObjectName(QString::fromUtf8("tab_RSI"));
        tabWidget_autres->addTab(tab_RSI, QString());
        tab_coursOHLVC = new QWidget();
        tab_coursOHLVC->setObjectName(QString::fromUtf8("tab_coursOHLVC"));
        tabWidget_autres->addTab(tab_coursOHLVC, QString());
        MainWindow_modepas->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow_modepas);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow_modepas->setStatusBar(statusbar);

        retranslateUi(MainWindow_modepas);

        tabWidget_autres->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow_modepas);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_modepas)
    {
        MainWindow_modepas->setWindowTitle(QApplication::translate("MainWindow_modepas", "MainWindow", nullptr));
        pushButton_retourMenu->setText(QApplication::translate("MainWindow_modepas", "Retour au menu", nullptr));
        pushButton_sauvegarder->setText(QApplication::translate("MainWindow_modepas", "Sauvegarder", nullptr));
        pushButton_parametre->setText(QApplication::translate("MainWindow_modepas", "Parametres", nullptr));
        pushButton_aide->setText(QApplication::translate("MainWindow_modepas", "Aide", nullptr));
        comboBox_timer->setItemText(0, QApplication::translate("MainWindow_modepas", "Pause", nullptr));
        comboBox_timer->setItemText(1, QApplication::translate("MainWindow_modepas", "Avancer", nullptr));
        comboBox_timer->setItemText(2, QApplication::translate("MainWindow_modepas", "Reculer", nullptr));
        comboBox_timer->setItemText(3, QApplication::translate("MainWindow_modepas", "D\303\251filer", nullptr));

        label_montantBase->setText(QApplication::translate("MainWindow_modepas", "MontantB", nullptr));
        label_montantContrepartie->setText(QApplication::translate("MainWindow_modepas", "MontantC", nullptr));
        label_broker->setText(QApplication::translate("MainWindow_modepas", "Broker", nullptr));
        label_date->setText(QApplication::translate("MainWindow_modepas", "Date", nullptr));
        label_openPrice->setText(QApplication::translate("MainWindow_modepas", "OpenPrice", nullptr));
        pushButton_achat->setText(QApplication::translate("MainWindow_modepas", "Achat", nullptr));
        pushButton_vente->setText(QApplication::translate("MainWindow_modepas", "Vente", nullptr));
        pushButton_annulerTransaction->setText(QApplication::translate("MainWindow_modepas", "Annuler transaction", nullptr));
        pushButton_tabCoursOHLCV->setText(QApplication::translate("MainWindow_modepas", "Tableau des cours", nullptr));
        pushButton_tabTransaction->setText(QApplication::translate("MainWindow_modepas", "Tableau des transactions", nullptr));
        pushButton_prendreNote->setText(QApplication::translate("MainWindow_modepas", "Prendre des notes", nullptr));
        checkBox_RSI->setText(QApplication::translate("MainWindow_modepas", "RSI", nullptr));
        checkBox_EMA->setText(QApplication::translate("MainWindow_modepas", "EMA", nullptr));
        checkBox_MACD->setText(QApplication::translate("MainWindow_modepas", "MACD", nullptr));
        tabWidget_autres->setTabText(tabWidget_autres->indexOf(tab_RSI), QApplication::translate("MainWindow_modepas", "RSI", nullptr));
        tabWidget_autres->setTabText(tabWidget_autres->indexOf(tab_coursOHLVC), QApplication::translate("MainWindow_modepas", "coursOHLCV", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_modepas: public Ui_MainWindow_modepas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_MODEPAS_H
