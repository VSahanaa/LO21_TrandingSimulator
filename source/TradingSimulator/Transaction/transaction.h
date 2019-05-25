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
    double getMontantBase() const {return montantBase;}
    double getMontantContrepartie() const {return montantContrepartie;}
    Transaction* getLastTransaction() const {return transactionDernier;}
    Transaction* next() {return getLastTransaction();}
    bool hasNext() const {if (transactionDernier) {return true;} else {return false;}}
};



class TransactionManager {
    static TransactionManager* instance;
    Transaction* listeTransaction = nullptr;    //pointeur vers la transaction le plus current, les transactions se organisent comme une liste chainée
    float pourcentage;  //profit du broker
    double montantBaseInitial;
    double montantContrepartieInitial;
    double montantTotalInitial;
    TransactionManager(const TransactionManager& transactionManager) = delete;
    TransactionManager& operator=(const TransactionManager& transactionManager) = delete;
    TransactionManager(float pourcentage, double montantBaseInitial, double montantContrepartieInitial, double montantTotalInitial): pourcentage(pourcentage), montantBaseInitial(montantBaseInitial), montantContrepartieInitial(montantContrepartieInitial), montantTotalInitial(montantTotalInitial) {}
    ~TransactionManager();
public:
    static TransactionManager* getTransactionManager() {
        if (instance == nullptr) throw TradingException("Transaction Manager n'est pas instancié");
        return instance;
    }
    static TransactionManager* getTransactionManager(float pourcentage, double montantBaseInitial, double montantContrepartieInitial, double montantTotalInitial){
        if (instance == nullptr) {
            instance = new TransactionManager(pourcentage, montantBaseInitial, montantContrepartieInitial, montantTotalInitial);
        }
        return instance;
    }

    static void libererTransactionManager(){
        delete instance;
        instance = nullptr;
    }

    void addTransaction(PaireDevises* paire, CoursOHLCV* cours, bool achat, double montant);
    void deleteLastTransaction();   //supprimer transaction derniere
    double solde() const;
    double roi() const {return solde()/ montantTotalInitial;}
    using iterator = Transaction*;      //definir iterator avec 2 operations: next() et hasNext()
    iterator head() const {return listeTransaction;}
};

#endif // TRANSACTION_H
