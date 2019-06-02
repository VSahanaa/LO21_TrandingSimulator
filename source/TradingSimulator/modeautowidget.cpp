#include "modeautowidget.h"
#include "ui_modeautowidget.h"

ModeAutowidget::ModeAutowidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeAutowidget)
{
    ui->setupUi(this);
}

ModeAutowidget::~ModeAutowidget()
{
    delete ui;
}
