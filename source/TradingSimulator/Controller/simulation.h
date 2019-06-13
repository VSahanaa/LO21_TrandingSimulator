#ifndef SIMULATION_H
#define SIMULATION_H

/**
 * \file 	simulation.h
 * \brief 	Contient les classes nécessaires à la simulation
 * 	
 * 	Contient les classes Note, Simulation, les modes de simulation, et SimulationManager
 * 			
 */

#include "strategie.h"
#include <QSettings>
#include <QTimer>
#include <QObject>
#include <QDateTime>

 /**
* \class Note
* \brief stock les notes prises par l'utilisateur
* attributs : nom, note, dateCreation, dernierAcces
* méthodes privées : setDateCreation
* méthodes publiques : modifierNom, modifierNote, getDateCreation, getDernierAcces, setNom, setNote
* amitiéss : class Simulation
* Remarques : 	seules la classe Simulation a accés au constructeur
*				les notes sont organisées comme QList dans l'attribut noteManager dans la classe Simulation
*/
class Note {
    friend class Simulation; /** déclaration d'amitié : Simulation */
    QString nom = "New note";/**< nom :QString contient le nom de la note*/        //nom is unique
    QString note = ""; /**< note :QString contient les notes */
    QDateTime dateCreation; /**< dateCreation :QDateTime contient la date et l'heure de la création de la note */
    QDateTime dernierAcces; /**< dernierAcces :QDateTime contient la date et l'heure du dernier accés de la note */
    //! Constructeur
	/**
	* \param evolutionCours :EvolutionCours*
	* \return void : modifie la valeur de l'attribut evolutionCours
	*/
	Note() {
        dateCreation = QDateTime::currentDateTime();
        dernierAcces = dateCreation;
    }
	//! méthode setDateCreation
	/**
	* \param dateCreation :QDateTime
	* \return void
	*/
    void setDateCreation(QDateTime dateCreation) {this->dateCreation = dateCreation;}
public:
	//! méthode getNote
	/**
	* \return QString& : revoie la valeur de note
	*/
    QString& getNote() {dernierAcces=QDateTime::currentDateTime(); return note;}
	//! méthode getNote
	/**
	* \return QString& : revoie la valeur de note
	*/
    QString& getNom() {dernierAcces = QDateTime::currentDateTime(); return nom;}
	//! méthode getDateCreation
	/**
	* \return QDateTime : revoie la valeur de dateCreation après modification
	*/
    QDateTime getDateCreation() const {return dateCreation;}
	//! méthode getDernierAcces
	/**
	* \return QDateTime : revoie la valeur de dernierAcces après modification
	*/
    QDateTime getDernierAcces() const {return dernierAcces;}
    //! méthode setNote
	/**
	* \param note :QString
	* \return void :modifie la valeur de note
	*/
	void setNote(QString note) {dernierAcces=QDateTime::currentDateTime(); this->note = note;}
    	//! méthode setNom
	/**
	* \param nom :QString
	* \return void :modifie la valeur de nom
	*/
	void setNom(QString nom) {dernierAcces=QDateTime::currentDateTime(); this->nom = nom;}
};


 /**
* \class Simulation
* \brief classe abstraite pour créer toutes les simulations
* attributs : type, nom, evolutionCours, currentCours, transactionManager, noteManager
* méthodes publiques : simulation, ~simulation, achat, vente, getNom, getType, getEvolutionCours getCurrentCours, saveEvolutionCours, saveTransactions, saveNotes, loadNotes, loadTransactions, getTransactionManager, getNoteManager, addNote
* methode virtuelle publique : saveSimulation
* Remarques : chaque simulation a son propre TransactionManager
*/
class Simulation {
protected:
    QString type; /**< type :QString type de simulation(lequel)*/
    QString nom;/**< nom :QString pour identifier la simulation*/
    EvolutionCours* evolutionCours; /**< evolutionCours :EvolutionCours* pointe sur les cours sur lesquels porte la simulation*/
    EvolutionCours::iterator currentCours = evolutionCours->begin(); /**< currentCours :EvolutionCours::iterator pointe sur le cours OHLCV en cours*/
    TransactionManager transactionManager;/**< transactionManager :TransactionManager représente le manager qui s'occupe des transactions*/
    QList<Note*> noteManager; /**< noteManager :QList<Note> contient les notes prises au cours de la transaction*/
public:
	//! constructeur
	/**
	* \param type :QString
	* \param nom :QString 
	* \param evolutionCours :EvolutionCours*
	* \param coursDebut :EvolutionCours::iterator
	* \param poucentage :double
	* \param montantBaseInitial :double
	* \param montantContrepartieInitial :double
	* \param parent :QObject* 
	*/
    Simulation(QString type, QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage, double montantBaseInitial, double montantContrepartieInitial) :
        type(type), evolutionCours(evolutionCours), currentCours(coursDebut),
        transactionManager(TransactionManager(pourcentage, montantBaseInitial, montantContrepartieInitial, montantContrepartieInitial + montantBaseInitial*coursDebut->getClose())) {
        //if (!verifierNomSimulation(nom)) throw TradingException("Simulation: ce nom est déjà pris");
        this->nom = nom;
    }
	//! Destructeur
    ~Simulation();
	//! Méthode achat
	/**
	* \param cours :CoursOHLCV*
	* \param montant :double
	* \return void : ajoute la transaction en achat
	*/
    void achat(CoursOHLCV* cours, double montant) {transactionManager.addTransaction(evolutionCours->getPaireDevises(), cours, true, montant);}
    //! Méthode vente
	/**
	* \param cours :CoursOHLCV*
	* \param montant :double
	* \return void : ajoute la transaction en vente
	*/
	void vente(CoursOHLCV* cours, double montant) {transactionManager.addTransaction(evolutionCours->getPaireDevises(), cours, false, montant);}
    //! Méthode getEvolutionCours
	/**
	* \return const QString& : retourne la valeur de l'attribut evolutionCours
	*/ 
	EvolutionCours* getEvolutionCours() const {return evolutionCours;}
    //! Méthode getNom
	/**
	* \return const QString& : retourne la valeur de l'attribut nom
	*/    
	const QString& getNom() const {return nom;}
    //! Méthode getType
	/**
	* \return const QString& : retourne la valeur de l'attribut type
	*/
    const QString& getType() const {return type;}
    //! Méthode getCurrentCours
	/**
	* \return EvolutionCours::iterator : retourne le pointeur CoursOHLCV* vers le cours OHLCV en cours
	*/
	EvolutionCours::iterator getCurrentCours() const {return currentCours;}
    //! Méthode virtuelle pure saveSimulation
	/**
	* \return void : sauvegarde la simulation
	*/
	virtual void saveSimulation() const = 0;
    //! Méthode saveEvolutionCours
	/**
	* \return void : sauvegarde les cours OHLCV
	*/
	void saveEvolutionCours() const;
	//! Méthode saveTransactions
	/**
	* \return void : sauvegarde les transactions
	*/
    void saveTransactions() const;
	//! Méthode saveNotes
	/**
	* \return void : sauvegarde les notes prises
	*/
    void saveNotes() const;
	//! Méthode loadTransactions
	/**
	* \return void : charge les transactions
	*/
    void loadTransactions();
	//! Méthode loadNotes
	/**
	* \return void : charge les notes
	*/
    void loadNotes();
	//! Méthode getTransactionManager
	/**
	* \return TransactionManager* : pointe sur le manager qui gère les transactions
	*/
    TransactionManager* getTransactionManager() {return &transactionManager;}
    using NoteManager = QList<Note*>; /**< declaration NoteManager <=> Qlist<Note*>*/
    //! Méthode getNoteManager
	/**
	* \return NoteManager& : renvoie la valeur de l'attribut noteManager, c'est à dire les notes prises
	*/
	NoteManager& getNoteManager() {return noteManager;}
	//! Méthode addNote
	/**
	* \return Note& : ajoute la note
	*/
    Note* addNote();
    //int searchNote(QString nom);
};



 /**
* \class ModeManuel
* \brief hérite de la classe Simulation
* méthodes publiques : ModeManuel,~ModeManuel, annule
* méthodes publiques virtuelles : saveSimulation
* Remarques : l'utilisateur peut choisir sur quel cours il souhaite faire la transaction
*/
class ModeManuel : public Simulation {

public:
	//! constructeur
	/**
	* \param nom :QString 
	* \param evolutionCours :EvolutionCours*
	* \param coursDebut :EvolutionCours::iterator
	* \param poucentage :double
	* \param montantBaseInitial : double
	* \param montantContrepartieInitial : double
	* \param parent :QObject* 
	*/
    ModeManuel(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage=0.001, double montantBaseInitial=0, double montantContrepartieInitial=1000000) :
        Simulation("Manuel", nom, evolutionCours, coursDebut, pourcentage, montantBaseInitial, montantContrepartieInitial) {}
    //! Destructeur
	~ModeManuel() = default;
	//! Méthode virtuelle saveSimulation
	/**
	* \return void : sauvegarde la simulation
	*/
    virtual void saveSimulation() const;
	//! Méthode annule
	/**
	* \return void : pour annuler la dernière transaction
	*/
    void annule() {transactionManager.deleteLastTransaction();}
};

