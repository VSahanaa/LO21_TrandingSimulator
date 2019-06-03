#ifndef SIMULATION_H
#define SIMULATION_H
#include "strategie.h"
#include <QSettings>
#include <QTimer>
#include <QObject>
#include <QDateTime>

/* * Class Note: Stock the note taken by user
 * Constructor is private, therefore only Simulation can access it
 * The notes are organized as a QList in noteManager in class Simulation
 */
class Note {
    friend class Simulation;
    QString nom = "New note";
    QString note = "";
    QDateTime dateCreation;
    QDateTime dernierAcces;
    Note() {
        dateCreation = QDateTime::currentDateTime();
        dernierAcces = dateCreation;
    }
public:
    QString& modifierNote() {dernierAcces=QDateTime::currentDateTime(); return note;}
    QString& modifierNom() {dernierAcces = QDateTime::currentDateTime(); return nom;}
    QDateTime getDateCreation() const {return dateCreation;}
    QDateTime getDernierAcces() const {return dernierAcces;}
};


/* * Class Simulation: abstract class of every Simulation
 * a simulation has a nom, type and associates with an EvolutionCours
 * currentCours and finishCours indicate the current date and the final date in the simulation
 * each Simulation has its own Transactionmanager
*/
class Simulation {
protected:
    QString type;
    QString nom;
    EvolutionCours* evolutionCours;
    EvolutionCours::iterator currentCours = evolutionCours->begin();        //default value
    TransactionManager transactionManager;
    QList<Note> noteManager;
public:
    Simulation(QString type, QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage, double montantBaseInitial, double montantContrepartieInitial) :
        type(type), evolutionCours(evolutionCours), currentCours(coursDebut),
        transactionManager(TransactionManager(pourcentage, montantBaseInitial, montantContrepartieInitial, montantContrepartieInitial + montantContrepartieInitial/coursDebut->getClose())) {
        if (!verifierNomSimulation(nom)) throw TradingException("Simulation: ce nom est déjà pris");
            this->nom = nom;
    }
    //~Simulation();              //TO IMPLEMENT !!!
    void achat(const PaireDevises* paire, CoursOHLCV* cours, double montant) {transactionManager.addTransaction(paire, cours, true, montant);}
    void vente(const PaireDevises* paire, CoursOHLCV* cours, double montant) {transactionManager.addTransaction(paire, cours, false, montant);}
    const QString& getNom() const {return nom;}
    EvolutionCours::iterator getCurrentCours() const {return currentCours;}
    virtual void saveSimulation() const = 0;
    virtual void saveEvolutionCours() const;
    virtual void saveTransactions() const;
    virtual void saveNotes() const;
    //virtual void saveNote() const;                                                        TO IMPLEMENT !!!
    bool verifierNomSimulation(QString nom) const;          //verify wheather the name of simulation is already exist
    TransactionManager* getTransactionManager() {return &transactionManager;}
    QList<Note>& getNoteManager() {return noteManager;}
    Note& addNote();
};



/* * Class ModeManuel: Derived class of Simulation
 * has 3 operations, achat(), vente() and annule()
 * User can choose any CoursOHLCV to make a Transaction
*/
class ModeManuel : public QObject, public Simulation {
    Q_OBJECT
    CoursOHLCV* coursPicked;
public:
    ModeManuel(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage=0.001, double montantBaseInitial=0, double montantContrepartieInitial=1000000, QObject* parent=nullptr) :
        QObject(parent), Simulation("Manuel", nom, evolutionCours, coursDebut, pourcentage, montantBaseInitial, montantContrepartieInitial) {coursPicked = coursDebut;}
    //~ModeManuel();          //TO IMPLEMENT !!!
    virtual void saveSimulation() const;
signals:
    void coursPickedChanged(CoursOHLCV* cours);
    void transactionAdded();
    void transactionAnnule();
private slots:
    void setCoursPicked(CoursOHLCV* cours) {
        if(cours->getDate() < currentCours->getDate()) throw TradingException("Mode Manule: Can not pick a past day");
        coursPicked = cours;
        emit coursPickedChanged(coursPicked);
    }
public slots:
    virtual void buy_slot(double montant) {achat(evolutionCours->getPaireDevises(), coursPicked, montant);  emit transactionAdded();}
    virtual void sell_slot(double montant) {vente(evolutionCours->getPaireDevises(), coursPicked, montant); emit transactionAdded();}
    void annule() {transactionManager.deleteLastTransaction();  emit transactionAnnule();}
};

