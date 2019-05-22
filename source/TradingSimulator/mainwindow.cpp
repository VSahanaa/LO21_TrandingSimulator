#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->currency1->addItems({"USD", "BTC"});
    ui->currency2->addItems({"USD", "BTC"});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Show_clicked()
{
    QString name, fPath = ui->filePath->text();
    name.append(ui->currency1->currentText());
    name.append("_");
    name.append(ui->currency2->currentText());
    evolution = new EvolutionCours(fPath);
    view = new EvolutionViewer(*evolution);
    view->setname(name);
    view->show();
}

void MainWindow::on_Funct1_clicked()
{
    ui->stackedPages->setCurrentIndex(Display);
}

void MainWindow::on_Funct2_clicked()
{

}

void MainWindow::on_Funct3_clicked()
{

}

void MainWindow::on_Funct4_clicked()
{

}

void MainWindow::on_enter_clicked()
{
    ui->stackedPages->setCurrentIndex(MainManu);
}

void MainWindow::on_searchFile_clicked()
{
    QFileDialog fdlg;
    ui->filePath->setText(fdlg.getOpenFileName(this, tr("Choose csv file"),
                                               "./",
                                               "Document files (*.csv)"));
}
