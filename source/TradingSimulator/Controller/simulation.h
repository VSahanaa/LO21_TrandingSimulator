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
    QString nom = "New note";           //nom is unique
    QString note = "";
    QDateTime dateCreation;
    QDateTime dernierAcces;
    Note() {
        dateCreation = QDateTime::currentDateTime();
        dernierAcces = dateCreation;
    }
    void setDateCreation(QDateTime dateCreation) {this->dateCreation = dateCreation;}
public:
    QString& getNote() {dernierAcces=QDateTime::currentDateTime(); return note;}
    QString& getNom() {dernierAcces = QDateTime::currentDateTime(); return nom;}
    QDateTime getDateCreation() const {return dateCreation;}
    QDateTime getDernierAcces() const {return dernierAcces;}
    void setNote(QString note) {dernierAcces=QDateTime::currentDateTime(); this->note = note;}
    void setNom(QString nom) {dernierAcces=QDateTime::currentDateTime(); this->nom = nom;}
};


/* * Class Simulation: abstract class of every Simulation,
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
    QList<Note*> noteManager;
public:
    Simulation(QString type, QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage, double montantBaseInitial, double montantContrepartieInitial) :
        type(type), evolutionCours(evolutionCours), currentCours(coursDebut),
        transactionManager(TransactionManager(pourcentage, montantBaseInitial, montantContrepartieInitial, montantContrepartieInitial + montantBaseInitial*coursDebut->getClose())) {
        //if (!verifierNomSimulation(nom)) throw TradingException("Simulation: ce nom est déjà pris");
        this->nom = nom;
    }
    ~Simulation();
    void achat(CoursOHLCV* cours, double montant) {transactionManager.addTransaction(evolutionCours->getPaireDevises(), cours, true, montant);}
    void vente(CoursOHLCV* cours, double montant) {transactionManager.addTransaction(evolutionCours->getPaireDevises(), cours, false, montant);}
    EvolutionCours* getEvolutionCours() const {return evolutionCours;}
    const QString& getNom() const {return nom;}
    const QString& getType() const {return type;}
    EvolutionCours::iterator getCurrentCours() const {return currentCours;}
    virtual void saveSimulation() const = 0;
    void saveEvolutionCours() const;
    void saveTransactions() const;
    void saveNotes() const;
    void loadTransactions();
    void loadNotes();
    //virtual void saveNote() const;                                                        TO IMPLEMENT !!!
    bool verifierNomSimulation(QString nom) const;          //verify wheather the name of simulation is already exist
    TransactionManager* getTransactionManager() {return &transactionManager;}
    using NoteManager = QList<Note*>;
    NoteManager& getNoteManager() {return noteManager;}
    Note* addNote();
    //int searchNote(QString nom);
};



/* * Class ModeManuel: Derived class of Simulation, is a QObject, coursPicked is the picked cours to make the transaction
 * has 3 operations, achat(), vente() and annule()
 * User can choose any CoursOHLCV to make a Transaction
*/
class ModeManuel : public Simulation {

public:
    ModeManuel(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage=0.001, double montantBaseInitial=0, double montantContrepartieInitial=1000000) :
        Simulation("Manuel", nom, evolutionCours, coursDebut, pourcentage, montantBaseInitial, montantContrepartieInitial) {}
    ~ModeManuel() = default;
    virtual void saveSimulation() const;
    void annule() {transactionManager.deleteLastTransaction();}
};

/* * Class ModePas_Pas: Derived class of ModeManuel, is a QObject
 * keep track of currentCours, user only know the open price of the currentCours, and can only make transaction in this Cours
 * This Mode has a QTimer to signal the change of currentCours
 * when currentCours reach finishCours, it emit a signal endSimulation()
*/
class ModePas_Pas: public QObject, public ModeManuel {
    Q_OBJECT
    QTimer* timer;
public:
    ModePas_Pas(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage=0.001, double montantBaseInitial=0, double montantContrepartieInitial=1000000, unsigned int time_interval=30000, QObject* parent=nullptr);
    ~ModePas_Pas() {delete timer;}
    void saveSimulation() const;
    void setTimer(unsigned int interval) {timer->setInterval(interval); qDebug() << timer->interval();}
    void achat(double montant) {transactionManager.addTransaction(evolutionCours->getPaireDevises(), currentCours, true, montant);}
    void vente(double montant) {transactionManager.addTransaction(evolutionCours->getPaireDevises(), currentCours, false, montant);}
signals:
    void coursChanged();
    void endSimulation();
private slots:
    void iteration();
public slots:
    void goBack(QDate date);
    /*
    void pause() {timer->stop();}
    void play() {if (currentCours != evolutionCours->end()) timer->start();}
    void speedUp() {if(timer->interval() > 10000) timer->setInterval(timer->interval() - 10000);}
    void slowDown() {timer->setInterval(timer->interval() + 10000);}
    */
};

/* * Class ModeAutomatique: Derived class of Simulation, is a QObject, applies Strategie pattern
 * This Mode has a QTimer to signal the change of currentCours
 * It stock a strategie pointer, by overloading operator (), strategie can implement object function
 * in each Iteration, it pass the past information to the strategie to make a trading decision
 * when currentCours reach finishCours, it emit a signal endSimulation()
*/
class ModeAutomatique : public QObject, public Simulation {
    Q_OBJECT
    Strategie* strategie = nullptr;
    QTimer* timer;                  //timer of between cours   
public:
    ModeAutomatique(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, Strategie* strategie, double pourcentage=0.001, double montantBaseInitial=0, double montantContrepartieInitial=1000000, unsigned int time_interval=30000, QObject* parent=nullptr);
    ~ModeAutomatique() {delete strategie;   delete timer;}
    void saveSimulation() const;
    void saveStrategie() const;
    QString getStrategieName() const {return strategie->getNom();}
    void setTimer(unsigned int interval) {timer->setInterval(interval);}
signals:
    void coursChanged();
    void endSimulation();
private slots:
    void iteration();
    /*
    void pause() {timer->stop();}
    void play() {if (currentCours != evolutionCours->end()) timer->start();}
    void speedUp() {if(timer->interval() > 10000) timer->setInterval(timer->interval() - 10000);}
    void slowDown() {timer->setInterval(timer->interval() + 10000);}
    */
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
    void removeSimulation(Simulation* simulation) {
        if (!simulation) return;
        for (int i=0; i<listeSimulation.count(); i++) {
            if (listeSimulation[i] == simulation) listeSimulation.removeAt(i);
            break;
        }
    }
    EvolutionCours* chargeEvolutionCours(QString nomSimulation);
    Simulation* chargeSimulation(QString nom);
    QStringList listSavedSimulation() const;
    QStringList listExistSimulation() const;
    const QString& getNomGroupe() const {return nomGroupe;}
    const QString& getNomApplication() const {return nomApplication;}
};

#endif // SIMULATION_H
