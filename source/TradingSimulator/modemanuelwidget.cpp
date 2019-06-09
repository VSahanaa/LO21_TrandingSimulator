#include "modemanuelwidget.h"
#include "ui_modemanuelwidget.h"

modeManuelWidget::modeManuelWidget(ModeManuel* modeManuel, QWidget *parent) : QWidget(parent), ui(new Ui::modeManuelWidget), modeManuel(modeManuel) {
    ui->setupUi(this);
    transactionManager = modeManuel->getTransactionManager();
    ui->pairelabel->setText(modeManuel->getEvolutionCours()->getPaireDevises()->toString());
    ui->base->setText(modeManuel->getEvolutionCours()->getPaireDevises()->getBase().getCode());
    ui->contrepartie->setText(modeManuel->getEvolutionCours()->getPaireDevises()->getContrepartie().getCode());
    ui->label_montantBase->setText(QString::number(transactionManager->getMontantBase()));
    ui->label_montantContrepartie->setText(QString::number(transactionManager->getMontantContrepartie()));
    ui->label_broker->setText(QString::number(transactionManager->getPourcentage()));

    ui->label_date->setText(modeManuel->getCurrentCours()->getDate().toString("dd.MM.yyyy"));
    ui->openPrice->setText(QString::number(modeManuel->getCurrentCours()->getOpen()));
    ui->montant_Edit->setMinimum(0);
    ui->montant_Edit->setMaximum(transactionManager->getMontantContrepartie()*1000);
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
    if(cours->getDate() < modeManuel->getCurrentCours()->getDate()) {
        QMessageBox::information(this, "Info", "Ne peut pas choisir un jour dans le passé");
    }
    else {
        ui->label_date->setText(cours->getDate().toString("dd.MM.yy"));
        ui->openPrice->setText(QString::number(cours->getOpen()));
    }
}

void modeManuelWidget::on_pushButton_achat_clicked() {
    double montant = ui->montant_Edit->value();
    if (montant > 0) {
        try {
            modeManuel->achat(coursPicked, montant);
            updateData();
            emit transactionChanged();
        }
        catch(TradingException exception) {
            QMessageBox::warning(this, "Warning", "Montant de contre partie n'est pas assez.");
        }
    }
}

void modeManuelWidget::on_pushButton_vente_clicked() {
    double montant = ui->montant_Edit->value();
    qDebug() << montant;
    if (montant > 0) {
        try {
            modeManuel->vente(coursPicked, montant);
            updateData();
            emit transactionChanged();
        }
        catch (TradingException exception) {
            QMessageBox::warning(this, "Warning", "Montant de base n'est pas assez.");
        }

    }
}

void modeManuelWidget::on_pushButton_annulerTransaction_clicked() {
    modeManuel->annule();
    updateData();
    emit transactionChanged();
}
