/********************************************************************************
** Form generated from reading UI file 'tab_coursohlcv.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB_COURSOHLCV_H
#define UI_TAB_COURSOHLCV_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tab_coursOHLCV
{
public:
    QTableWidget *tableWidget_coursOHLCV;

    void setupUi(QWidget *tab_coursOHLCV)
    {
        if (tab_coursOHLCV->objectName().isEmpty())
            tab_coursOHLCV->setObjectName(QString::fromUtf8("tab_coursOHLCV"));
        tab_coursOHLCV->resize(630, 300);
        tableWidget_coursOHLCV = new QTableWidget(tab_coursOHLCV);
        if (tableWidget_coursOHLCV->columnCount() < 6)
            tableWidget_coursOHLCV->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_coursOHLCV->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_coursOHLCV->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_coursOHLCV->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_coursOHLCV->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_coursOHLCV->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_coursOHLCV->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget_coursOHLCV->setObjectName(QString::fromUtf8("tableWidget_coursOHLCV"));
        tableWidget_coursOHLCV->setGeometry(QRect(10, 10, 611, 271));

        retranslateUi(tab_coursOHLCV);

        QMetaObject::connectSlotsByName(tab_coursOHLCV);
    } // setupUi

    void retranslateUi(QWidget *tab_coursOHLCV)
    {
        tab_coursOHLCV->setWindowTitle(QApplication::translate("tab_coursOHLCV", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_coursOHLCV->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("tab_coursOHLCV", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_coursOHLCV->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("tab_coursOHLCV", "Open Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_coursOHLCV->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("tab_coursOHLCV", "Hight Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_coursOHLCV->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("tab_coursOHLCV", "Low Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_coursOHLCV->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("tab_coursOHLCV", "Close Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_coursOHLCV->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("tab_coursOHLCV", "Volume", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tab_coursOHLCV: public Ui_tab_coursOHLCV {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB_COURSOHLCV_H
