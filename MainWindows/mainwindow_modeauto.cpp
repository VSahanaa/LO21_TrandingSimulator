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
    //ouverture fenetre2
}

void MainWindow_modeauto::on_pushButton_tabTransaction_clicked()
{
    //ouverture fenetre2
}

void MainWindow_modeauto::on_pushButton_prendreNote_clicked()
{
    //editeur de texte dialog ?
}

void MainWindow_modeauto::on_checkBox_MACD_stateChanged(int arg1)
{
    /* if (this.isChecked()){
     * //afficher
     * }else //cacher
     * */
}

void MainWindow_modeauto::on_checkBox_RSI_stateChanged(int arg1)
{
    //idem
}

void MainWindow_modeauto::on_checkBox_EMA_stateChanged(int arg1)
{
    //idem
}
