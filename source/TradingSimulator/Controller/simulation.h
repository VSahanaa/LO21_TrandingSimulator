#ifndef COMMANDE_H
#define COMMANDE_H
#include "strategie.h"
class Commande {
protected:
    TransactionManager* transactionManager;   
public:
    Commande() {transactionManager = TransactionManager::getTransactionManager();}
    void achat(PaireDevises* paire, CoursOHLCV* cours, double montant) {transactionManager->addTransaction(paire, cours, true, montant);}
    void vente(PaireDevises* paire, CoursOHLCV* cours, double montant) {transactionManager->addTransaction(paire, cours, false, montant);}
};

class ModeManuel : public Commande {   
    EvolutionCours* evolutionCours;         //evolutionCours associates with this command

public:
    ModeManuel(EvolutionCours* evolutionCours) : Commande(), evolutionCours(evolutionCours) {}
    void annule() {transactionManager->deleteLastTransaction();}
};

class ModeAutomatique : public Commande {
    Strategie* strategie;
    EvolutionCours::iterator currentCours;
    ModeAutomatique(EvolutionCours* evolutionCours, Strategie* strategie, EvolutionCours::iterator coursDebut) : Commande() {
        if (!strategie) throw TradingException("ModeAutomatique: Strategie is null");
        this->strategie = strategie;
        if (!coursDebut) throw TradingException("ModeAutomatique: Cours debut is null");
        this->currentCours = coursDebut;
    }
public:
    void eachIteration();
};

#endif // COMMANDE_H
