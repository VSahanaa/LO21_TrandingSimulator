#include "modemanuelwidget.h"
#include "ui_modemanuelwidget.h"

modeManuelWidget::modeManuelWidget(ModeManuel* modeManuel, QWidget *parent) : QWidget(parent), ui(new Ui::modeManuelWidget), modeManuel(modeManuel) {
    ui->setupUi(this);
    transactionManager = modeManuel->getTransactionManager();
    ui->pairelabel->setText(modeManuel->getEvolutionCours()->getPaireDevises()->toString());

    ui->label_montantBase->setText(QString::number(transactionManager->getMontantBase()));
    ui->label_montantContrepartie->setText(QString::number(transactionManager->getMontantContrepartie()));
    ui->label_broker->setText(QString::number(transactionManager->getPourcentage()));

    ui->label_date->setText(modeManuel->getCurrentCours()->getDate().toString("dd.MM.yyyy"));
    ui->openPrice->setText(QString::number(modeManuel->getCurrentCours()->getOpen()));
    ui->montant_Edit->setMinimum(0);
    ui->montant_Edit->setMaximum(transactionManager->getMontantContrepartie());  
}

modeManuelWidget::~modeManuelWidget() {
    delete ui;
}

void modeManuelWidget::updateData() {
    ui->label_montantBase->setText(QString::number(transactionManager->getMontantBase()));
    ui->label_montantContrepartie->setText(QString::number(transactionManager->getMontantContrepartie()));
    ui->label_broker->setText(QString::number(transactionManager->getPourcentage()));
    ui->montant_Edit->setMaximum(transactionManager->getMontantContrepartie());
}

void modeManuelWidget::setCoursPicked(CoursOHLCV* cours) {
    coursPicked = cours;
    if(cours->getDate() < modeManuel->getCurrentCours()->getDate()) throw TradingException(" ne peut pas choisir un jour dans le passé");
    ui->label_date->setText(cours->getDate().toString("dd.MM.yy"));
    ui->openPrice->setText(QString::number(cours->getOpen()));
}

void modeManuelWidget::on_pushButton_achat_clicked() {
    double montant = ui->montant_Edit->value();
    qDebug() << montant;
    if (montant > 0) {
        modeManuel->achat(coursPicked, montant);
        updateData();
    }
}

void modeManuelWidget::on_pushButton_vente_clicked() {
    double montant = ui->montant_Edit->value();
    qDebug() << montant;
    if (montant > 0) {
        modeManuel->vente(coursPicked, montant);
        updateData();
    }
}

void modeManuelWidget::on_pushButton_annulerTransaction_clicked() {
    modeManuel->annule();
    updateData();
}
