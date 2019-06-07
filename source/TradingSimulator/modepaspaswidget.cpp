#include "modepaspaswidget.h"
#include "ui_modepaspaswidget.h"

ModePasPaswidget::ModePasPaswidget(ModePas_Pas* modePas_Pas, QWidget *parent) : QWidget(parent), ui(new Ui::ModePasPaswidget), modePas_Pas(modePas_Pas) {
    ui->setupUi(this);
    transactionManager = modePas_Pas->getTransactionManager();
    qDebug() << "get here 1";
    ui->paireLabel->setText(modePas_Pas->getEvolutionCours()->getPaireDevises()->toString());
    ui->label_montantBase->setText(QString::number(transactionManager->getMontantBase()));
    ui->label_montantContrepartie->setText(QString::number(transactionManager->getMontantContrepartie()));
    ui->label_broker->setText(QString::number(transactionManager->getPourcentage()));

    ui->dateEdit->setDate(modePas_Pas->getCurrentCours()->getDate());
    ui->dateEdit->setMaximumDate(modePas_Pas->getCurrentCours()->getDate());
    ui->dateEdit->setMinimumDate(modePas_Pas->getCurrentCours()->getDate());

    ui->openPrice->setText(QString::number(modePas_Pas->getCurrentCours()->getOpen()));
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
    QObject::connect(modePas_Pas, SIGNAL(coursChanged()), this, SLOT(updateCurrentCours()));
    qDebug() << "get here 2";
}

ModePasPaswidget::~ModePasPaswidget()
{
    delete ui;
}

void ModePasPaswidget::updateData() {
    ui->label_montantBase->setText(QString::number(transactionManager->getMontantBase()));
    ui->label_montantContrepartie->setText(QString::number(transactionManager->getMontantContrepartie()));
    ui->label_broker->setText(QString::number(transactionManager->getPourcentage()));
    ui->montant_edit->setMaximum(transactionManager->getMontantContrepartie());
}

void ModePasPaswidget::updateCurrentCours() {
    CoursOHLCV* currentCours = modePas_Pas->getCurrentCours();
    ui->dateEdit->setMaximumDate(currentCours->getDate());
    ui->dateEdit->setDate(currentCours->getDate());
    ui->openPrice->setText(QString::number(currentCours->getOpen()));
    updateData();
}

void ModePasPaswidget::on_goBack_clicked() {
    modePas_Pas->goBack(ui->dateEdit->date());
    updateData();
}

void ModePasPaswidget::on_comboBox_timer_currentIndexChanged(const QString &arg1) {
    modePas_Pas->setTimer(ui->comboBox_timer->currentData().toInt());
}

void ModePasPaswidget::on_pushButton_achat_clicked() {
    double montant = ui->montant_edit->value();
    if (montant > 0) {
        modePas_Pas->achat(montant);
        updateData();
    }
}

void ModePasPaswidget::on_pushButton_vente_clicked() {
    double montant = ui->montant_edit->value();
    if (montant > 0) {
        modePas_Pas->vente(montant);
        updateData();
    }
}

void ModePasPaswidget::on_pushButton_annulerTransaction_clicked() {
    modePas_Pas->annule();
    updateData();
}
