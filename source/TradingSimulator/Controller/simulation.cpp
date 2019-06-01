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

void Simulation::saveNotes() const {
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    QSettings setting(simulationManager->getNomGroupe(), simulationManager->getNomApplication());
    setting.beginGroup("Simulation");
        setting.beginGroup(nom);
            setting.beginGroup("NoteManager");
                setting.beginWriteArray("Note");
                    for (int i=0; i<noteManager.length(); i++){
                        setting.setArrayIndex(i);
                        setting.setValue("nom", noteManager[i].nom);
                        setting.setValue("note", noteManager[i].note);
                        setting.setValue("dateCreation", noteManager[i].dateCreation);
                        setting.setValue("dernierAcces", noteManager[i].dernierAcces);
                    }
                setting.endArray();
            setting.endGroup();
        setting.endGroup();
    setting.endGroup();
}

bool Simulation::verifierNomSimulation(QString nom) const {
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    return !simulationManager->listExistSimulation().contains(nom);
}

/*---------------------------------------------------------- Methodes de Mode Manuel -------------------------------------------------------*/

void ModeManuel::saveSimulation() const {
    saveEvolutionCours();
    saveTransactions();
    saveNotes();
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    QSettings setting(simulationManager->getNomGroupe(), simulationManager->getNomApplication());
    setting.beginGroup("Simulation");
        setting.beginGroup(nom);
            setting.setValue("type", type);
            setting.setValue("currentDate", currentCours->getDate().toString("yyyy-MM-dd"));
        setting.endGroup();
    setting.endGroup();


}

Note& Simulation::addNote() {
    Note note;
    noteManager.append(note);
    return noteManager[noteManager.length()];
}
/*---------------------------------------------------------- Methodes de Mode Automatique -------------------------------------------------------*/
ModeAutomatique::ModeAutomatique(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut,  Strategie* strategie, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, unsigned int time_interval):
    QObject(), Simulation("Automatique", nom, evolutionCours, coursDebut, pourcentage, montantBaseInitial, montantContrepartieInitial) {
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
    currentCours++;        //move to next day
    if(currentCours == evolutionCours->end()) {
        timer->stop();
        emit endSimulation();
    }

}

void ModeAutomatique::saveStrategie() const {
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    QSettings setting(simulationManager->getNomGroupe(), simulationManager->getNomApplication());
    setting.beginGroup("Simulation");
        setting.beginGroup(nom);
            setting.beginGroup("Strategie");
                setting.setValue("nom", strategie->getNom());
                //save parametrer
                QMap<QString, QVariant> parameters = strategie->getParameters();
                setting.beginWriteArray("parameters");
                    QMap<QString, QVariant>::iterator parametersIterator = parameters.begin();
                    while (parametersIterator != parameters.end()) {
                        setting.setValue(parametersIterator.key(), parametersIterator.value());
                    }
                setting.endArray();
            setting.endGroup();
        setting.endGroup();
    setting.endGroup();
}

void ModeAutomatique::saveSimulation() const {
    saveEvolutionCours();
    saveTransactions();
    saveNotes();
    saveStrategie();
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    QSettings setting(simulationManager->getNomGroupe(), simulationManager->getNomApplication());
    setting.beginGroup("Simulation");
        setting.beginGroup(nom);
            setting.setValue("type", type);
            setting.setValue("currentDate", currentCours->getDate().toString("yyyy-MM-dd"));
            setting.setValue("timerInterval", timer->interval());
        setting.endGroup();
    setting.endGroup();
}


/*---------------------------------------------------------- Methodes de Mode Pas à pas -------------------------------------------------------*/
ModePas_Pas::ModePas_Pas(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, unsigned int time_interval):
     QObject(), ModeManuel(nom, evolutionCours, coursDebut, pourcentage, montantBaseInitial, montantContrepartieInitial) {
    type = "Pas_Pas";
    timer = new QTimer(this);
    timer->setInterval(time_interval);              //set timer interval in ms
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(iteration()));
    timer->start();
}

void ModePas_Pas::iteration(){
    currentCours++;
    if(currentCours == evolutionCours->end()) {
        timer->stop();
        emit endSimulation();
    }

}

void ModePas_Pas::saveSimulation() const {
    saveEvolutionCours();
    saveTransactions();
    saveNotes();
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    QSettings setting(simulationManager->getNomGroupe(), simulationManager->getNomApplication());
    setting.beginGroup("Simulation");
        setting.beginGroup(nom);
            setting.setValue("type", type);
            setting.setValue("currentDate", currentCours->getDate().toString("yyyy-MM-dd"));
            setting.setValue("timerInterval", timer->interval());
        setting.endGroup();
    setting.endGroup();
}

/*---------------------------------------------------------- Methodes de Simulation Manager -------------------------------------------------------*/
SimulationManager* SimulationManager::instance = nullptr;
SimulationManager::~SimulationManager(){
    for (int i=0; i<listeSimulation.length(); i++) {
        delete listeSimulation[i];
    }
    listeSimulation.empty();
}

QStringList SimulationManager::listExistSimulation() const {
    QStringList listeNomSimulation = listSavedSimulation();
    for (int i=0; i<listeSimulation.length(); i++) {
        listeNomSimulation.append(listeSimulation[i]->getNom());        //list saved Simulation
    }
    return listeNomSimulation;
}

QStringList SimulationManager::listSavedSimulation() const {
    QSettings setting(nomGroupe, nomApplication);
    setting.beginGroup("Simulation");
        QStringList listeSavedSimulation = setting.childGroups();         //list saved Simulation
    setting.endGroup();
    return listeSavedSimulation;
}

/*Simulation* SimulationManager::chargeSimulation(QString nom) {

}
*/