/**
* \class ModePas_Pas
* \brief hérite de la classe Simulation, de la classe ModeManuel et de la class QObject
* attributs : timer
* méthodes publiques : ModePas_Pas,~ModePas_Pas, saveSimulation, setTimer, achat, vente
* signals publics : endSimulation, coursChanged
* slots privées :iteration
* slots publiques : goBack
*/
class ModePas_Pas: public QObject, public ModeManuel {
    Q_OBJECT
    QTimer* timer; /**< timer :QTimer pour avancer et reculer dans le temps*/
public:
	//! constructeur
	/**
	* \param nom :QString 
	* \param evolutionCours :EvolutionCours*
	* \param coursDebut :EvolutionCours::iterator
	* \param poucentage :double
	* \param montantBaseInitial : double
	* \param montantContrepartieInitial : double
	* \param time_interval :unsigned int
	* \param parent :QObject* 
	*/
    ModePas_Pas(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage=0.001, double montantBaseInitial=0, double montantContrepartieInitial=1000000, unsigned int time_interval=5000, QObject* parent=nullptr);
    //!Destructeur
	~ModePas_Pas() {delete timer;}
	//! Méthode saveSimulation
	/**
	* \return void : sauvegarde la simulation
	*/
    void saveSimulation() const;
	//! Méthode setTimer
	/**
	* \param interval :unsigned int
	* \return void : permet de modifier le timer
	*/
    void setTimer(unsigned int interval) {timer->setInterval(interval); qDebug() << timer->interval();}
    //! Méthode achat
	/**
	* \param montant :double
	* \return void : ajoute la transaction en achat
	*/
	void achat(double montant) {transactionManager.addTransaction(evolutionCours->getPaireDevises(), currentCours, true, montant);}
    //! Méthode achat
	/**
	* \param montant :double
	* \return void : ajoute la transaction en achat
	*/
	void vente(double montant) {transactionManager.addTransaction(evolutionCours->getPaireDevises(), currentCours, false, montant);}
signals:
	//! Signal coursChanged
	/**
	* \return void : transmettre le message de changement de cours 
	*/
    void coursChanged();
	//! Signal endSimulation
	/**
	* \return void : transmettre le message de fin de simulation
	*/
    void endSimulation();
private slots:
	//! Slot privée iteration
	/**
	* \return void : faire passer le message pour itérer les cours et avancer/reculer dans le temps
	*/
    void iteration();
public slots:
	//! Slot goBack
	/**
	* \param date :QDate
	* \return void : retourner à la date indiquée
	*/
    void goBack(QDate date);
    /*
    void pause() {timer->stop();}
    void play() {if (currentCours != evolutionCours->end()) timer->start();}
    void speedUp() {if(timer->interval() > 10000) timer->setInterval(timer->interval() - 10000);}
    void slowDown() {timer->setInterval(timer->interval() + 10000);}
    */
};

