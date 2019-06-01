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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *HL_Menu_2;
    QVBoxLayout *VL_Fichier;
    QTextBrowser *textBrowser_Fichier;
    QPushButton *pushButtonRetourMenu;
    QPushButton *pushButton_Sauv;
    QPushButton *pushButton_Param;
    QVBoxLayout *VL_afficher;
    QTextBrowser *textBrowser_aff;
    QPushButton *pushButton_curseur;
    QPushButton *pushButton_indicateur;
    QPushButton *pushButton_tabCours;
    QVBoxLayout *VL_transaction;
    QTextBrowser *textBrowser_transaction;
    QPushButton *pushButton_nouvelletransaction;
    QPushButton *pushButton_annuler;
    QPushButton *pushButton_tabTransaction;
    QVBoxLayout *VL_simulation;
    QTextBrowser *textBrowser_simulation;
    QPushButton *pushButton_avancer;
    QPushButton *pushButton_reculer;
    QHBoxLayout *HL_simulation_play;
    QPushButton *pushButton_defiler;
    QPushButton *pushButton_pause;
    QVBoxLayout *VL_notes_2;
    QTextBrowser *textBrowser_notes_2;
    QPushButton *pushButton_Lire_2;
    QPushButton *pushButton_modifier_2;
    QPushButton *pushButton_fichier_2;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser_notes_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QFrame *frame_chandelier;
    QFrame *frame_RSI;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(797, 523);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 0, 771, 169));
        HL_Menu_2 = new QHBoxLayout(layoutWidget);
        HL_Menu_2->setSpacing(6);
        HL_Menu_2->setContentsMargins(11, 11, 11, 11);
        HL_Menu_2->setObjectName(QString::fromUtf8("HL_Menu_2"));
        HL_Menu_2->setContentsMargins(0, 0, 0, 0);
        VL_Fichier = new QVBoxLayout();
        VL_Fichier->setSpacing(6);
        VL_Fichier->setObjectName(QString::fromUtf8("VL_Fichier"));
        textBrowser_Fichier = new QTextBrowser(layoutWidget);
        textBrowser_Fichier->setObjectName(QString::fromUtf8("textBrowser_Fichier"));

        VL_Fichier->addWidget(textBrowser_Fichier);

        pushButtonRetourMenu = new QPushButton(layoutWidget);
        pushButtonRetourMenu->setObjectName(QString::fromUtf8("pushButtonRetourMenu"));

        VL_Fichier->addWidget(pushButtonRetourMenu);

        pushButton_Sauv = new QPushButton(layoutWidget);
        pushButton_Sauv->setObjectName(QString::fromUtf8("pushButton_Sauv"));

        VL_Fichier->addWidget(pushButton_Sauv);

        pushButton_Param = new QPushButton(layoutWidget);
        pushButton_Param->setObjectName(QString::fromUtf8("pushButton_Param"));

        VL_Fichier->addWidget(pushButton_Param);


        HL_Menu_2->addLayout(VL_Fichier);

        VL_afficher = new QVBoxLayout();
        VL_afficher->setSpacing(6);
        VL_afficher->setObjectName(QString::fromUtf8("VL_afficher"));
        textBrowser_aff = new QTextBrowser(layoutWidget);
        textBrowser_aff->setObjectName(QString::fromUtf8("textBrowser_aff"));

        VL_afficher->addWidget(textBrowser_aff);

        pushButton_curseur = new QPushButton(layoutWidget);
        pushButton_curseur->setObjectName(QString::fromUtf8("pushButton_curseur"));

        VL_afficher->addWidget(pushButton_curseur);

        pushButton_indicateur = new QPushButton(layoutWidget);
        pushButton_indicateur->setObjectName(QString::fromUtf8("pushButton_indicateur"));

        VL_afficher->addWidget(pushButton_indicateur);

        pushButton_tabCours = new QPushButton(layoutWidget);
        pushButton_tabCours->setObjectName(QString::fromUtf8("pushButton_tabCours"));

        VL_afficher->addWidget(pushButton_tabCours);


        HL_Menu_2->addLayout(VL_afficher);

        VL_transaction = new QVBoxLayout();
        VL_transaction->setSpacing(6);
        VL_transaction->setObjectName(QString::fromUtf8("VL_transaction"));
        textBrowser_transaction = new QTextBrowser(layoutWidget);
        textBrowser_transaction->setObjectName(QString::fromUtf8("textBrowser_transaction"));

        VL_transaction->addWidget(textBrowser_transaction);

        pushButton_nouvelletransaction = new QPushButton(layoutWidget);
        pushButton_nouvelletransaction->setObjectName(QString::fromUtf8("pushButton_nouvelletransaction"));

        VL_transaction->addWidget(pushButton_nouvelletransaction);

        pushButton_annuler = new QPushButton(layoutWidget);
        pushButton_annuler->setObjectName(QString::fromUtf8("pushButton_annuler"));

        VL_transaction->addWidget(pushButton_annuler);

        pushButton_tabTransaction = new QPushButton(layoutWidget);
        pushButton_tabTransaction->setObjectName(QString::fromUtf8("pushButton_tabTransaction"));

        VL_transaction->addWidget(pushButton_tabTransaction);


        HL_Menu_2->addLayout(VL_transaction);

        VL_simulation = new QVBoxLayout();
        VL_simulation->setSpacing(6);
        VL_simulation->setObjectName(QString::fromUtf8("VL_simulation"));
        textBrowser_simulation = new QTextBrowser(layoutWidget);
        textBrowser_simulation->setObjectName(QString::fromUtf8("textBrowser_simulation"));

        VL_simulation->addWidget(textBrowser_simulation);

        pushButton_avancer = new QPushButton(layoutWidget);
        pushButton_avancer->setObjectName(QString::fromUtf8("pushButton_avancer"));

        VL_simulation->addWidget(pushButton_avancer);

        pushButton_reculer = new QPushButton(layoutWidget);
        pushButton_reculer->setObjectName(QString::fromUtf8("pushButton_reculer"));

        VL_simulation->addWidget(pushButton_reculer);

        HL_simulation_play = new QHBoxLayout();
        HL_simulation_play->setSpacing(6);
        HL_simulation_play->setObjectName(QString::fromUtf8("HL_simulation_play"));
        pushButton_defiler = new QPushButton(layoutWidget);
        pushButton_defiler->setObjectName(QString::fromUtf8("pushButton_defiler"));

        HL_simulation_play->addWidget(pushButton_defiler);

        pushButton_pause = new QPushButton(layoutWidget);
        pushButton_pause->setObjectName(QString::fromUtf8("pushButton_pause"));

        HL_simulation_play->addWidget(pushButton_pause);


        VL_simulation->addLayout(HL_simulation_play);


        HL_Menu_2->addLayout(VL_simulation);

        VL_notes_2 = new QVBoxLayout();
        VL_notes_2->setSpacing(6);
        VL_notes_2->setObjectName(QString::fromUtf8("VL_notes_2"));
        textBrowser_notes_2 = new QTextBrowser(layoutWidget);
        textBrowser_notes_2->setObjectName(QString::fromUtf8("textBrowser_notes_2"));

        VL_notes_2->addWidget(textBrowser_notes_2);

        pushButton_Lire_2 = new QPushButton(layoutWidget);
        pushButton_Lire_2->setObjectName(QString::fromUtf8("pushButton_Lire_2"));

        VL_notes_2->addWidget(pushButton_Lire_2);

        pushButton_modifier_2 = new QPushButton(layoutWidget);
        pushButton_modifier_2->setObjectName(QString::fromUtf8("pushButton_modifier_2"));

        VL_notes_2->addWidget(pushButton_modifier_2);

        pushButton_fichier_2 = new QPushButton(layoutWidget);
        pushButton_fichier_2->setObjectName(QString::fromUtf8("pushButton_fichier_2"));

        VL_notes_2->addWidget(pushButton_fichier_2);


        HL_Menu_2->addLayout(VL_notes_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser_notes_4 = new QTextBrowser(layoutWidget);
        textBrowser_notes_4->setObjectName(QString::fromUtf8("textBrowser_notes_4"));

        verticalLayout->addWidget(textBrowser_notes_4);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);


        HL_Menu_2->addLayout(verticalLayout);

        frame_chandelier = new QFrame(centralWidget);
        frame_chandelier->setObjectName(QString::fromUtf8("frame_chandelier"));
        frame_chandelier->setGeometry(QRect(10, 120, 781, 211));
        frame_chandelier->setFrameShape(QFrame::StyledPanel);
        frame_chandelier->setFrameShadow(QFrame::Raised);
        frame_RSI = new QFrame(centralWidget);
        frame_RSI->setObjectName(QString::fromUtf8("frame_RSI"));
        frame_RSI->setGeometry(QRect(9, 339, 781, 131));
        frame_RSI->setFrameShape(QFrame::StyledPanel);
        frame_RSI->setFrameShadow(QFrame::Raised);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 797, 22));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        textBrowser_Fichier->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:7pt;\">FICHIER</span></p></body></html>", nullptr));
        pushButtonRetourMenu->setText(QApplication::translate("MainWindow", "Retour menu", nullptr));
        pushButton_Sauv->setText(QApplication::translate("MainWindow", "Sauvegarder", nullptr));
        pushButton_Param->setText(QApplication::translate("MainWindow", "Parametres", nullptr));
        textBrowser_aff->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:7pt;\">AFFICHER</span></p></body></html>", nullptr));
        pushButton_curseur->setText(QApplication::translate("MainWindow", "curseur", nullptr));
        pushButton_indicateur->setText(QApplication::translate("MainWindow", "Indicateur", nullptr));
        pushButton_tabCours->setText(QApplication::translate("MainWindow", "Tableau cours", nullptr));
        textBrowser_transaction->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:7pt;\">TRANSACTION</span></p></body></html>", nullptr));
        pushButton_nouvelletransaction->setText(QApplication::translate("MainWindow", "Nouvelle ", nullptr));
        pushButton_annuler->setText(QApplication::translate("MainWindow", "Annuler", nullptr));
        pushButton_tabTransaction->setText(QApplication::translate("MainWindow", "Historique", nullptr));
        textBrowser_simulation->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:7pt;\">SIMULATION</span></p></body></html>", nullptr));
        pushButton_avancer->setText(QApplication::translate("MainWindow", "Avancer", nullptr));
        pushButton_reculer->setText(QApplication::translate("MainWindow", "Reculer", nullptr));
        pushButton_defiler->setText(QApplication::translate("MainWindow", "D\303\251filer", nullptr));
        pushButton_pause->setText(QApplication::translate("MainWindow", "Pause", nullptr));
        textBrowser_notes_2->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:7pt;\">NOTES</span></p></body></html>", nullptr));
        pushButton_Lire_2->setText(QApplication::translate("MainWindow", "Lire", nullptr));
        pushButton_modifier_2->setText(QApplication::translate("MainWindow", "Modifier", nullptr));
        pushButton_fichier_2->setText(QApplication::translate("MainWindow", "Fichier", nullptr));
        textBrowser_notes_4->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt;\">AUTRES</span></p></body></html>", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "Mise a jour", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Autres", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "Autres", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
