#include "configuration.h"
#include "ui_configuration.h"

Configuration::Configuration(QWidget *parent) : QDialog(parent), ui(new Ui::Configuration) {
    ui->setupUi(this);
    setListesDevise();
    ui->strategie_widget->hide();            //hide strategieParameters widget by default, show only if Mode Automatique is chosen
}

Configuration::~Configuration() {
    delete ui;
}

void Configuration::setListesDevise() {
    DevisesManager& deviseManager = DevisesManager::getManager();
    QStringList listeDeviseCodes = deviseManager.getDeviseCodes();
    ui->listeBase->addItems(listeDeviseCodes);
    ui->listeContrepartie->addItems(listeDeviseCodes);
}

void Configuration::on_addDevise_button_clicked() {
    addDevise_dialog = new AddDevise_Dialog(this);
    addDevise_dialog->setModal(true);
    addDevise_dialog->exec();
    //add new Devise to the Combo boxes
    if(addDevise_dialog->getNewDevise()) {
        ui->listeContrepartie->addItem(addDevise_dialog->getNewDevise()->getCode(), addDevise_dialog->getNewDevise()->getCode());
        ui->listeBase->addItem(addDevise_dialog->getNewDevise()->getCode(), addDevise_dialog->getNewDevise()->getCode());
    }
}

void Configuration::on_browseButton_clicked() {
    QFileDialog fdlg;
    ui->browseFile->setText(fdlg.getOpenFileName(this, tr("Choose csv file"), "./fichier_OHLCV/", "Document files (*.csv)"));
}

void Configuration::setEvolutionCours() {
    DevisesManager& deviseManager = DevisesManager::getManager();
    const PaireDevises& paire = deviseManager.getPaireDevises(ui->listeBase->currentText(), ui->listeContrepartie->currentText());
    QString fPath = ui->browseFile->text();
    evolutionCours =  new EvolutionCours(paire, fPath);
}

void Configuration::finishConfigEvolutionCours() {
    nomSimulation = ui->nameSimulation->text();
    setEvolutionCours();
    ui->mainWidget->setCurrentWidget(ui->config_page);
    qDebug() << (evolutionCours->begin())->getDate().toString("yyyy-MM-dd");
    qDebug() << (evolutionCours->end()-1)->getDate().toString("yyyy-MM-dd");
    ui->pickStartDate->setMinimumDate(evolutionCours->begin()->getDate());             //date debut du EvolutionCours
    ui->pickStartDate->setMaximumDate((evolutionCours->end()-1)->getDate());            //date fini du evolutionCours
    ui->pickStartDate->setDate(evolutionCours->begin()->getDate());                    //valeur par défault
    ui->pickPourcentage->setSuffix(" %");
    ui->pickPourcentage->setMaximum(100);
    ui->pickPourcentage->setMinimum(0);
    ui->pickPourcentage->setValue(0.1);
    ui->pickBase->setMaximum(100000000000000);
    ui->pickBase->setValue(0);
    ui->pickContrepartie->setMaximum(100000000000000);
    ui->pickContrepartie->setValue(1000000);
}

void Configuration::on_ModeManule_button_clicked() {
    if(ui->nameSimulation->text().length() == 0) throw TradingException("Nom Simulation est vide.");
    if(ui->listeBase->count()==0 || ui->listeContrepartie->count()==0) throw TradingException("Devise est vide.");
    modeSimulation = "Manuel";
    finishConfigEvolutionCours();
}

void Configuration::on_ModePas_Pas_button_clicked() {
    if(ui->nameSimulation->text().length() == 0) throw TradingException("Nom Simulation est vide.");
    if(ui->listeBase->count()==0 || ui->listeContrepartie->count()==0) throw TradingException("Devise est vide.");
    modeSimulation = "Pas_Pas";
    finishConfigEvolutionCours();
}

void Configuration::on_ModeAuto_buton_clicked() {
    if(ui->nameSimulation->text().length() == 0) throw TradingException("Nom Simulation est vide.");
    if(ui->listeBase->count()==0 || ui->listeContrepartie->count()==0) throw TradingException("Devise est vide.");
    modeSimulation = "Automatique";
    finishConfigEvolutionCours();
    ui->strategie_widget->show();
    QStringList nomStrategies = strategieFactory->listeStrategie();
    ui->listeStrategie->insertItems(0, nomStrategies);
    refreshStrategieLayout(ui->listeStrategie->currentText());
}

void Configuration::refreshStrategieLayout(QString strategieNom) {
    // clear old data
    if(strategieNom == "MA Strategie") {
        //qDebug() << ui->rsiParameters->isVisible();
        ui->rsiParameters->hide();
        ui->maParameters->show();
        ui->pickEmaPeriod->setMaximum(100);
        ui->pickEmaPeriod->setMinimum(0);
        ui->pickEmaPeriod->setValue(10);
        ui->pickEmaPeriod->setSuffix(" jours");
        }
    else if (strategieNom == "RSI Strategie") {
        ui->rsiParameters->show();
        ui->maParameters->hide();
        //qDebug() << ui->rsiParameters->isVisible();
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
}

void Configuration::on_listeStrategie_currentTextChanged(const QString &strategieNom) {
    refreshStrategieLayout(strategieNom);
}

void Configuration::createSimulation() {
    if(simulation) delete simulation;
    dateDebut = ui->pickStartDate->date();
    pourcentage = ui->pickPourcentage->value();
    montantBaseInitial = ui->pickBase->value();
    montantContrepartieInitial = ui->pickContrepartie->value();
    EvolutionCours::iterator coursDebut = evolutionCours->searchCours(dateDebut);
    if (modeSimulation == "Manuel") {
        simulation = new ModeManuel(nomSimulation, evolutionCours, coursDebut, pourcentage, montantBaseInitial, montantContrepartieInitial);
    }
    else if (modeSimulation == "Pas_Pas") {
        simulation = new ModePas_Pas(nomSimulation, evolutionCours, coursDebut, pourcentage, montantBaseInitial, montantContrepartieInitial);
    }
    else if (modeSimulation == "Automatique") {
        QString strategieNom = ui->listeStrategie->currentText();
        if(strategieNom == "MA Strategie") {
            parameters.empty();
            parameters.insert("period", ui->pickEmaPeriod->value());
        }
        else if (strategieNom == "RSI Strategie") {
            parameters.empty();
            parameters.insert("lookbackPeriod", ui->pickLookbackPeriod->value());
            parameters.insert("overboughtBound", ui->pickOverbought->value());
            parameters.insert("oversoldBound", ui->pickOversold->value());
        }
        if(strategie) delete strategie;
        strategie = strategieFactory->getStrategie(strategieNom, evolutionCours);
        strategie->setParameters(parameters);
        simulation = new ModeAutomatique(nomSimulation, evolutionCours, coursDebut, strategie, pourcentage, montantBaseInitial, montantContrepartieInitial);
    }
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    simulationManager->addSimulation(simulation);
    qDebug()<<simulation->getNom();
}

void Configuration::on_creatSimul_button_clicked() {
    createSimulation();
    Configuration::accept();
}

void Configuration::on_back_button_clicked() {
    ui->mainWidget->setCurrentWidget(ui->pickCours_page);
}
