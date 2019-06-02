#include "modemanuelwidget.h"
#include "ui_modemanuelwidget.h"

modeManuelWidget::modeManuelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modeManuelWidget)
{
    ui->setupUi(this);
}

modeManuelWidget::~modeManuelWidget()
{
    delete ui;
}
