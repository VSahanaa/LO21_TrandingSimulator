#include "tab_ema.h"
#include "ui_tab_ema.h"

tab_EMA::tab_EMA(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tab_EMA)
{
    ui->setupUi(this);
}

tab_EMA::~tab_EMA()
{
    delete ui;
}
