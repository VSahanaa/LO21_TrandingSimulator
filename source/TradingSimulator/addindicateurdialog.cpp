#include "addindicateurdialog.h"
#include "ui_addindicateurdialog.h"

AddIndicateurDialog::AddIndicateurDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddIndicateurDialog)
{
    ui->setupUi(this);
}

AddIndicateurDialog::~AddIndicateurDialog()
{
    delete ui;
}
