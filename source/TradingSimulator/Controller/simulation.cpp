#include "simulation.h"

/*---------------------------------------------------------- Methodes de classe Simulation -------------------------------------------------------*/
void Simulation::saveEvolutionCours() const {
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    QSettings setting(simulationManager->getNomGroupe(), simulationManager->getNomApplication());
    setting.beginGroup("Simulation");
    setting.beginGroup(nom);
    setting.beginGroup("EvolutionCours");

    setting.beginGroup("paireDevises");     //sauvegarde paire devises
    setting.setValue("base/code", evolutionCours->getPaireDevises()->getBase().getCode());
    setting.setValue("base/monnaie", evolutionCours->getPaireDevises()->getBase().getMonnaie());
    setting.setValue("base/zone", evolutionCours->getPaireDevises()->getBase().getZoneGeographique());
    setting.setValue("contrepartie/code", evolutionCours->getPaireDevises()->getContrepartie().getCode());
    setting.setValue("contrepartie/monnaie", evolutionCours->getPaireDevises()->getContrepartie().getMonnaie());
    setting.setValue("contrepartie/zone", evolutionCours->getPaireDevises()->getContrepartie().getZoneGeographique());
    setting.setValue("surnom", evolutionCours->getPaireDevises()->getSurnom());
    setting.endGroup();
    setting.setValue("fichier", evolutionCours->getNomFichier());       //sauvegarde fichier csv
    //if (evolutionCours->saveFile()) throw TradingException("error saving csv file");
    setting.endGroup();
    setting.endGroup();
    setting.endGroup();
}

void Simulation::saveTransactions() const {
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    QSettings setting(simulationManager->getNomGroupe(), simulationManager->getNomApplication());
    setting.beginGroup("Simulation");
    setting.beginGroup(nom);
    setting.beginGroup("TransactionManager");
    setting.setValue("pourcentage", transactionManager.pourcentage);
    setting.setValue("montantBaseInitial", transactionManager.montantBaseInitial);
    setting.setValue("montantContrepartieInitial", transactionManager.montantContrepartieInitial);
    setting.setValue("montantTotalInitial", transactionManager.montantTotalInitial);
    //save history Transaction

    setting.beginWriteArray("Transaction");
    TransactionManager::iterator transactionIterator = transactionManager.head();
    int i = 0;
    while (transactionIterator) {
        setting.setArrayIndex(i++);
        setting.setValue("date", transactionIterator->getCours()->getDate().toString("yyyy-MM-dd"));
        setting.setValue("achat", transactionIterator->est_achat());
        setting.setValue("montantBase", transactionIterator->getMontantBase());
        setting.setValue("montantContrepartie", transactionIterator->getMontantContrepartie());
        transactionIterator->next();
    }
    setting.endArray();
    setting.endGroup();
    setting.endGroup();
    setting.endGroup();
}

bool Simulation::verifierNomSimulation(QString nom) const {
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    return !simulationManager->listSavedSimulation().contains(nom);
}

/*---------------------------------------------------------- Methodes de Mode Manuel -------------------------------------------------------*/

void ModeManuel::saveSimulation() {
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    QSettings setting(simulationManager->getNomGroupe(), simulationManager->getNomApplication());
    setting.beginGroup("Simulation");
    setting.beginGroup(nom);
    setting.setValue("type", type);
    setting.endGroup();
    setting.endGroup();
    saveEvolutionCours();
    saveTransactions();
}
/*---------------------------------------------------------- Methodes de Mode Automatique -------------------------------------------------------*/
ModeAutomatique::ModeAutomatique(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, Strategie* strategie, unsigned int time_interval):
    Simulation("Automatique", nom, evolutionCours, coursDebut, coursFini, pourcentage, montantBaseInitial, montantContrepartieInitial) {
    if (!strategie) throw TradingException("ModeAutomatique: Strategie is null");
    this->strategie = strategie;
    timer = new QTimer(this);
    timer->setInterval(time_interval);              //set timer interval in ms
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(iteration()));
    timer->start();
}

void ModeAutomatique::iteration() {
    double decision = (*strategie)(&transactionManager, currentCours);
    if (decision > 0) {
        achat(evolutionCours->getPaireDevises(), currentCours, decision);
    }
    else if (decision < 0) {
        vente(evolutionCours->getPaireDevises(), currentCours, -decision);
    }
    if(currentCours == finishCours) {
        timer->stop();
        emit endSimulation();
    }
    currentCours++;        //move to next day
}

void ModeAutomatique::saveSimulation() {
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    QSettings setting(simulationManager->getNomGroupe(), simulationManager->getNomApplication());
    setting.beginGroup("Simulation");
    setting.beginGroup(nom);
    setting.setValue("type", type);

    setting.endGroup();
    setting.endGroup();
    saveEvolutionCours();
    saveTransactions();
}

/*---------------------------------------------------------- Methodes de Mode Pas à pas -------------------------------------------------------*/
ModePas_Pas::ModePas_Pas(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, unsigned int time_interval):
    ModeManuel(nom, evolutionCours, coursDebut, coursFini, pourcentage, montantBaseInitial, montantContrepartieInitial) {
    type = "Pas_Pas";
    timer = new QTimer(this);
    timer->setInterval(time_interval);              //set timer interval in ms
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(iteration()));
    timer->start();
}

void ModePas_Pas::iteration(){
    if(currentCours == finishCours) {
        timer->stop();
        emit endSimulation();
    }
    currentCours++;
}

/*---------------------------------------------------------- Methodes de Simulation Manager -------------------------------------------------------*/
SimulationManager* SimulationManager::instance = nullptr;
SimulationManager::~SimulationManager(){
    for (int i=0; i<listeSimulation.length(); i++) {
        delete listeSimulation[i];
    }
    listeSimulation.empty();
}

QStringList SimulationManager::listSavedSimulation() const {
    QSettings setting(nomGroupe, nomApplication);
    setting.beginGroup("Simulation");
    QStringList listeSimulation = setting.childGroups();
    setting.endGroup();
    return listeSimulation;
}
