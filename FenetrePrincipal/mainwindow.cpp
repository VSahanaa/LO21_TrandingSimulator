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

void MainWindow::on_pushButtonRetourMenu_clicked()
{
    /*QMessageBox::standardButton reply = QMessageBox::question(this,"ATTENTION","Vous allez revenir au menu, la sauvegarde n'est pas effectuée automatiquement. Voulez-vous continuer ?",QMessageBox::Yes|QMessageBox::No);
    if (reply==QMessageBox::Yes){
        //revenir au menu sans sauvegarder
    }  //else{//ne rien faire}
    */

}

void MainWindow::on_pushButton_Sauv_clicked()
{
    //ouvrir la fenetre dialog de sauvegarde sous ou sauvegarder directement
}

void MainWindow::on_pushButton_Param_clicked()
{
    //ouvrir la fenetre dialog parametre où il affiche la résolution... ?
}

void MainWindow::on_pushButton_curseur_clicked()
{
    //ouvrir le curseur sur le graph ?
}

void MainWindow::on_pushButton_indicateur_clicked()
{
    //ouvrir le dialog indicateur
    dialog_ind=new Indicateur(this);
    dialog_ind->show();
}

void MainWindow::on_pushButton_tabCours_clicked()
{
    //ouverture du dialog tabCours
}

void MainWindow::on_pushButton_nouvelletransaction_clicked()
{
    //ouverture du dialog pour faire transaction
}

void MainWindow::on_pushButton_annuler_clicked()
{
    //transaction -1
}

void MainWindow::on_pushButton_tabTransaction_clicked()
{
    //dialog pour ouvrir le tableau des transactions
}

void MainWindow::on_pushButton_avancer_clicked()
{
    //QMessageBox::critical(this,"Erreur","Transaction impossible dans ce mode ou erreur interne.");
    //pour la simulation
}

void MainWindow::on_pushButton_reculer_clicked()
{
    //pre transaction idem
}

void MainWindow::on_pushButton_defiler_clicked()
{
    //simulation auto
}

void MainWindow::on_pushButton_pause_clicked()
{
    //simulation auto
}

void MainWindow::on_pushButton_Lire_2_clicked()
{
    //ouverture en lecture du fichier dans une autre fenetre
}

void MainWindow::on_pushButton_modifier_2_clicked()
{
    //ouverture en écriture du fichier dans une autre fenetre...
}

void MainWindow::on_pushButton_3_clicked()
{
    //mise a jour des graphs ?
}