/* * Class ModeManuel: Derived class of ModeManuel, is a QObject
 * keep track of currentCours, user only know the open price of the currentCours, and can only make transaction in this Cours
 * This Mode has a QTimer to signal the change of currentCours
 * when currentCours reach finishCours, it emit a signal endSimulation()
*/
class ModePas_Pas: public ModeManuel {
    Q_OBJECT
    QTimer* timer;
public:
    ModePas_Pas(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage=0.001, double montantBaseInitial=0, double montantContrepartieInitial=1000000, unsigned int time_interval=600000, QObject* parent=nullptr);
    //~ModePas_Pas();                 //TO IMPLEMENT !!!
    void saveSimulation() const;
signals:
    void endSimulation();
private slots:
    void iteration();
public slots:
    void setTimer(unsigned int interval) {timer->setInterval(interval);}
    void pause() {timer->stop();}
    void play() {if (currentCours != evolutionCours->end()) timer->start();}
    void speedUp() {if(timer->interval() > 10000) timer->setInterval(timer->interval() - 10000);}
    void slowDown() {timer->setInterval(timer->interval() + 10000);}
    void buy_slot(double montant) {achat(evolutionCours->getPaireDevises(), currentCours, montant);}
    void sell_slot(double montant) {vente(evolutionCours->getPaireDevises(), currentCours, montant);}
};

/* * Class ModeAutomatique: Derived class of Simulation, is a QObject
 * This Mode has a QTimer to signal the change of currentCours
 * It has a strategie, in each Iteration, it pass the past information to the strategie to make a trading decision
 * when currentCours reach finishCours, it emit a signal endSimulation()
*/
class ModeAutomatique : public QObject, public Simulation {
    Q_OBJECT
    Strategie* strategie = nullptr;
    QTimer* timer;                  //timer of between cours   
public:
    ModeAutomatique(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, Strategie* strategie, double pourcentage=0.001, double montantBaseInitial=0, double montantContrepartieInitial=1000000, unsigned int time_interval=600000, QObject* parent=nullptr);
    //~ModeAutomatique();             //TO IMPLEMENT !!!
    void saveSimulation() const;
    void saveStrategie() const;
signals:
    void endSimulation();
private slots:
    void iteration();
public slots:
    void setTimer(unsigned int interval) {timer->setInterval(interval);}
    void pause() {timer->stop();}
    void play() {if (currentCours != evolutionCours->end()) timer->start();}
    void speedUp() {if(timer->interval() > 10000) timer->setInterval(timer->interval() - 10000);}
    void slowDown() {timer->setInterval(timer->interval() + 10000);}
};

/* * Class SimulationManager: container on Simulations
 * it has a nomGroupe and nomApplication for saving and restoring a Simulation
 * Each simulation after creation is add to listeSimulation
 */
class SimulationManager {
    static SimulationManager* instance;
    QString nomGroupe;
    QString nomApplication;
    QList<Simulation*> listeSimulation;
    SimulationManager(QString nomGroupe, QString nomApplication): nomGroupe(nomGroupe), nomApplication(nomApplication) {}
    ~SimulationManager();
public:
    static SimulationManager* getSimulationManager(QString nomGroupe="LO21_TD2_Groupe100", QString nomApplication="Trading Simulator") {
        if (!instance) {
            instance = new SimulationManager(nomGroupe, nomApplication);
        }
        return instance;
    }
    static void libererSimulationManager() {
        delete instance;
        instance = nullptr;
    }
    void addSimulation(Simulation* simulation) { listeSimulation.append(simulation);}

    Simulation* chargeSimulation(QString nom);          //TO IMPLEMENT !!!
    QStringList listSavedSimulation() const;
    QStringList listExistSimulation() const;
    const QString& getNomGroupe() const {return nomGroupe;}
    const QString& getNomApplication() const {return nomApplication;}
};

#endif // SIMULATION_H
