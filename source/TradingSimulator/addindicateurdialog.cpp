#include "addindicateurdialog.h"
#include "ui_addindicateurdialog.h"

AddIndicateurDialog::AddIndicateurDialog(QString indicateur, EvolutionCours* evolutionCours, QWidget *parent) :
    QDialog(parent), ui(new Ui::AddIndicateurDialog), indicateur(indicateur), evolutionCours(evolutionCours) {
    ui->setupUi(this);
    if(indicateur == "EMA") {
        ui->stackedWidget->setCurrentIndex(0);
        ui->pickEmaPeriod->setMaximum(100);
        ui->pickEmaPeriod->setMinimum(0);
        ui->pickEmaPeriod->setValue(10);
        ui->pickEmaPeriod->setSuffix(" jours");
    }
    else if(indicateur == "RSI") {
        ui->stackedWidget->setCurrentIndex(1);
        ui->pickLookbackPeriod->setMaximum(100);
        ui->pickLookbackPeriod->setMinimum(0);
        ui->pickLookbackPeriod->setValue(10);
        ui->pickLookbackPeriod->setSuffix(" jours");

        ui->pickOverbought->setMaximum(100);
        ui->pickOverbought->setMinimum(0);
        ui->pickOverbought->setValue(80);
        ui->pickOverbought->setSuffix(" %");

        ui->pickOversold->setMaximum(100);
        ui->pickOversold->setMinimum(0);
        ui->pickOversold->setValue(20);
        ui->pickOversold->setSuffix(" %");
    }
    else if (indicateur == "MACD") {
        ui->stackedWidget->setCurrentIndex(2);
        ui->pickLongPeriod->setMaximum(100);
        ui->pickLongPeriod->setMinimum(0);
        ui->pickLongPeriod->setValue(26);
        ui->pickLongPeriod->setSuffix(" jours");

        ui->pickShortPeriod->setMaximum(100);
        ui->pickShortPeriod->setMinimum(0);
        ui->pickShortPeriod->setValue(12);
        ui->pickShortPeriod->setSuffix(" jours");

        ui->pickSignalPeriod->setMaximum(100);
        ui->pickSignalPeriod->setMinimum(0);
        ui->pickSignalPeriod->setValue(9);
        ui->pickSignalPeriod->setSuffix(" jours");
    }
    else {
        QMessageBox::warning(this, "Warning", "Indicateur n'est pas encores implémenté");
    }
}

AddIndicateurDialog::~AddIndicateurDialog() {
    delete ui;
}

void AddIndicateurDialog::on_AddIndicateurDialog_accepted() {
    QMap<QString, QVariant> parameters;
    if(indicateur == "EMA") {
        parameters["period"] = ui->pickEmaPeriod->value();
        evolutionCours->getCollection()->getIndicateur("EMA")->setParameters(parameters);
    }
    else if (indicateur == "RSI") {
        parameters["lookbackPeriod"] = ui->pickLookbackPeriod->value();
        parameters["overboughtBound"] = ui->pickOverbought->value();
        parameters["oversoldBound"] = ui->pickOversold->value();
        evolutionCours->getCollection()->getIndicateur("RSI")->setParameters(parameters);
    }
    else if (indicateur == "MACD") {
        parameters["longPeriod"] = ui->pickLongPeriod->value();
        parameters["shortPeriod"] = ui->pickShortPeriod->value();
        parameters["signalPeriod"] = ui->pickSignalPeriod->value();
        evolutionCours->getCollection()->getIndicateur("MACD")->setParameters(parameters);
    }
}
