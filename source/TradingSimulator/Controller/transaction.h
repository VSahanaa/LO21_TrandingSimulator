#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <QDate>
#include "../Core_Devises/trading.h"

/* * Class Transaction: hold information of each transaction
 * the constructor and destructor is private, therefore an only be created and deleted by TransactionManager
 * Each transaction contains the CoursOHLCV where the trading occur, PaireDevises and the montantBase, montantContrepartie of user after the transaction
 * attribute achat is a boolean to mark wheather the transaction is a purchase of selling
 */
class Transaction {
    friend class TransactionManager;
    Transaction* transactionDernier = nullptr;      //organiser comme une liste chainée
    const PaireDevises* paire;
    CoursOHLCV* cours;
    bool achat;
    double montantBase;         //montant actuel de devise de base que l'utilisateur possède
    double montantContrepartie; //montant actuel de devise de contre partie que l'utilisateur possède

    Transaction(Transaction* transactionDernier, const PaireDevises* paire, CoursOHLCV* cours, bool achat, double montantBase, double montantContrepartie):
        transactionDernier(transactionDernier), paire(paire), cours(cours), achat(achat), montantBase(montantBase), montantContrepartie(montantContrepartie) {}
public:
    double differenceBase() const {return this->montantBase - transactionDernier->montantBase;}
    double differenceContrepartie() const {return this->montantContrepartie - transactionDernier->montantContrepartie;}
    double montantTotal() const {return montantBase/cours->getClose() + montantContrepartie;}
    double getMontantBase() const {return montantBase;}
    double getMontantContrepartie() const {return montantContrepartie;}
    CoursOHLCV* getCours() const {return cours;}
    bool est_achat() const {return achat;}
    Transaction* getLastTransaction() const {return transactionDernier;}
    Transaction* next() const {return getLastTransaction();}
    bool hasNext() const {if (transactionDernier) {return true;} else {return false;}}
};

/* * Class TransactionManager: container of Transaction
 * the Transactions are organized as a linked list, the head of the list points to the most recent transaction
 * the constructor and destructor is private, therefore an only be created and deleted by a Simulation
 * It also contains the the montantBaseInitial, montantContrepartieInitial and montantTotalInitial of user at the beginning of the Simulation
 * It has an Iterator with 2 operations: next() et hasNext()
 */
class TransactionManager {
    friend class Simulation;
    Transaction* listeTransaction = nullptr;    //pointeur vers la transaction le plus current, les transactions se organisent comme une liste chainée
    double pourcentage;                          //interet du broker
    double montantBaseInitial, montantContrepartieInitial, montantTotalInitial;

    TransactionManager(double pourcentage, double montantBaseInitial, double montantContrepartieInitial, double montantTotalInitial):
        pourcentage(pourcentage), montantBaseInitial(montantBaseInitial), montantContrepartieInitial(montantContrepartieInitial), montantTotalInitial(montantTotalInitial) {}
    ~TransactionManager();
public:
    void addTransaction(const PaireDevises* paire, CoursOHLCV* cours, bool achat, double montant);
    void addTransaction(const PaireDevises* paire, CoursOHLCV* cours, bool achat, double montantBase, double montantContrepartie);
    void deleteLastTransaction();
    double solde() const;                       //retourne le solde en devise de contrepartie
    double getMontantBase() const {
        if (!listeTransaction) {return montantBaseInitial;}
            return listeTransaction->getMontantBase();
    }
    double getPourcentage() const {return pourcentage;}
    double getMontantContrepartie() const {
        if (!listeTransaction) {return montantContrepartieInitial;}
            return listeTransaction->getMontantContrepartie();
    }
    double roi() const {return solde()/ montantTotalInitial;}
    using iterator = Transaction*;      //definir iterator avec 2 operations: next() et hasNext()
    iterator head() const {return listeTransaction;}
};

#endif // TRANSACTION_H
