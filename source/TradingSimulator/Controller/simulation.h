#ifndef COMMANDE_H
#define COMMANDE_H
#include "strategie.h"
#include <QTimer>
class Simulation {
protected:
    QString type;
    EvolutionCours* evolutionCours;
    EvolutionCours::iterator currentCours, finishCours;
    TransactionManager transactionManager;
public:
    Simulation(QString type, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial):
        evolutionCours(evolutionCours), currentCours(coursDebut), finishCours(coursFini), type(type),
        transactionManager(TransactionManager(pourcentage, montantBaseInitial, montantContrepartieInitial, montantContrepartieInitial + montantContrepartieInitial/coursDebut->getClose())) {}
    void achat(const PaireDevises* paire, CoursOHLCV* cours, double montant) {transactionManager.addTransaction(paire, cours, true, montant);}
    void vente(const PaireDevises* paire, CoursOHLCV* cours, double montant) {transactionManager.addTransaction(paire, cours, false, montant);}
    EvolutionCours::iterator getCurrentCours() const {return currentCours;}
    EvolutionCours::iterator getFinishCours() const {return finishCours;}
    //const TransactionManager* getTransactionManager() const {return &transactionManager;}
};

class ModeManuel : public Simulation {
public:
    ModeManuel(EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial) :
        Simulation("Manuel", evolutionCours, coursDebut, coursFini, pourcentage, montantBaseInitial, montantContrepartieInitial) {}
    void annule() {transactionManager.deleteLastTransaction();}
};


class ModePas_Pas: public ModeManuel, public QObject {
    Q_OBJECT
    QTimer* timer;
public:
    ModePas_Pas(EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, unsigned int time_interval=600000):
        ModeManuel(evolutionCours, coursDebut, coursFini, pourcentage, montantBaseInitial, montantContrepartieInitial) {
        type = "Pas_Pas";
        timer = new QTimer(this);
        timer->setInterval(time_interval);              //set timer interval in ms
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(iteration()));
        timer->start();
    }
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
    ModeAutomatique(EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, Strategie* strategie, unsigned int time_interval=600000):
        Simulation("Automatique", evolutionCours, coursDebut, coursFini, pourcentage, montantBaseInitial, montantContrepartieInitial) {
        if (!strategie) throw TradingException("ModeAutomatique: Strategie is null");
        this->strategie = strategie;
        timer = new QTimer(this);
        timer->setInterval(time_interval);              //set timer interval in ms
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(iteration()));
        timer->start();
    }
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

#endif // COMMANDE_H
