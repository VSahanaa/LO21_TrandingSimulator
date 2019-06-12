#include "modeautowidget.h"
#include "ui_modeautowidget.h"

ModeAutowidget::ModeAutowidget(ModeAutomatique* modeAutomatique, QWidget *parent) : QWidget(parent), ui(new Ui::ModeAutowidget), modeAutomatique(modeAutomatique) {
    ui->setupUi(this);
    transactionManager = modeAutomatique->getTransactionManager();
    ui->pairelabel->setText(modeAutomatique->getEvolutionCours()->getPaireDevises()->toString());
    ui->base->setText(modeAutomatique->getEvolutionCours()->getPaireDevises()->getBase().getCode());
    ui->contrepartie->setText(modeAutomatique->getEvolutionCours()->getPaireDevises()->getContrepartie().getCode());

    ui->label_montantBase->setText(QString::number(transactionManager->getMontantBase()));
    ui->label_montantContrepartie->setText(QString::number(transactionManager->getMontantContrepartie()));
    ui->label_broker->setText(QString::number(transactionManager->getPourcentage()));
    ui->label_strategie->setText(modeAutomatique->getStrategieName());
    ui->dateEdit->setDate(modeAutomatique->getCurrentCours()->getDate());
    ui->dateEdit->setMaximumDate(modeAutomatique->getCurrentCours()->getDate());
    ui->dateEdit->setMinimumDate(modeAutomatique->getCurrentCours()->getDate());
    ui->openPrice->setText(QString::number(modeAutomatique->getCurrentCours()->getOpen()));
    ui->comboBox_timer->addItem("30 secondes", 30000);
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
    QObject::connect(modeAutomatique, SIGNAL(coursChanged()), this, SLOT(updateData()));
}

ModeAutowidget::~ModeAutowidget() {
    delete ui;
}

void ModeAutowidget::updateData() {
    ui->label_montantBase->setText(QString::number(transactionManager->getMontantBase()));
    if((ui->label_montantContrepartie->text()).toDouble() != transactionManager->getMontantContrepartie()) emit transactionChanged();
    ui->label_montantContrepartie->setText(QString::number(transactionManager->getMontantContrepartie()));
    ui->label_broker->setText(QString::number(transactionManager->getPourcentage()));
    ui->dateEdit->setDate(modeAutomatique->getCurrentCours()->getDate());
    ui->dateEdit->setMaximumDate(modeAutomatique->getCurrentCours()->getDate());
    ui->dateEdit->setMinimumDate(modeAutomatique->getCurrentCours()->getDate());
    ui->openPrice->setText(QString::number(modeAutomatique->getCurrentCours()->getOpen()));
}


void ModeAutowidget::on_comboBox_timer_currentIndexChanged(int index){
    modeAutomatique->setTimer(ui->comboBox_timer->currentData().toInt());
}
