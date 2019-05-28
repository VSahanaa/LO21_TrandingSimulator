#ifndef SIMULATION_H
#define SIMULATION_H
#include "strategie.h"
#include <QSettings>
#include <QTimer>

/* * Abstract class of every Simulation
*/
class Simulation {
protected:
    QString type;
    QString nom;
    EvolutionCours* evolutionCours;
    EvolutionCours::iterator currentCours, finishCours;
    TransactionManager transactionManager;
public:
    Simulation(QString type, QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial):
        evolutionCours(evolutionCours), currentCours(coursDebut), finishCours(coursFini), type(type),
        transactionManager(TransactionManager(pourcentage, montantBaseInitial, montantContrepartieInitial, montantContrepartieInitial + montantContrepartieInitial/coursDebut->getClose())) {
        if (!verifierNomSimulation(nom)) throw TradingException("Simulation: ce nom est déjà pris");
            this->nom = nom;
    }
    ~Simulation();
    void achat(const PaireDevises* paire, CoursOHLCV* cours, double montant) {transactionManager.addTransaction(paire, cours, true, montant);}
    void vente(const PaireDevises* paire, CoursOHLCV* cours, double montant) {transactionManager.addTransaction(paire, cours, false, montant);}
    EvolutionCours::iterator getCurrentCours() const {return currentCours;}
    EvolutionCours::iterator getFinishCours() const {return finishCours;}
    virtual void saveSimulation() const = 0;
    virtual void saveEvolutionCours() const;
    virtual void saveTransactions() const;
    //virtual void saveNote() const;                                                        TO IMPLEMENT !!!
    bool verifierNomSimulation(QString nom) const;
    //const TransactionManager* getTransactionManager() const {return &transactionManager;}
};

class ModeManuel : public Simulation {
public:
    ModeManuel(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial) :
        Simulation("Manuel", nom, evolutionCours, coursDebut, coursFini, pourcentage, montantBaseInitial, montantContrepartieInitial) {}
    ~ModeManuel();
    virtual void saveSimulation() const;
    void annule() {transactionManager.deleteLastTransaction();}
};


class ModePas_Pas: public ModeManuel, public QObject {
    Q_OBJECT
    QTimer* timer;
public:
    ModePas_Pas(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, unsigned int time_interval=600000);
    ~ModePas_Pas();
    void saveSimulation() const;
signals:
    void endSimulation();
private slots:
    void iteration();
public slots:
    void setTimer(unsigned int interval) {timer->setInterval(interval);}
    void pause() {timer->stop();}
    void play() {if (currentCours != finishCours) timer->start();}
    void speedUp() {if(timer->interval() > 10000) timer->setInterval(timer->interval() - 10000);}
    void slowDown() {timer->setInterval(timer->interval() + 10000);}
    void buy_slot(double montant) {achat(evolutionCours->getPaireDevises(), currentCours, montant);}
    void sell_slot(double montant) {vente(evolutionCours->getPaireDevises(), currentCours, montant);}
};



class ModeAutomatique : public Simulation, public QObject {
    Q_OBJECT
    Strategie* strategie;
    QTimer* timer;                  //timer of between cours   
public:
    ModeAutomatique(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, Strategie* strategie, unsigned int time_interval=600000);
    ~ModeAutomatique();
    void saveSimulation() const;
    void saveStrategie() const;
signals:
    void endSimulation();
private slots:
    void iteration();
public slots:
    void setTimer(unsigned int interval) {timer->setInterval(interval);}
    void pause() {timer->stop();}
    void play() {if (currentCours != finishCours) timer->start();}
    void speedUp() {if(timer->interval() > 10000) timer->setInterval(timer->interval() - 10000);}
    void slowDown() {timer->setInterval(timer->interval() + 10000);}
};


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

    Simulation* chargeSimulation(QString nom);
    QStringList listSavedSimulation() const;
    const QString& getNomGroupe() const {return nomGroupe;}
    const QString& getNomApplication() const {return nomApplication;}
};

#endif // SIMULATION_H
