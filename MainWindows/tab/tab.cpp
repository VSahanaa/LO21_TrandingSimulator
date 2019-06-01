#include "tab.h"
#include "ui_tab.h"

TAB::TAB(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TAB)
{
    ui->setupUi(this);
}

TAB::~TAB()
{
    delete ui;
}
