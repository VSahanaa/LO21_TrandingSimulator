#ifndef COMMANDE_H
#define COMMANDE_H
#include "transaction.h"
#include "evolutionviewer.h"
class Commande {
protected:
    TransactionManager* transactionManager;
    EvolutionCours* currentEvolutionCours;
    static Commande* instance;
    Commande(const Commande& commande) = delete;
    Commande& operator=(const Commande& commande) = delete;
    Commande(EvolutionCours* evolutionCours) : currentEvolutionCours(evolutionCours) {transactionManager = TransactionManager::getTransactionManager();}
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

class ModeManuel: public Commande, public QObject {
    Q_OBJECT
    CoursOHLCV* currentCours;
    ModeManuel(EvolutionCours* evolutionCours) : Commande(evolutionCours) {}
public:
    void annule() {transactionManager->deleteLastTransaction();}
private slots:
    void changeCours(Bougie* bougie) {currentCours = &(bougie->getCoursOHLCV());}
};

#endif // COMMANDE_H
