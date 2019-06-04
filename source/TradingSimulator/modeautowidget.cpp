#include "modeautowidget.h"
#include "ui_modeautowidget.h"

ModeAutowidget::ModeAutowidget(ModeAutomatique* modeAutomatique, QWidget *parent) : QWidget(parent), ui(new Ui::ModeAutowidget), modeAutomatique(modeAutomatique) {
    ui->setupUi(this);
    transactionManager = modeAutomatique->getTransactionManager();

    ui->label_montantBase->setNum(transactionManager->getMontantBase());
    ui->label_montantContrepartie->setNum(transactionManager->getMontantContrepartie());
    ui->label_broker->setNum(transactionManager->getPourcentage());
    ui->label_strategie->setText(modeAutomatique->getStrategieName());
    ui->dateEdit->setDate(modeAutomatique->getCurrentCours()->getDate());
    ui->dateEdit->setMaximumDate(modeAutomatique->getCurrentCours()->getDate());
    ui->dateEdit->setMinimumDate(modeAutomatique->getCurrentCours()->getDate());
    ui->openPrice->setNum(modeAutomatique->getCurrentCours()->getOpen());
    ui->comboBox_timer->addItem("30 seconde", 30000);
    ui->comboBox_timer->addItem("1 min", 60000);
    ui->comboBox_timer->addItem("5 mins", 300000);
    ui->comboBox_timer->addItem("10 mins", 600000);
    ui->comboBox_timer->addItem("30 mins", 1800000);
    ui->comboBox_timer->addItem("1 heure", 3600000);
    ui->comboBox_timer->addItem("3 heures", 10800000);
    ui->comboBox_timer->addItem("5 heures", 18000000);
    ui->comboBox_timer->addItem("12 heures", 43200000);
    ui->comboBox_timer->addItem("1 jour", 86400000);
    ui->comboBox_timer->setCurrentIndex(0);
    QObject::connect(modeAutomatique, SIGNAL(dateChanged()), this, SLOT(updateData()));
}

ModeAutowidget::~ModeAutowidget() {
    delete ui;
}

void ModeAutowidget::updateData() {
    ui->label_montantBase->setNum(transactionManager->getMontantBase());
    ui->label_montantContrepartie->setNum(transactionManager->getMontantContrepartie());
    ui->label_broker->setNum(transactionManager->getPourcentage());
    ui->dateEdit->setDate(modeAutomatique->getCurrentCours()->getDate());
    ui->dateEdit->setMaximumDate(modeAutomatique->getCurrentCours()->getDate());
    ui->dateEdit->setMinimumDate(modeAutomatique->getCurrentCours()->getDate());
    ui->openPrice->setNum(modeAutomatique->getCurrentCours()->getOpen());
}


void ModeAutowidget::on_comboBox_timer_currentIndexChanged(int index)
{
    modeAutomatique->setTimer(ui->comboBox_timer->currentData().toInt());
}
