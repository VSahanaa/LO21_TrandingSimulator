#ifndef COMMANDE_H
#define COMMANDE_H
#include "transaction.h"

class Commande {
protected:
    TransactionManager* transactionManager;
    static Commande* instance;
    Commande(const Commande& commande) = delete;
    Commande& operator=(const Commande& commande) = delete;
    Commande() {transactionManager = TransactionManager::getTransactionManager();}
public:
    static Commande* getCommande() {
        if (instance == nullptr) {
            instance = new Commande();
        }
        return instance;
    }

    static void libererCommande() {
        delete instance;
        instance = nullptr;
    }
    void achat(PaireDevises* paire, CoursOHLCV* cours, double montant) {transactionManager->addTransaction(paire, cours, true, montant);}
    void vente(PaireDevises* paire, CoursOHLCV* cours, double montant) {transactionManager->addTransaction(paire, cours, false, montant);}

};

class ModeManuel: public Commande {
public:
    ModeManuel(const Commande& commande) = delete;
    ModeManuel& operator=(const Commande& commande) = delete;
    void annule() {transactionManager->deleteLastTransaction();}
};

#endif // COMMANDE_H
