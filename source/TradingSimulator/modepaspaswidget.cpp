#include "modepaspaswidget.h"
#include "ui_modepaspaswidget.h"

ModePasPaswidget::ModePasPaswidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModePasPaswidget)
{
    ui->setupUi(this);
}

ModePasPaswidget::~ModePasPaswidget()
{
    delete ui;
}
