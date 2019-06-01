#include "mainwindow_modepas.h"
#include "ui_mainwindow_modepas.h"
//#include <QMessageBox>
#include "tab_coursohlcv.h"
#include "tab_transaction.h"
#include "tab_ema.h"
#include "tab_macd.h"
#include "tab_rsi.h"

MainWindow_modepas::MainWindow_modepas(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_modepas)
{
    ui->setupUi(this);
    //ui->label_montantB=
    //ui->label_montantC=
    //ui->label_date = Date;
    //ui->label_openPrice

    /*
    tabWidget_autres = new QTabWidget;
    tabWidget_autres->addTab(new tab_RSI(),"RSI");
    */
}

MainWindow_modepas::~MainWindow_modepas()
{
    delete ui;
}

void MainWindow_modepas::on_pushButton_retourMenu_clicked()
{
    /*QMessageBox::standardButton reply = QMessageBox::question(this,"ATTENTION","Vous allez revenir au menu, la sauvegarde n'est pas effectuée automatiquement. Voulez-vous continuer ?",QMessageBox::Yes|QMessageBox::No);
    if (reply==QMessageBox::Yes){
        //revenir au menu sans sauvegarder
        //fermer MainWindow_modepas et ouvrir la fenetre de début
    }  //else{//ne rien faire}
    */
}

void MainWindow_modepas::on_pushButton_sauvegarder_clicked()
{
    //ouvrir le dialog pour enregistrer le fichier
}

void MainWindow_modepas::on_pushButton_parametre_clicked()
{
    //dialog parametre
}

void MainWindow_modepas::on_pushButton_aide_clicked()
{
    //dialog aide... site internet? documentation ?
}

void MainWindow_modepas::on_pushButton_achat_clicked()
{
    //recuperer Qedit
    // long int montant = ui->lineEdit_montant->text()-1;
    //lancer la transaction en achat
}

void MainWindow_modepas::on_pushButton_vente_clicked()
{
    // long int montant = ui->lineEdit_montant->text()-1;
    //idem
}

void MainWindow_modepas::on_pushButton_annulerTransaction_clicked()
{
    //message de confirmation ?
    //supp la dernier transaction.
}

void MainWindow_modepas::on_pushButton_tabCoursOHLCV_clicked()
{
    //ui->tabWidget_autres->addTab(new tab_coursohlcv(),"CoursOHLCV");
}

void MainWindow_modepas::on_pushButton_tabTransaction_clicked()
{
    //ui->tabWidget_autres->addTab(new tab_transaction(),"transactions");
}

void MainWindow_modepas::on_pushButton_prendreNote_clicked()
{
    //ouvrir l'editeur de txt et le fichier
}

void MainWindow_modepas::on_checkBox_RSI_stateChanged(int arg1)
{
    //afficher ou cacher la fenetre sur frame_autres
    /*if(this->isChecked()){
        ui->tabWidget_autres->addTab(new tab_RSI(),"RSI");
        //tableau
    else {
        //ui->tabwidget_autres->removeTab(//RSI);
    }*/
}

void MainWindow_modepas::on_checkBox_EMA_stateChanged(int arg1)
{
    /*if(this->isChecked()){
        ui->tabWidget_autres->addTab(new tab_EMA(),"EMA");
        //tableau
    else {
        //ui->tabwidget_autres->removeTab(//EMA);
    }*/
}

void MainWindow_modepas::on_checkBox_MACD_stateChanged(int arg1)
{
    /*if(this->isChecked()){
        ui->tabWidget_autres->addTab(new tab_MACD(),"MACD");
        //tableau
    else {
        //ui->tabwidget_autres->removeTab(//MACD);
    }*/
}

void MainWindow_modepas::on_tabWidget_autres_tabCloseRequested(int index)
{
    //ui->tabwidget_autres->removeTab(index);
}
