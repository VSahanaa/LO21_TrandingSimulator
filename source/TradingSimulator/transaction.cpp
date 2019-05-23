#include "transaction.h"

/*----------------------------------- Methodes de classe TransactionManager --------------------------------------*/

TransactionManager::~TransactionManager() {
    Transaction* currentTransatction;
    //supprimer tous les transaction
    while (listeTransaction) {
        currentTransatction = listeTransaction;
        listeTransaction = currentTransatction->getLastTransaction();
        delete currentTransatction;
    }
}

void TransactionManager::addTransaction(PaireDevises *paire, CoursOHLCV *cours, bool achat, double montant) {
    double currentMontantBase, currentMontantContrepartie;
    double montantBase, montantContrepartie;

    if (listeTransaction == nullptr) {
        currentMontantBase = montantBaseInitial;
        currentMontantContrepartie = montantContrepartieInitial;
    }
    else {
        currentMontantBase = listeTransaction->getMontantBase();
        currentMontantContrepartie = listeTransaction->getMontantContrepartie();
    }

    if (achat) {
        montantBase = currentMontantBase + montant*cours->getOpen()*(1-pourcentage);
        montantContrepartie = currentMontantContrepartie - montant;
        if (montantContrepartie < 0) throw TradingException("montant de devise contre partie n'est pas assez");
    }
    else {
        montantBase = currentMontantBase - montant;
        montantContrepartie = currentMontantContrepartie + montant/cours->getClose()*(1-pourcentage);
        if (montantBase < 0) throw TradingException("montant de devise de base n'est pas assez");
    }
    listeTransaction = new Transaction(listeTransaction, paire, cours, achat, montantBase, montantContrepartie);    //effectuer la transaction
}

void TransactionManager::deleteLastTransaction() {
    if (listeTransaction == nullptr) throw TradingException("Il n'y a pas transaction à annuler");
    Transaction* transactionCurrent = listeTransaction;
    listeTransaction = transactionCurrent->getLastTransaction();
    delete transactionCurrent;
}

double TransactionManager::solde() const {
    if (listeTransaction == nullptr) {
        return montantTotalInitial;
    }
    else {
        return listeTransaction->montantTotal();
    }
}
