#include "modemanuelwidget.h"
#include "ui_modemanuelwidget.h"

modeManuelWidget::modeManuelWidget(ModeManuel* modeManuel, QWidget *parent) : QWidget(parent), ui(new Ui::modeManuelWidget), modeManuel(modeManuel) {
    ui->setupUi(this);
    transactionManager = modeManuel->getTransactionManager();
    ui->label_montantBase->setNum(transactionManager->getMontantBase());
    ui->label_montantContrepartie->setNum(transactionManager->getMontantContrepartie());
    ui->label_broker->setNum(transactionManager->getPourcentage());
    ui->label_date->setText(modeManuel->getCurrentCours()->getDate().toString("dd.MM.yyyy"));
    ui->openPrice->setNum(modeManuel->getCurrentCours()->getOpen());
    ui->montant_Edit->setMinimum(0);
    ui->montant_Edit->setMaximum(transactionManager->getMontantContrepartie());
    //connect signals
    QObject::connect(ui->pushButton_achat, SIGNAL(clicked()), modeManuel, SLOT(buy_slot(i->montant_Edit->value())));
    QObject::connect(ui->pushButton_vente, SIGNAL(clicked()), modeManuel, SLOT((sell_slot(i->montant_Edit->value()))));
    QObject::connect(ui->pushButton_annulerTransaction, SIGNAL(clicked()), modeManuel, SLOT(annule()));
    QObject::connect(modeManuel, SIGNAL(transactionAdded()), this, SLOT(updateData()));
    QObject::connect(modeManuel, SIGNAL(transactionAnnule()), this, SLOT(updateData()));
    QObject::connect(modeManuel, SIGNAL(coursPickedChanged(CoursOHLCV*)), this, SLOT(updateCoursPicked(CoursOHLCV*)));
}

modeManuelWidget::~modeManuelWidget() {
    delete ui;
}

void modeManuelWidget::updateData() {
    ui->label_montantBase->setNum(transactionManager->getMontantBase());
    ui->label_montantContrepartie->setNum(transactionManager->getMontantContrepartie());
    ui->label_broker->setNum(transactionManager->getPourcentage());
    ui->montant_Edit->setMaximum(transactionManager->getMontantContrepartie());
}

void modeManuelWidget::updateCoursPicked(CoursOHLCV* cours) {
    ui->label_date->setText(cours->getDate().toString("dd.MM.yy"));
    ui->openPrice->setNum(cours->getOpen());
}
