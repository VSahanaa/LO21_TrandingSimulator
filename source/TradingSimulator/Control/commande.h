#ifndef COMMANDE_H
#define COMMANDE_H
#include "strategie.h"
class Commande {
protected:
    TransactionManager* transactionManager;
    EvolutionCours* currentEvolutionCours;
    static Commande* instance;
    Commande(const Commande& commande) = delete;
    Commande& operator=(const Commande& commande) = delete;
    Commande(EvolutionCours* evolutionCours) {
        if (!evolutionCours) throw TradingException("Commande: evolution Cours is null");
        this->currentEvolutionCours = evolutionCours;
        transactionManager = TransactionManager::getTransactionManager();}
public:
    //la commande doit savoir le Transaction Manager et evolution Cours actuel pour commander les transactions
    //static virtual Commande* getCommande(EvolutionCours* currentEvolutionCours) = 0;

    static void libererCommande() {
        delete instance;
        instance = nullptr;
    }

    void achat(PaireDevises* paire, CoursOHLCV* cours, double montant) {transactionManager->addTransaction(paire, cours, true, montant);}
    void vente(PaireDevises* paire, CoursOHLCV* cours, double montant) {transactionManager->addTransaction(paire, cours, false, montant);}

};

class ModeManuel : public Commande {
    ModeManuel(EvolutionCours* evolutionCours) : Commande(evolutionCours) {}
public:
    void annule() {transactionManager->deleteLastTransaction();}
};

class ModeAutomatique : public Commande {
    Strategie* strategie;
    EvolutionCours::iterator currentCours;
    ModeAutomatique(EvolutionCours* evolutionCours, Strategie* strategie, EvolutionCours::iterator coursDebut) : Commande(evolutionCours) {
        if (!strategie) throw TradingException("ModeAutomatique: Strategie is null");
        this->strategie = strategie;
        if (!coursDebut) throw TradingException("ModeAutomatique: Cours debut is null");
        this->currentCours = coursDebut;
    }
public:
    void eachIteration();
};

#endif // COMMANDE_H
