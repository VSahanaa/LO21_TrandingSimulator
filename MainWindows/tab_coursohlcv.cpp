#include "tab_coursohlcv.h"
#include "ui_tab_coursohlcv.h"


tab_coursOHLCV::tab_coursOHLCV(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tab_coursOHLCV)
{
    ui->setupUi(this);
    //ui->tableWidget_coursOHLCV->setRowCount(//nb_coursOHLCV);
    //ui->tableWidget_coursOHLCV->setColumnCount(6);

    /*
    int i=0;
    for (evolutionCours::iterator it=it.begin(); it=it.end(); it++)
    {
        ui->tableWidget_coursOHLCV->setItem(i, 0, new QTableWidgetItem(//getdate()));
        ui->tableWidget_coursOHLCV->setItem(i, 1, new QTableWidgetItem(//getdate()));
        ui->tableWidget_coursOHLCV->setItem(i, 2, new QTableWidgetItem(//getdate()));
        ui->tableWidget_coursOHLCV->setItem(i, 3, new QTableWidgetItem(//getdate()));
        ui->tableWidget_coursOHLCV->setItem(i, 4, new QTableWidgetItem(//getdate()));
        ui->tableWidget_coursOHLCV->setItem(i, 5, new QTableWidgetItem(//getdate()));
        i++;
    }
    */
}

tab_coursOHLCV::~tab_coursOHLCV()
{
    delete ui;
}
