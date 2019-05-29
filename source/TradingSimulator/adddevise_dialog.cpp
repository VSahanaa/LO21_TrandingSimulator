#include "adddevise_dialog.h"
#include "ui_adddevise_dialog.h"

AddDevise_Dialog::AddDevise_Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddDevise_Dialog) {
    ui->setupUi(this);
}

AddDevise_Dialog::~AddDevise_Dialog() {
    delete ui;
}

void AddDevise_Dialog::on_AddDevise_Dialog_accepted()
{
    //qDebug() << ui->codeEdit->text() << " "<< ui->monnaieEdit->text() << " "<< ui->zoneEdit->currentText();
    if (ui->codeEdit->text().isEmpty() || ui->monnaieEdit->text().isEmpty() || ui->zoneEdit->currentText().isEmpty()) throw TradingException("Add Devise Dialog: champs invalid");
    DevisesManager& deviseManager = DevisesManager::getManager();
    //add new devise
    newDevise = &deviseManager.creationDevise(ui->codeEdit->text(), ui->monnaieEdit->text(), ui->zoneEdit->currentText());
    qDebug() << newDevise->getCode() <<" "<< newDevise->getMonnaie()<<" "<< newDevise->getZoneGeographique();
}
