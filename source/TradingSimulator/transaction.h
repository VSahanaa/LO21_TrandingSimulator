#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <QDate>
#include "trading.h"

class Transaction {
    Transaction* transactionDernier = nullptr;      //organiser comme une liste chainée
    QDate date;
    PaireDevises* paire;
    CoursOHLCV* cours;
    bool achat;
    double montantBase; //montant actuel de devise de base que l'utilisateur possède
    double montantContrepartie; //montant actuel de devise de contre partie que l'utilisateur possède
public:
    Transaction(Transaction* transactionDernier, QDate date, PaireDevises* paire, CoursOHLCV* cours, bool achat, double montantBase, double montantContrepartie)
        :transactionDernier(transactionDernier), date(date), paire(paire), cours(cours), achat(achat), montantBase(montantBase), montantContrepartie(montantContrepartie) {}
    double differenceBase() const {return this->montantBase - transactionDernier->montantBase;}
    double differenceContrepartie() const {return this->montantContrepartie - transactionDernier->montantContrepartie;}
    double montantTotal() const {return montantBase*cours->getClose() + montantContrepartie;}
    double roi(double montantInitial) const {return montantTotal()/montantInitial;}
    QDate getDate() const {return date;}
};

class TransactionManager {

};

#endif // TRANSACTION_H
