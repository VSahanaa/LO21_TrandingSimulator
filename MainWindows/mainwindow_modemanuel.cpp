#include "mainwindow_modemanuel.h"
#include "ui_mainwindow_modemanuel.h"

MainWindow_modemanuel::MainWindow_modemanuel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_modemanuel)
{
    ui->setupUi(this);
    //ui->label_montantB=
    //ui->label_montantC=
    //ui->label_date = Date;
    //ui->label_broker =
}

MainWindow_modemanuel::~MainWindow_modemanuel()
{
    delete ui;
}

void MainWindow_modemanuel::on_pushButton_retourMenu_clicked()
{
    /*QMessageBox::standardButton reply = QMessageBox::question(this,"ATTENTION","Vous allez revenir au menu, la sauvegarde n'est pas effectuée automatiquement. Voulez-vous continuer ?",QMessageBox::Yes|QMessageBox::No);
    if (reply==QMessageBox::Yes){
        //revenir au menu sans sauvegarder
        //fermer MainWindow_modepas et ouvrir la fenetre de début
    }  //else{//ne rien faire}
    */
}

void MainWindow_modemanuel::on_pushButton_sauvegarder_clicked()
{
    //dialog sauver
}

void MainWindow_modemanuel::on_pushButton_parametre_clicked()
{
    //dialog parametre
}

void MainWindow_modemanuel::on_pushButton_aide_clicked()
{
    //dialog aide
}

void MainWindow_modemanuel::on_pushButton_achat_clicked()
{
    //achat
}

void MainWindow_modemanuel::on_pushButton_vente_clicked()
{
    //vente
}

void MainWindow_modemanuel::on_pushButton_annulerTransaction_clicked()
{
    //annuler transaction
}

void MainWindow_modemanuel::on_pushButton_tabCoursOHLCV_clicked()
{
    //fenetre 2 tableau
}

void MainWindow_modemanuel::on_pushButton_tabTransaction_clicked()
{
    //fenetre 2 tableau
}

void MainWindow_modemanuel::on_pushButton_prendreNote_clicked()
{
    //prise de note
}

void MainWindow_modemanuel::on_checkBox_RSI_stateChanged(int arg1)
{
    //if (this.isChecked()) //affiche else //cache
}

void MainWindow_modemanuel::on_checkBox_EMA_stateChanged(int arg1)
{
    //idem
}

void MainWindow_modemanuel::on_checkBox_MACD_stateChanged(int arg1)
{
    //idem
}
