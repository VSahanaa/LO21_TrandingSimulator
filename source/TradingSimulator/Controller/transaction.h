#ifndef TRANSACTION_H
#define TRANSACTION_H
/**
 * \file 	transaction.h
 * \brief 	Contient la classe transaction et son manager TransactionManager 			
 */
#include <QDate>
#include "../Core_Devises/trading.h"


/* * Class Transaction: hold information of each transaction
 * the constructor and destructor is private, therefore an only be created and deleted by TransactionManager
 * Each transaction contains the CoursOHLCV where the trading occur, PaireDevises and the montantBase, montantContrepartie of user after the transaction
 * attribute achat is a boolean to mark wheather the transaction is a purchase of selling
 */
 /**
* \class Transaction
* \brief contient les informations de chaque transaction
* attributs privés : transactionDernier, paire, cours, achat, montantBase, montantContrepartie, montantBaseInitial, montantContrepartieInitial
* méthodes privées : Transaction
* méthodes publiques : differenceBase, differenceContrepartie, getMontantBase, roi, getMontantContrepartie, getCours, est_achat, getLastTransaction, next, hasNext
* amitiéss : class TransactionManager
* Remarques : 	constructeur, destructeur privés dont seul TransactionManager à accés
                les transactions sont organisées en liste chainées
*/
class Transaction {
    friend class TransactionManager; /**< déclaration d'amitiés : TransactionManager */
    Transaction* transactionDernier = nullptr; /**< transactionDernier :Transaction* pointe sur la transaction précédente effectuée*/
    const PaireDevises* paire; /**< paire :const PaireDevises* pointe sur la paire de devise sur laquelle les transactions sont faites*/
    CoursOHLCV* cours; /**< cours :CoursOHLCV* pointe sur le cours associé à la transaction*/
    bool achat;	/**< achat :bool true signifie achat, false siignifie vente*/
    double montantBaseInitial; /**< montantBaseInitial :double montant de la devise de base possédé par l'utilisateur initialement*/
    double montantContrepartieInitial; /**< montantContrepartieInitial :double montant de la devise de contrepartie possédé par l'utilisateur initialement*/
    double montantBase; /**< montantBase :double montant actuel de la devise de base possédé par l'utilisateur*/
    double montantContrepartie; /**< montantContrepartie :double montant actuel de la devise de contrepartie possédé par l'utilisateur*///montant actuel de devise de contre partie que l'utilisateur possède
    //!Constructeur
    /**
    * \param transactionDernier :Transaction*
    * \param paire :const PaireDevises*
    * \param cours :CoursOHLCV*
    * \param achat :bool
    * \param montantBase :double
    * \param montantContrepartie :double
    * \param montantBaseInitial :double
    * \param montantContrepartieInitial :double
    */
    Transaction(Transaction* transactionDernier, const PaireDevises* paire, CoursOHLCV* cours, bool achat, double montantBase, double montantContrepartie, double montantBaseInitial, double montantContrepartieInitial):
        transactionDernier(transactionDernier), paire(paire), cours(cours), achat(achat), montantBase(montantBase), montantContrepartie(montantContrepartie), montantBaseInitial(montantBaseInitial), montantContrepartieInitial(montantContrepartieInitial) {}
public:
    //! Méthode differenceBase
    /**
    * \return double :retourne la différence entre le montant de base de cette transaction et de la précédente
    */
    double differenceBase() const {
        if(!transactionDernier) return this->montantBase - montantBaseInitial;
        return this->montantBase - transactionDernier->montantBase;
    }
    //! Méthode differenceContrepartie
    /**
    * \return double :retourne la différence entre le montant de contrepartie de cette transaction et de lla précédente
    */
    double differenceContrepartie() const {
        if(!transactionDernier) return this->montantContrepartie - montantContrepartieInitial;
        return this->montantContrepartie - transactionDernier->montantContrepartie;
    }
    //! Solde du compte
    /**
    * \return double :retourne le montant total dans la devise de contrepartie
    */
    double montantTotal() const {return montantBase*cours->getClose() + montantContrepartie;}
    //! Retour sur invertissement total
    /**
    * \return double : ratio entre le montantTotal et le montantTotalInitial
    */
    double roi(double montantTotalInitial) const {return montantTotal()/ montantTotalInitial;}
    //! Valeur de montant de base
    /**
    * \return double :retourne la valeur de l'attribut montantBase
    */
    double getMontantBase() const {return montantBase;}
    //! Valeur de montant de contre partie
    /**
    * \return double :retourne la valeur de l'attribut montantContrepartie
    */
    double getMontantContrepartie() const {return montantContrepartie;}
    //! CoursOHLCV ou effectué la transaction
    /**
    * \return CoursOHLCV* : retourne la valeur de l'attribut cours
    */
    CoursOHLCV* getCours() const {return cours;}
    //! Booléan Transaction est achat ou vente
    /**
    * \return bool : retourne la valeur de l'attribut achat
    */
    bool est_achat() const {return achat;}
    //! Pointeur vers la transaction précedente
    /**
    * \return Transaction* : retourne la valeur de l'attribut transactionDernier
    */
    Transaction* getLastTransaction() const {return transactionDernier;}
    //! Noeud suivant dans la liste chainée
    /**
    * \return Transaction* : retourne la valeur de l'attribut transactionDernier
    */
    Transaction* next() const {return getLastTransaction();}
    //! Boolean si avoir un noeud suivant
    /**
    * \return bool : true si transactionDernier existe, false sinon
    */
    bool hasNext() const {if (transactionDernier) {return true;} else {return false;}}
};

