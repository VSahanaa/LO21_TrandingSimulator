#include "tab_rsi.h"
#include "ui_tab_rsi.h"

tab_RSI::tab_RSI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tab_RSI)
{
    ui->setupUi(this);
}

tab_RSI::~tab_RSI()
{
    delete ui;
}
