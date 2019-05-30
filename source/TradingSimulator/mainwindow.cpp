#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeMode(int mode)
{
    ui->Modes->setCurrentIndex(mode);

    switch (mode) {
    case cdStk:
        view = new EvolutionViewer(*cours, ui->csChart);
        ui->csLabel->addItems(view->getLabels());
        break;

    }
}

void MainWindow::on_csLabel_currentRowChanged(int currentRow)
{
    //qDebug()<<currentRow;
    view->changeChart(currentRow);
}