/* * Class TransactionManager: container of Transaction
 * the Transactions are organized as a linked list, the head of the list points to the most recent transaction
 * the constructor and destructor is private, therefore an only be created and deleted by a Simulation
 * It also contains the the montantBaseInitial, montantContrepartieInitial and montantTotalInitial of user at the beginning of the Simulation
 * It has an Iterator with 2 operations: next() et hasNext()
 */
/**
* \class TransactionManager
* \brief s'occupe de la classe Transaction, appartient une Simulation
* attributs : listeTransaction, pourcentage, montantBaseInitial, montantContrepartieInitial
* méthodes privées : TransactionManager, ~TransactionManager, clearTransactions
* méthodes publiques : addTransaction,deleteLastTransaction, solde, getMontantBase, getMontantContrepartie, getPourcentage, roi
* amitiés : Simulation
* Remarques : 	constructeur, destructeur privés dont seul Simulation à accés
                possède un itérateur pour parcourir les transactions avec next, hasNext
*/
class TransactionManager {
    friend class Simulation; /**<déclaration d'amitié : Simulation*/
    Transaction* listeTransaction = nullptr; /**< listeTransaction :Transaction* pointe sur la transaction la plus récente*/
    double pourcentage; /**< pourcentage :double contient l'intérêt du broker */
    double montantBaseInitial; /**< montantBaseInitial :double montant de la devise de base au début de la simulation */
    double montantContrepartieInitial; /**< montantContrepartieInitial :double montant de la devise de contrepartie au début de la simulation */
    double montantTotalInitial; /**<montantTotalInitial :double montant total disposé avant la simulation */
    //! Constructeur privé
    /**
    * \param pourcentage :double
    * \param montantBaseInitial :double
    * \param montantContrepartieInitial :double
    * \param montantTotalInitial :double
    */
    TransactionManager(double pourcentage, double montantBaseInitial, double montantContrepartieInitial, double montantTotalInitial):
        pourcentage(pourcentage), montantBaseInitial(montantBaseInitial), montantContrepartieInitial(montantContrepartieInitial), montantTotalInitial(montantTotalInitial) {}
    //! Destructeur
    ~TransactionManager();
    //! Supprimer tous les transactions
    /**
    * \return void : suppression des transactions
    */
    void clearTransactions();
public:
    //! Ajouter une nouvelle transaction avec le montant de trading
    /**
    * \param paire :PaireDevises*
    * \param achat :bool
    * \param montant :double
    * \return void : ajout d'une transaction
    */
    void addTransaction(const PaireDevises* paire, CoursOHLCV* cours, bool achat, double montant);
    //! Ajouter une nouvelle transaction avec le montant de base et contre partie apres effectuer la transaction, utilisée pour le chargement de la simulation
    /**
    * \param paire :PaireDevises*
    * \param achat :bool
    * \param montant :double
    * \param montantBase :double
    * \param montantContrepartie :double
    * \return void : ajout d'une transaction
    */
    void addTransaction(const PaireDevises* paire, CoursOHLCV* cours, bool achat, double montantBase, double montantContrepartie);
    //! Supprimer la transaction plus récent
    /**
    * \return void : supprime la dernière transaction faite (la plus récente)
    */
    void deleteLastTransaction();
    //! Solde du compte
    /**
    * \return double : donne le solde en devise de contrepartie
    */
    double solde() const;                       //retourne le solde en devise de contrepartie
    //! Montant de base du compte
    /**
    * \return double : donne le montant de la devise de base détenu par l'utilisateur au moment présent
    */
    double getMontantBase() const {
        if (!listeTransaction) {return montantBaseInitial;}
            return listeTransaction->getMontantBase();
    }
    //! Interet du broker
    /**
    * \return double : donne la valeur de l'attribut pourcentage
    */
    double getPourcentage() const {return pourcentage;}
    //! Montant de contrepartie du compte
    /**
    * \return double : donne le montant de la devise de contrepartie détenu par l'utilisateur au moment présent
    */
    double getMontantContrepartie() const {
        if (!listeTransaction) {return montantContrepartieInitial;}
            return listeTransaction->getMontantContrepartie();
    }
    //! Montant total initial
    /**
    * \return double : donne le montant totale détenu par l'utilisateur initialement
    */
    double getMontantTotalInitial() const {return montantTotalInitial;}
    using iterator = Transaction*; /**< déclaration iterator <=> Transaction* */    //definir iterator avec 2 operations: next() et hasNext()
    //! La tete de la liste chainée
    /**
    * \return iterator : donne la la transaction la plus récente
    */
    iterator head() const {return listeTransaction;}
};

#endif // TRANSACTION_H
