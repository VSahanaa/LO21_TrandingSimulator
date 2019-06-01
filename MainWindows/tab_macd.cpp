#include "tab_macd.h"
#include "ui_tab_macd.h"

tab_MACD::tab_MACD(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tab_MACD)
{
    ui->setupUi(this);
}

tab_MACD::~tab_MACD()
{
    delete ui;
}
