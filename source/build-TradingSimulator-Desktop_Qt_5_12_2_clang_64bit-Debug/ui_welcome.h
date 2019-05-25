/********************************************************************************
** Form generated from reading UI file 'welcome.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOME_H
#define UI_WELCOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Welcome
{
public:
    QStackedWidget *stackedWidget;
    QWidget *Home;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *About;
    QPushButton *Continue;
    QLabel *label;
    QWidget *MainMenu;
    QToolButton *Candlestick;
    QToolButton *Simulation;
    QToolButton *toolButton_2;
    QToolButton *Quit;
    QWidget *Mode;
    QToolButton *Manuel;
    QToolButton *Step;
    QToolButton *Auto;
    QToolButton *Back;
    QWidget *Candle;
    QDialogButtonBox *dispaly_dialog;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *Currency1;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QComboBox *Currency2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *linePath;
    QToolButton *filePath;

    void setupUi(QWidget *Welcome)
    {
        if (Welcome->objectName().isEmpty())
            Welcome->setObjectName(QString::fromUtf8("Welcome"));
        Welcome->resize(360, 360);
        stackedWidget = new QStackedWidget(Welcome);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 360, 360));
        Home = new QWidget();
        Home->setObjectName(QString::fromUtf8("Home"));
        widget = new QWidget(Home);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(60, 150, 269, 120));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(150, 0, 0, 0);
        About = new QPushButton(widget);
        About->setObjectName(QString::fromUtf8("About"));

        verticalLayout->addWidget(About);

        Continue = new QPushButton(widget);
        Continue->setObjectName(QString::fromUtf8("Continue"));

        verticalLayout->addWidget(Continue);

        label = new QLabel(Home);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 221, 101));
        label->setPixmap(QPixmap(QString::fromUtf8(":/TradingSimulator/evolutionCours/icons/welcome.png")));
        label->setScaledContents(true);
        stackedWidget->addWidget(Home);
        MainMenu = new QWidget();
        MainMenu->setObjectName(QString::fromUtf8("MainMenu"));
        Candlestick = new QToolButton(MainMenu);
        Candlestick->setObjectName(QString::fromUtf8("Candlestick"));
        Candlestick->setGeometry(QRect(190, 20, 140, 140));
        Candlestick->setCursor(QCursor(Qt::PointingHandCursor));
        Candlestick->setAutoFillBackground(true);
        Simulation = new QToolButton(MainMenu);
        Simulation->setObjectName(QString::fromUtf8("Simulation"));
        Simulation->setGeometry(QRect(30, 20, 140, 140));
        Simulation->setCursor(QCursor(Qt::PointingHandCursor));
        toolButton_2 = new QToolButton(MainMenu);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setGeometry(QRect(30, 180, 140, 140));
        toolButton_2->setCursor(QCursor(Qt::PointingHandCursor));
        Quit = new QToolButton(MainMenu);
        Quit->setObjectName(QString::fromUtf8("Quit"));
        Quit->setGeometry(QRect(190, 180, 140, 140));
        Quit->setCursor(QCursor(Qt::PointingHandCursor));
        stackedWidget->addWidget(MainMenu);
        Mode = new QWidget();
        Mode->setObjectName(QString::fromUtf8("Mode"));
        Manuel = new QToolButton(Mode);
        Manuel->setObjectName(QString::fromUtf8("Manuel"));
        Manuel->setGeometry(QRect(30, 20, 140, 140));
        Manuel->setCursor(QCursor(Qt::PointingHandCursor));
        Step = new QToolButton(Mode);
        Step->setObjectName(QString::fromUtf8("Step"));
        Step->setGeometry(QRect(190, 20, 140, 140));
        Step->setCursor(QCursor(Qt::PointingHandCursor));
        Auto = new QToolButton(Mode);
        Auto->setObjectName(QString::fromUtf8("Auto"));
        Auto->setGeometry(QRect(30, 180, 140, 140));
        Auto->setCursor(QCursor(Qt::PointingHandCursor));
        Back = new QToolButton(Mode);
        Back->setObjectName(QString::fromUtf8("Back"));
        Back->setGeometry(QRect(190, 180, 140, 140));
        Back->setCursor(QCursor(Qt::PointingHandCursor));
        stackedWidget->addWidget(Mode);
        Candle = new QWidget();
        Candle->setObjectName(QString::fromUtf8("Candle"));
        dispaly_dialog = new QDialogButtonBox(Candle);
        dispaly_dialog->setObjectName(QString::fromUtf8("dispaly_dialog"));
        dispaly_dialog->setGeometry(QRect(160, 300, 164, 32));
        dispaly_dialog->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        widget1 = new QWidget(Candle);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(30, 80, 291, 191));
        verticalLayout_3 = new QVBoxLayout(widget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, 0, -1);
        label_3 = new QLabel(widget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        Currency1 = new QComboBox(widget1);
        Currency1->setObjectName(QString::fromUtf8("Currency1"));

        horizontalLayout_3->addWidget(Currency1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(widget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        Currency2 = new QComboBox(widget1);
        Currency2->setObjectName(QString::fromUtf8("Currency2"));

        horizontalLayout_2->addWidget(Currency2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(widget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        linePath = new QLineEdit(widget1);
        linePath->setObjectName(QString::fromUtf8("linePath"));

        horizontalLayout->addWidget(linePath);

        filePath = new QToolButton(widget1);
        filePath->setObjectName(QString::fromUtf8("filePath"));

        horizontalLayout->addWidget(filePath);


        verticalLayout_3->addLayout(horizontalLayout);

        stackedWidget->addWidget(Candle);

        retranslateUi(Welcome);

        QMetaObject::connectSlotsByName(Welcome);
    } // setupUi

    void retranslateUi(QWidget *Welcome)
    {
        Welcome->setWindowTitle(QApplication::translate("Welcome", "Trading Simulator", nullptr));
        About->setText(QApplication::translate("Welcome", "About", nullptr));
        Continue->setText(QApplication::translate("Welcome", "Continue", nullptr));
        label->setText(QString());
#ifndef QT_NO_TOOLTIP
        Candlestick->setToolTip(QApplication::translate("Welcome", "Display", nullptr));
#endif // QT_NO_TOOLTIP
        Candlestick->setText(QApplication::translate("Welcome", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        Simulation->setToolTip(QApplication::translate("Welcome", "Simulation", nullptr));
#endif // QT_NO_TOOLTIP
        Simulation->setText(QApplication::translate("Welcome", "...", nullptr));
        toolButton_2->setText(QApplication::translate("Welcome", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        Quit->setToolTip(QApplication::translate("Welcome", "Quit", nullptr));
#endif // QT_NO_TOOLTIP
        Quit->setText(QApplication::translate("Welcome", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        Manuel->setToolTip(QApplication::translate("Welcome", "Manuel mode", nullptr));
#endif // QT_NO_TOOLTIP
        Manuel->setText(QApplication::translate("Welcome", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        Step->setToolTip(QApplication::translate("Welcome", "Step by step", nullptr));
#endif // QT_NO_TOOLTIP
        Step->setText(QApplication::translate("Welcome", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        Auto->setToolTip(QApplication::translate("Welcome", "Auto Mode", nullptr));
#endif // QT_NO_TOOLTIP
        Auto->setText(QApplication::translate("Welcome", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        Back->setToolTip(QApplication::translate("Welcome", "Back", nullptr));
#endif // QT_NO_TOOLTIP
        Back->setText(QApplication::translate("Welcome", "...", nullptr));
        label_3->setText(QApplication::translate("Welcome", "Currency 1", nullptr));
        label_4->setText(QApplication::translate("Welcome", "Currency 2", nullptr));
        label_2->setText(QApplication::translate("Welcome", "File Path", nullptr));
        filePath->setText(QApplication::translate("Welcome", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Welcome: public Ui_Welcome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOME_H
