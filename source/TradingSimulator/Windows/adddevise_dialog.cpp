#include "adddevise_dialog.h"
#include "ui_adddevise_dialog.h"

AddDevise_Dialog::AddDevise_Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddDevise_Dialog) {
    ui->setupUi(this);
    this->setWindowTitle("Add Devise");
}

AddDevise_Dialog::~AddDevise_Dialog() {
    delete ui;
}

void AddDevise_Dialog::on_AddDevise_Dialog_accepted()
{
    //qDebug() << ui->codeEdit->text() << " "<< ui->monnaieEdit->text() << " "<< ui->zoneEdit->currentText();
    if (ui->codeEdit->text().isEmpty() || ui->codeEdit->text().length() > 3 || ui->monnaieEdit->text().isEmpty() || ui->zoneEdit->currentText().isEmpty()) {
        QMessageBox::warning(this, "Warning", "Add Devise Dialog: champs invalid");
    }
    else {
        DevisesManager& deviseManager = DevisesManager::getManager();
        //add new devise
        newDevise = deviseManager.creationDevise(ui->codeEdit->text().toUpper(), ui->monnaieEdit->text(), ui->zoneEdit->currentText());
        qDebug() << newDevise->getCode() <<" "<< newDevise->getMonnaie()<<" "<< newDevise->getZoneGeographique();
    }
}
