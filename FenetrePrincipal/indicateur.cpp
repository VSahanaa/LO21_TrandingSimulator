#include "indicateur.h"
#include "ui_indicateur.h"

Indicateur::Indicateur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Indicateur)
{
    ui->setupUi(this);
}

Indicateur::~Indicateur()
{
    delete ui;
}

void Indicateur::on_listWidget_indicateurs_itemActivated(QListWidgetItem *item)
{
    //indicateur select
}

void Indicateur::on_buttonBox_OK_accepted()
{
    //ouverture de la fenetre correspondante ?
}

void Indicateur::on_buttonBox_OK_rejected()
{
    //annuler et fermer la fenetre dialog indicateur
    this->~Indicateur();
}
