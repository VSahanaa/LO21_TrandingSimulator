/********************************************************************************
** Form generated from reading UI file 'tab_transaction.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB_TRANSACTION_H
#define UI_TAB_TRANSACTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tab_transaction
{
public:
    QTableWidget *tableWidget_transaction;

    void setupUi(QWidget *tab_transaction)
    {
        if (tab_transaction->objectName().isEmpty())
            tab_transaction->setObjectName(QString::fromUtf8("tab_transaction"));
        tab_transaction->resize(631, 289);
        tableWidget_transaction = new QTableWidget(tab_transaction);
        if (tableWidget_transaction->columnCount() < 6)
            tableWidget_transaction->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_transaction->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_transaction->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_transaction->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_transaction->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_transaction->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_transaction->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget_transaction->setObjectName(QString::fromUtf8("tableWidget_transaction"));
        tableWidget_transaction->setGeometry(QRect(10, 10, 611, 271));

        retranslateUi(tab_transaction);

        QMetaObject::connectSlotsByName(tab_transaction);
    } // setupUi

    void retranslateUi(QWidget *tab_transaction)
    {
        tab_transaction->setWindowTitle(QApplication::translate("tab_transaction", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_transaction->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("tab_transaction", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_transaction->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("tab_transaction", "Open Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_transaction->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("tab_transaction", "Hight Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_transaction->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("tab_transaction", "Low Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_transaction->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("tab_transaction", "Close Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_transaction->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("tab_transaction", "Volume", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tab_transaction: public Ui_tab_transaction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB_TRANSACTION_H
