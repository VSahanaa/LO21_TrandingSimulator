#include "tradinginterface.h"
#include "ui_tradinginterface.h"

TradingInterface::TradingInterface(QWidget *parent) : QWidget(parent), ui(new Ui::TradingInterface) {
    ui->setupUi(this);
}

TradingInterface::~TradingInterface() {
    delete ui;
}
