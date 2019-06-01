#include "mainwindow_modeauto.h"
#include "ui_mainwindow_modeauto.h"
//#include <QMessageBox>

MainWindow_modeauto::MainWindow_modeauto(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_modeauto)
{
    ui->setupUi(this);
    //ui->label_montantB=
    //ui->label_montantC=
    //ui->label_date = Date;
    //ui->label_strategie =
}

MainWindow_modeauto::~MainWindow_modeauto()
{
    delete ui;
}

void MainWindow_modeauto::on_pushButton_retourMenu_clicked()
{
    /*QMessageBox::standardButton reply = QMessageBox::question(this,"ATTENTION","Vous allez revenir au menu, la sauvegarde n'est pas effectuée automatiquement. Voulez-vous continuer ?",QMessageBox::Yes|QMessageBox::No);
    if (reply==QMessageBox::Yes){
        //revenir au menu sans sauvegarder
        //fermer MainWindow_modepas et ouvrir la fenetre de début
    }  //else{//ne rien faire}
    */
}

void MainWindow_modeauto::on_pushButton_sauvegarder_clicked()
{
    //dialog pour sauver
}

void MainWindow_modeauto::on_pushButton_parametre_clicked()
{
    //dialog parametre
}

void MainWindow_modeauto::on_pushButton_aide_clicked()
{
    //dialog help
}

void MainWindow_modeauto::on_pushButton_tabCoursOHLCV_clicked()
{
   //ui->tabWidget_autres->addTab(new tab_coursohlcv(),"coursOHLCV");
}

void MainWindow_modeauto::on_pushButton_tabTransaction_clicked()
{
    //ui->tabWidget_autres->addTab(new tab_transaction(),"transactions");
}

void MainWindow_modeauto::on_pushButton_prendreNote_clicked()
{
    //editeur de texte dialog ?
}

void MainWindow_modeauto::on_checkBox_MACD_stateChanged(int arg1)
{
    /*if(this->isChecked()){
        ui->tabWidget_autres->addTab(new tab_MACD(),"MACD");
        //tableau
    else {
        //ui->tabwidget_autres->removeTab(//MACD);
    }*/
}

void MainWindow_modeauto::on_checkBox_RSI_stateChanged(int arg1)
{
    //afficher ou cacher la fenetre sur frame_autres
    /*if(this->isChecked()){
        ui->tabWidget_autres->addTab(new tab_RSI(),"RSI");
        //tableau
    else {
        //ui->tabwidget_autres->removeTab(//RSI);
    }*/
}

void MainWindow_modeauto::on_checkBox_EMA_stateChanged(int arg1)
{
    /*if(this->isChecked()){
        ui->tabWidget_autres->addTab(new tab_EMA(),"EMA");
        //tableau
    else {
        //ui->tabwidget_autres->removeTab(//EMA);
    }*/
}

void MainWindow_modeauto::on_tabWidget_autres_tabCloseRequested(int index)
{
    //ui->tabwidget_autres->removeTab(index);
}
