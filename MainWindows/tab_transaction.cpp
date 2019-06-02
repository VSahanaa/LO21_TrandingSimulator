#include "tab_transaction.h"
#include "ui_tab_transaction.h"

tab_transaction::tab_transaction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tab_transaction)
{
    ui->setupUi(this);
    //ui->tableWidget_transaction->setRowCount(//nb_transaction);
    //ui->tableWidget_transaction->setColumnCount(4);

    /*
    int i=0;
    for (evolutionCours::iterator it=it.begin(); it=it.end(); it++)
    {
        ui->tableWidget_transaction->setItem(i, 0, new QTableWidgetItem(//getdate()));
        ui->tableWidget_transaction->setItem(i, 1, new QTableWidgetItem(//decision));
        ui->tableWidget_transaction->setItem(i, 2, new QTableWidgetItem(//montant));
        ui->tableWidget_transaction->setItem(i, 3, new QTableWidgetItem(//resultat));
        i++;
    }
    */
}

tab_transaction::~tab_transaction()
{
    delete ui;
}