/**
* \class ModeAutomatique
* \brief hérite de la classe Simulation et de la class QObject
* attributs : timer, strategie
* méthodes publiques : ModeAutomatique, ~ModeAutomatique, saveSimulation, saveStrategie, getStrategieName, setTimer
* signals publics : endSimulation, coursChanged
* slots privées :iteration
* slots publiques setTimer, pause, play, speedUp, slowDown
*/
class ModeAutomatique : public QObject, public Simulation {
    Q_OBJECT
    Strategie* strategie = nullptr;
    QTimer* timer;                  //timer of between cours   
public:
	//! constructeur
	/**
	* \param nom :QString 
	* \param evolutionCours :EvolutionCours*
	* \param coursDebut :EvolutionCours::iterator
	* \param poucentage :double
	* \param montantBaseInitial : double
	* \param montantContrepartieInitial : double
	* \param time_interval :unsigned int
	* \param parent :QObject* 
	*/
    ModeAutomatique(QString nom, EvolutionCours* evolutionCours, EvolutionCours::iterator coursDebut, Strategie* strategie, double pourcentage=0.001, double montantBaseInitial=0, double montantContrepartieInitial=1000000, unsigned int time_interval=5000, QObject* parent=nullptr);
    //! Destructeur
	~ModeAutomatique() {delete strategie;   delete timer;}
    //! Méthode saveSimulation
	/**
	* \return void : sauvegarde la simulation
	*/
    void saveSimulation() const;
    //! Méthode saveStrategie
	/**
	* \return void : sauvegarde la strategie
	*/
    void saveStrategie() const;
	//! Méthode getStrategieName
	/**
	* \return QString : retourne le nom de la strategie utilisée
	*/
    QString getStrategieName() const {return strategie->getNom();}
	//! Méthode setTimer
	/**
	* \param interval :unsigned int
	* \return void : permet de modifier le timer
	*/
    void setTimer(unsigned int interval) {timer->setInterval(interval);}
signals:
	//! Signal coursChanged
	/**
	* \return void : transmettre le message de changement de cours 
	*/
    void coursChanged();
	//! Signal endSimulation
	/**
	* \return void : transmettre le message de fin de simulation
	*/
    void endSimulation();
private slots:
	//! Slot privée iteration
	/**
	* \return void : faire passer le message pour itérer les cours et avancer/reculer dans le temps
	*/
    void iteration();
    /*
    void pause() {timer->stop();}
    void play() {if (currentCours != evolutionCours->end()) timer->start();}
    void speedUp() {if(timer->interval() > 10000) timer->setInterval(timer->interval() - 10000);}
    void slowDown() {timer->setInterval(timer->interval() + 10000);}
    */
};

