#include "modepaspaswidget.h"
#include "ui_modepaspaswidget.h"

ModePasPaswidget::ModePasPaswidget(ModePas_Pas* modePas_Pas, QWidget *parent) : QWidget(parent), ui(new Ui::ModePasPaswidget), modePas_Pas(modePas_Pas) {
    ui->setupUi(this);
    transactionManager = modePas_Pas->getTransactionManager();

    ui->label_montantBase->setNum(transactionManager->getMontantBase());
    ui->label_montantContrepartie->setNum(transactionManager->getMontantContrepartie());
    ui->label_broker->setNum(transactionManager->getPourcentage());
    ui->dateEdit->setDate(modePas_Pas->getCurrentCours()->getDate());
    ui->dateEdit->setMaximumDate(modePas_Pas->getCurrentCours()->getDate());
    ui->dateEdit->setMinimumDate(modePas_Pas->getCurrentCours()->getDate());
    ui->openPrice->setNum(modePas_Pas->getCurrentCours()->getOpen());
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
    ui->montant_edit->setMinimum(0);
    ui->montant_edit->setMaximum(transactionManager->getMontantContrepartie());
    //connect signals
    QObject::connect(ui->pushButton_achat, SIGNAL(clicked()), modePas_Pas, SLOT(buy_slot(ui->montant_edit->value())));
    QObject::connect(ui->pushButton_vente, SIGNAL(clicked()), modePas_Pas, SLOT((sell_slot(ui->montant_edit->value()))));
    QObject::connect(ui->pushButton_annulerTransaction, SIGNAL(clicked()), modePas_Pas, SLOT(annule()));
    QObject::connect(modePas_Pas, SIGNAL(transactionAdded()), this, SLOT(updateData()));
    QObject::connect(modePas_Pas, SIGNAL(transactionAnnule()), this, SLOT(updateData()));
    QObject::connect(modePas_Pas, SIGNAL(coursPickedChanged(CoursOHLCV*)), this, SLOT(updateCurrentCours(CoursOHLCV*)));
}

ModePasPaswidget::~ModePasPaswidget()
{
    delete ui;
}

void ModePasPaswidget::updateData() {
    ui->label_montantBase->setNum(transactionManager->getMontantBase());
    ui->label_montantContrepartie->setNum(transactionManager->getMontantContrepartie());
    ui->label_broker->setNum(transactionManager->getPourcentage());
    ui->montant_edit->setMaximum(transactionManager->getMontantContrepartie());
}

void ModePasPaswidget::updateCurrentCours(CoursOHLCV* cours) {
    ui->dateEdit->setDate(cours->getDate());
    ui->dateEdit->setMaximumDate(cours->getDate());
    ui->openPrice->setNum(cours->getOpen());
}

void ModePasPaswidget::on_goBack_clicked() {
    modePas_Pas->setCours(ui->dateEdit->date());
}

void ModePasPaswidget::on_comboBox_timer_currentIndexChanged(const QString &arg1) {
    modePas_Pas->setTimer(ui->comboBox_timer->currentData().toInt());
}
