/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Info
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_6;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_8;

    void setupUi(QDialog *Info)
    {
        if (Info->objectName().isEmpty())
            Info->setObjectName(QString::fromUtf8("Info"));
        Info->resize(400, 300);
        buttonBox = new QDialogButtonBox(Info);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 260, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        widget = new QWidget(Info);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(120, 80, 211, 124));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout->addWidget(label_7);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout->addWidget(label_6);

        widget1 = new QWidget(Info);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(40, 30, 136, 201));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setLineWidth(3);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(widget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        label_8 = new QLabel(widget1);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_2->addWidget(label_8);


        retranslateUi(Info);
        QObject::connect(buttonBox, SIGNAL(accepted()), Info, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Info, SLOT(reject()));

        QMetaObject::connectSlotsByName(Info);
    } // setupUi

    void retranslateUi(QDialog *Info)
    {
        Info->setWindowTitle(QApplication::translate("Info", "Dialog", nullptr));
        label_3->setText(QApplication::translate("Info", "Gaye Hamza", nullptr));
        label_4->setText(QApplication::translate("Info", "Minh-Nghia Duong", nullptr));
        label_5->setText(QApplication::translate("Info", "Vijayakumar Sahanaa", nullptr));
        label_7->setText(QApplication::translate("Info", "Xu Jiali", nullptr));
        label_6->setText(QApplication::translate("Info", "Zhang Chenchao", nullptr));
        label->setText(QApplication::translate("Info", "Current Version: v0.0.0", nullptr));
        label_2->setText(QApplication::translate("Info", "Developers:", nullptr));
        label_8->setText(QApplication::translate("Info", "2019 June", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Info: public Ui_Info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H