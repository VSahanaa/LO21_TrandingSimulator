#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <QDate>
#include "trading.h"

class Transaction {
    Transaction* transactionDernier = nullptr;      //organiser comme une liste chainée
    PaireDevises* paire;
    CoursOHLCV* cours;
    bool achat;
    double montantBase; //montant actuel de devise de base que l'utilisateur possède
    double montantContrepartie; //montant actuel de devise de contre partie que l'utilisateur possède
public:
    Transaction(Transaction* transactionDernier, PaireDevises* paire, CoursOHLCV* cours, bool achat, double montantBase, double montantContrepartie)
        :transactionDernier(transactionDernier), paire(paire), cours(cours), achat(achat), montantBase(montantBase), montantContrepartie(montantContrepartie) {}
    double differenceBase() const {return this->montantBase - transactionDernier->montantBase;}
    double differenceContrepartie() const {return this->montantContrepartie - transactionDernier->montantContrepartie;}
    double montantTotal() const {return montantBase/cours->getClose() + montantContrepartie;}
    double roi(double montantTotalInitial) const {return montantTotal() / montantTotalInitial;}
    double getMontantBase() const {return montantBase;}
    double getMontantContrepartie() const {return montantContrepartie;}
    Transaction* getTransactionDernier() const {return transactionDernier;}
};

class TransactionManager {
    Transaction* listeTransaction = nullptr;    //pointeur vers la transaction le plus current, les transactions se organisent comme une liste chainée
    float pourcentage;
    double montantBaseInitial;
    double montantContrepartieInitial;
    double montantTotalInitial;
public:
    //TransactionManager();
    //~TransactionManager();
    void addTransaction(PaireDevises* paire, CoursOHLCV* cours, bool achat, double montant);
    void deleteTransaction();   //supprimer transaction derniere
    double solde() const;
};

#endif // TRANSACTION_H