/* * Class SimulationManager: container on Simulations
 * it has a nomGroupe and nomApplication for saving and restoring a Simulation
 * Each simulation after creation is add to listeSimulation
 */
/**
* \class SimulationManager
* \brief gère les simulations
* attributs : instance, nomGroupe, nomApplication, listeSimulation
* méthodes privées : SimulationManager, ~SimulationManager
* méthodes publiques : getSimulationManager, libererSimulationManager, addSimulation, removeSimulation
chargeEvolutionCours, listExistSimulation, listSavedSimulation, getNomApplication, getNomGroupe
* Remarques : chaque simulation est ajouté à la liste après sa création
*/
class SimulationManager {
    static SimulationManager* instance; /**< instance :static SimulationManager* pointe sur l'unique manager qui gère les simulations*/
    QString nomGroupe; /**< nomGroupe :QString représente le nom du groupe*/
    QString nomApplication; /**< nomApplication :QString représente le nom de l'application */
    QList<Simulation*> listeSimulation; /**< listeSimulation :QList<simulation> liste des simulations */
    //! Constructeur
	/**
	* \param nomGroupe :QString
	* \param nomApplication :QString
	*/    
	SimulationManager(QString nomGroupe, QString nomApplication): nomGroupe(nomGroupe), nomApplication(nomApplication) {}
    //! Destructeur
	~SimulationManager();
public:
	//! Méthode getSimulationManager 
	/**
	* \param nomGroupe :QString 
	* \param nomApplication :QString 
	* \return static SimulationManager* : renvoie la valeur de l'attribut instance, et la crée si elle est null
	*/
    static SimulationManager* getSimulationManager(QString nomGroupe="LO21_TD2_Groupe100", QString nomApplication="Trading Simulator") {
        if (!instance) {
            instance = new SimulationManager(nomGroupe, nomApplication);
        }
        return instance;
    }
	//! Méthode libererSimulationManager
	/**
	* \return static void : libère l'instance
	*/
    static void libererSimulationManager() {
        delete instance;
        instance = nullptr;
    }
	//! Méthode addSimulation
	/**
	* \param simulation :Simulation*
	* \return void : ajoute la simulation
	*/
    void addSimulation(Simulation* simulation) { listeSimulation.append(simulation);}
    //! Méthode removeSimulation
	/**
	* \param simulation :void
	* \return void : supprime la simulation de la liste des simulation
	*/
	void removeSimulation(Simulation* simulation) {
        if (!simulation) return;
        for (int i=0; i<listeSimulation.count(); i++) {
            if (listeSimulation[i] == simulation) listeSimulation.removeAt(i);
            break;
        }
    }
    //! Méthode chargeEvolutionCours
	/**
	* \param nomSimulation :QString
	* \return EvolutionCours* : renvoie la valeur du pointeur sur l'evolutionCours associé à la simulation
	*/
    EvolutionCours* chargeEvolutionCours(QString nomSimulation);
	//! Méthode chargeSimulation
	/**
	* \param nom :QString
	* \return Simulation* : renvoie la simulation dont le nom est donnée en paramètre
	*/
    Simulation* chargeSimulation(QString nom);
	//! Méthode listSavedSimulation
	/**
	* \return QStringList : renvoie la liste des noms des simulations sauvegardées
	*/
    QStringList listSavedSimulation() const;
	//! Méthode listExistSimulation
	/**
	* \return QStringList : renvoie la liste des noms des simulations existantes
	*/
    QStringList listExistSimulation() const;
	//! Méthode getNomGroupe
	/**
	* \return const QString& : renvoie la valeur de getNomGroupe
	*/
    const QString& getNomGroupe() const {return nomGroupe;}
	//! Méthode getNomApplication
	/**
	* \return const QString& : renvoie la valeur de getNomApplication
	*/
    const QString& getNomApplication() const {return nomApplication;}
	//! Méthode verifierNomSimulation
	/**
	* \param nom :QString
	* \return bool : true si une simulation du même nom exist, false sinon
	*/
    bool verifierNomSimulation(QString nom) const;                //verify wheather the name of simulation is already exist
    //! Méthode deleteSavedSimulation
	/**
	* \param nom :QString
	* \return void : supprime la simulation qui a nom donné (si elle avait été sauvegardée)
	*/
	void deleteSavedSimulation(QString nom);
};

#endif // SIMULATION_H
