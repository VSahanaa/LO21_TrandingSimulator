#include "transaction.h"

/*----------------------------------- Methodes de classe TransactionManager --------------------------------------*/
void TransactionManager::clearTransactions() {
    Transaction* currentTransatction;
    //supprimer tous les transaction
    while (listeTransaction) {
        currentTransatction = listeTransaction;
        listeTransaction = currentTransatction->getLastTransaction();
        delete currentTransatction;
    }
}
TransactionManager::~TransactionManager() {
    clearTransactions();
}

void TransactionManager::addTransaction(const PaireDevises *paire, CoursOHLCV *cours, bool achat, double montant) {
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
        montantBase = currentMontantBase + (1-pourcentage)/montant*cours->getOpen();
        montantContrepartie = currentMontantContrepartie - montant;
        if (montantContrepartie < 0) throw TradingException("montant de devise contre partie n'est pas assez");
    }
    else {
        montantBase = currentMontantBase - montant;
        montantContrepartie = currentMontantContrepartie + (1-pourcentage)*montant*cours->getOpen();
        if (montantBase < 0) throw TradingException("montant de devise de base n'est pas assez");
    }
    listeTransaction = new Transaction(listeTransaction, paire, cours, achat, montantBase, montantContrepartie, montantBaseInitial, montantContrepartieInitial);    //effectuer la transaction
}

void TransactionManager::addTransaction(const PaireDevises *paire, CoursOHLCV *cours, bool achat, double montantBase, double montantContrepartie) {
    listeTransaction = new Transaction(listeTransaction, paire, cours, achat, montantBase, montantContrepartie, montantBaseInitial, montantContrepartieInitial);
}

void TransactionManager::deleteLastTransaction() {
    if (listeTransaction == nullptr) return;
    Transaction* transactionCurrent = listeTransaction;
    listeTransaction = transactionCurrent->getLastTransaction();
    qDebug() << "delete transaction";
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
