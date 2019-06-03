#include "simulation.h"

/*---------------------------------------------------------- Methodes de classe Simulation -------------------------------------------------------*/
Simulation::~Simulation() {
    delete evolutionCours;
}

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

void Simulation::loadTransactions() {
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    QSettings setting(simulationManager->getNomGroupe(), simulationManager->getNomApplication());
    setting.beginGroup("Simulation");
        setting.beginGroup(nom);
            setting.beginGroup("TransactionManager");
                double pourcentage = setting.value("pourcentage").toDouble();
                double montantBaseInitial = setting.value("montantBaseInitial").toDouble();
                double montantContrepartieInitial = setting.value("montantContrepartieInitial").toDouble();
                double montantTotalInitial =  setting.value("montantTotalInitial").toDouble();
                transactionManager = TransactionManager(pourcentage, montantBaseInitial, montantContrepartieInitial, montantTotalInitial);
                int size = setting.beginReadArray("Transaction");
                for (int i=0; i<size; i++) {
                    setting.setArrayIndex(i);
                    EvolutionCours::iterator cours = evolutionCours->searchCours(QDate::fromString(setting.value("date").toString(), "yyyy-MM-dd"));
                    transactionManager.addTransaction(evolutionCours->getPaireDevises(), cours, setting.value("achat").toBool(), setting.value("montantBase").toDouble(), setting.value("montantContrepartie").toDouble());
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
                        setting.setValue("dateCreation", noteManager[i].dateCreation.toString("yyyy-MM-dd : HH.mm"));
                    }
                setting.endArray();
            setting.endGroup();
        setting.endGroup();
    setting.endGroup();
}


void Simulation::loadNotes() {
    noteManager.clear();
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    QSettings setting(simulationManager->getNomGroupe(), simulationManager->getNomApplication());
    setting.beginGroup("Simulation");
        setting.beginGroup(nom);
            setting.beginGroup("NoteManager");
                int size = setting.beginReadArray("Note");
                    for (int i=0; i<size; i++){
                        setting.setArrayIndex(i);
                        Note& note = addNote();
                        note.setNom(setting.value("nom").toString());
                        note.setNote(setting.value("note").toString());
                        note.setDateCreation(QDateTime::fromString(setting.value("dateCreation").toString(), "yyyy-MM-dd : HH.mm"));
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


Note& Simulation::addNote() {
    Note note;
    noteManager.append(note);
    return noteManager[noteManager.length()];
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


/*---------------------------------------------------------- Methodes de Mode Automatique -------------------------------------------------------*/
ModeAutomatique::ModeAutomatique(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut,  Strategie* strategie, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, unsigned int time_interval, QObject* parent):
    QObject(parent), Simulation("Automatique", nom, evolutionCours, coursDebut, pourcentage, montantBaseInitial, montantContrepartieInitial) {
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
                setting.beginGroup("parameters");
                    QMap<QString, QVariant>::iterator parametersIterator = parameters.begin();
                    while (parametersIterator != parameters.end()) {
                        setting.setValue(parametersIterator.key(), parametersIterator.value());
                    }
                setting.endGroup();
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
ModePas_Pas::ModePas_Pas(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, unsigned int time_interval, QObject* parent):
    ModeManuel(nom, evolutionCours, coursDebut, pourcentage, montantBaseInitial, montantContrepartieInitial, parent) {
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
        listeNomSimulation.append(listeSimulation[i]->getNom());        //list of simulation that already exist in the program
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

EvolutionCours* SimulationManager::chargeEvolutionCours(QString nomSimulation) {
    DevisesManager& deviseManager = DevisesManager::getManager();
    Devise* base;
    Devise* contrepartie;
    QString filename;
    EvolutionCours* evolutionCours;
    QSettings setting(nomGroupe, nomApplication);
    setting.beginGroup("Simulation");
        setting.beginGroup(nomSimulation);
            setting.beginGroup("EvolutionCours");
                setting.beginGroup("paireDevises");     //load paire devises
                    if(deviseManager.getDeviseCodes().contains(setting.value("base/code").toString())) {
                        base = deviseManager.getDevise(setting.value("base/code").toString());
                    }
                    else {
                        base = deviseManager.creationDevise(setting.value("base/code").toString(), setting.value("base/monnaie").toString(), setting.value("base/zone").toString());
                    }

                    if(deviseManager.getDeviseCodes().contains(setting.value("contrepartie/code").toString())) {
                        contrepartie = deviseManager.getDevise(setting.value("contrepartie/code").toString());
                    }
                    else {
                        contrepartie = deviseManager.creationDevise(setting.value("contrepartie/code").toString(), setting.value("contrepartie/monnaie").toString(), setting.value("contrepartie/zone").toString());
                    }
                    PaireDevises& paire =  deviseManager.getPaireDevises(setting.value("base/code").toString(), setting.value("contrepartie/code").toString());
                    paire.setSurnom(setting.value("surnom").toString());
                setting.endGroup();
                filename = setting.value("fichier").toString();
                evolutionCours = new EvolutionCours(paire, filename);
            setting.endGroup();
        setting.endGroup();
    setting.endGroup();
    return evolutionCours;
}

Simulation* SimulationManager::chargeSimulation(QString nom) {
    EvolutionCours* evolutionCours = chargeEvolutionCours(nom);
    Simulation* simulation = nullptr;
    QString type;
    EvolutionCours::iterator currentCours;
    double pourcentage, montantBaseInitial, montantContrepartieInitial;
    QSettings setting(nomGroupe, nomApplication);

    setting.beginGroup("Simulation");
        setting.beginGroup(nom);
            currentCours = evolutionCours->searchCours(QDate::fromString(setting.value("currentDate").toString(), "yyyy-MM-dd"));
            type = setting.value("type").toString();
            setting.beginGroup("TransactionManager");
            pourcentage =  setting.value("TransactionManager/pourcentage").toDouble();
            montantBaseInitial = setting.value("TransactionManager/montantBaseInitial").toDouble();
            montantContrepartieInitial = setting.value("TransactionManager/montantContrepartieInitial").toDouble();
            if(type == "Manuel") {
                simulation = new ModeManuel(nom, evolutionCours, currentCours, pourcentage, montantBaseInitial, montantContrepartieInitial);
            }
            else if (type == "Pas_Pas") {
                int time_interval = setting.value("timerInterval").toInt();
                simulation = new ModePas_Pas(nom, evolutionCours, currentCours, pourcentage, montantBaseInitial, montantContrepartieInitial, time_interval);
            }
            else if (type == "Automatique"){
                int time_interval = setting.value("timerInterval").toInt();
                StrategieFactory* strategieFactory = StrategieFactory::getStrategieFactory();
                setting.beginGroup("Strategie");
                Strategie* strategie = strategieFactory->getStrategie( setting.value("nom").toString(), evolutionCours);
                QMap<QString, QVariant> parameters;
                    setting.beginGroup("parameters");
                        QStringList listeParameters = setting.childKeys();
                        for(int i=0; i<listeParameters.count(); i++) {
                            parameters[listeParameters[i]] = setting.value(listeParameters[i]);
                        }
                    setting.endGroup();
                setting.endGroup();
                strategie->setParameters(parameters);
                simulation = new ModeAutomatique(nom, evolutionCours, currentCours, strategie, pourcentage, montantBaseInitial, montantContrepartieInitial, time_interval);
            }
        setting.endGroup();
    setting.endGroup();
    simulation->loadTransactions();
    simulation->loadNotes();
    addSimulation(simulation);
    return simulation;
}

