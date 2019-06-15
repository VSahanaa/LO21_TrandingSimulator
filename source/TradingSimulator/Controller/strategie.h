#ifndef STRATEGIE_H
#define STRATEGIE_H
/**
 * \file 	strategie.h
 * \brief 	Contient les stratégies de trading
 * 	
 * 	Contient les classes concernant les strategies
 * 			
 */
#include "transaction.h"

/**
* \class Strategie
* \brief classe mère abstraite pour ajouter des stratégies de trading
* attributs protégés : nom, evolutionCours
* méthodes virtuelles protégées : setEvolutionCours, Strategie
* méthodes virtuelles : ~Strategie, clone, getNom, setParameters, getParameters, operator()
* amitiéss : class StrategieFactory
* Remarques : 	Appliquer design patern Strategy, utiliseé seul pour Polymorphisme
* Fontionnement : 	le trading se base sur l'operator() qui retourne :
                        - un nombre négatif pour une vente
                        - un nombre positif pour un achat
                        - 0 pour ne rien faire
                    chaque stratégie charge un clone() pour faire une réplique
*/
class Strategie {
    friend class StrategieFactory; /**< declaration d'amitiés : DevisesManager */
protected:
    QString nom = "unnamed strategie"; /**< nom :QString nom de la stratégie */
    EvolutionCours* evolutionCours = nullptr; /**< evolutionCours :EvolutionCours* pointe sur la serie de cours sur laquelle s'appliquera la stratégie*/
    //! Constructeur avec le nom de strategie
    /**
    * \param nom :QString
    */
    Strategie(QString nom) : nom(nom){}
    Strategie(Strategie* strategie) = delete;
    //! Appliquer la strategie sur une evolution cours
    /**
    * \param evolutionCours :EvolutionCours*
    * \return void : modifie la valeur de l'attribut evolutionCours
    */
    void setEvolutionCours(EvolutionCours* evolutionCours) {this->evolutionCours = evolutionCours;}
public:
    //! Destructeur par défault
    virtual ~Strategie() = default;
    //! Duppliquer un objet Stratégie
    /**
    * \return Strategie* : revoie une réplique de la stratégie
    */
    virtual Strategie* clone() {
        Strategie* clone = new Strategie(nom);
        clone->setEvolutionCours(evolutionCours);
        return clone;
    }
    //! Nom de la stratégie
    /**
    * \return const QString& : la valeur de l'attribut nom
    */
    const QString& getNom() const {return nom;}
    //! Interface virtuelle setParameters(), changer les valeurs de paramètres de Stratégie
    /**
    * \param QMap<QString,QVariant> parameter
    * \return void : modifie les paramatres
    */
    virtual void setParameters(QMap<QString, QVariant> parameters) {/*do nothing*/}
    //! Interface virtuelle getParameters, retourne les valeurs de paramètres de Stratégie
    /**
    * \return QMap<QString,QVariant> : donne les paramatres de la statégie
    */
    virtual QMap<QString, QVariant> getParameters() const {return QMap<QString, QVariant>(); /*return empty object*/}
    //! Implémenter l'algorithme de stratégie, donne la décision pour une journée
    /**
    * \return double : le montant de la transaction
    * renvoie :	- un montant positif si la transaction à faire est un achat
                - un montant négatif si la transaction à faire est une vente
                - 0 s'il ne faut rien faire
    */
    virtual double operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours){return 0;  /*do nothing*/}  //implementer algorithme de trading
    //int hausse; //PERIODE 5utilisation pour les methodes pendu, marteau... : -1 baissiere, 0 neutre, 1 hausse
        //hausse
        //void updateHausse(){};
        //Indicateur graphique
        //bool verte(const CoursOHLCV& c);

        //int pendu(const CoursOHLCV& c);
        //int marteau(const CoursOHLCV& c);
        //int etoile(const CoursOHLCV& c);
        //int marteauinverse(const CoursOHLCV& c);
        //bool lignependante(const CoursOHLCV& c1,const CoursOHLCV& c2);
        //bool cielcouvert(const CoursOHLCV& c1,const CoursOHLCV& c2);
        //bool avalementhaussiere(const CoursOHLCV& c1,const CoursOHLCV& c2);
        //bool avalementbaissiere(const CoursOHLCV& c1,const CoursOHLCV& c2);
        //a faire le doji
};

/**
* \class MA_Strategie
* \brief herite de Strategie, strategie basée sur l'EMA
* attributs : ema, ema_Iterator
* méthodes privées : MA_Strategie
* méthodes publiques : ~MA_Strategie clone, setParameters, getParameters, operator()
* amitiéss : class StrategieFactory
*/
class MA_Strategie : public Strategie {
    friend class StrategieFactory;	/**< Déclaration d'amitié : StrategieFactory */
    EMA* ema=nullptr; /**< ema :EMA* pointe sur l'indicateur EMA associé à l'evolutionCours sur laquelle va s'appliquer la strategie*/
    EMA::iterator ema_Iterator=nullptr; /**< ema_Iterator :EMA::iterator permet de parcourir le tableau de valeurs EMA par jour*/
    //! Constructeur
    MA_Strategie(): Strategie("MA Strategie") {}
public:
    //! Destructeur
    ~MA_Strategie() {delete ema;}
    //! Implémenter l'interface clone
    /**
    * \return Strategie* : renvoie une réplique de la stratégie MA
    */
    Strategie* clone();
    //! Implémenter interface setParameters()
    /**
    * \param QMap<QString,QVariant> parameter
    * \return void : modifie les paramatres
    */
    void setParameters(QMap<QString, QVariant> parameters);
    //! Implémenter interface getParameters()
    /**
    * \return QMap<QString,QVariant> : donne les paramatres de la statégie
    */
    QMap<QString, QVariant> getParameters() const {return ema->getParameters();}
    //! Implémenter algorithme de trading
    /**
    * \return double : le montant de la transaction
    * renvoie :	- un montant positif si la transaction à faire est un achat
                - un montant négatif si la transaction à faire est une vente
                - 0 s'il ne faut rien faire
    */
    double operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours);
};

/* * Class RSI_Strategie: Implement RSI Trading Strategy
 * Parameters of this strategy is a lookbackPeriod(unsigned int), an overboughtBound(double), an oversoldBound(double) for a RSI indicator
 * the parameters is pass to the object is encapsulated in a QMap<QString, QVariant> object
 */
 /**
* \class RSI_Strategie
* \brief herite de Strategie, strategie basée sur l'RSI
* attributs : rsi, rsi_Iterator
* méthodes privées : RSI_Strategie
* méthodes publiques : ~RSI_Strategie, clone, setParameters, getParameters, operator()
* amitiéss : class StrategieFactory
*/
class RSI_Strategie : public Strategie {
    friend class StrategieFactory; /**< Déclaration d'amitié : StrategieFactory */
    RSI* rsi=nullptr; /**< rsi :RSI* pointe sur l'indicateur RSI associé à l'evolutionCours sur laquelle va s'appliquer la strategie*/
    RSI::iterator rsi_Iterator=nullptr; /**< rsi_Iterator :RSI::iterator permet de parcourir le tableau de valeurs RSI par jour*/
    //! Constructeur
    RSI_Strategie() : Strategie("RSI Strategie") {}
public:
    //! Destructeur
    ~RSI_Strategie() {delete rsi;}
    //! Implémenter interface clone()
    /**
    * \return Strategie* : renvoie une réplique de la stratégie RSI
    */
    Strategie* clone();
    //! Implémenter interface setParameters()
    /**
    * \param QMap<QString,QVariant> parameter
    * \return void : modifie les paramatres
    */
    void setParameters(QMap<QString, QVariant> parameters);
    //! Implémenter interface getParameters()
    /**
    * \return QMap<QString,QVariant> : donne les paramatres de la statégie
    */
    QMap<QString, QVariant> getParameters() const {return rsi->getParameters();}
    //! Implémenter algorithme de trading
    /**
    * \return double : le montant de la transaction
    * renvoie :	- un montant positif si la transaction à faire est un achat
                - un montant négatif si la transaction à faire est une vente
                - 0 s'il ne faut rien faire
    */
    double operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours);
};

/* * Class StrategieFactory: keeps track only the prototype of Strategie, applies Singleton partern and Factory pattern
 * When ever a new Strategie is added to the code base, it's only need to be added here to the strategieDictonary at the constructor in order to be used with other Strategies
 * When ever a strategie is needed, function getStrategie() will create a replicate of the strategie object stored in strategieDictonary and return it with an evolutionCours
 * Strategie objects in strategieDictonary are always prototype of each Strategie with evolutionCours is null
 * the Strategie returned by getStrategie() need to setParameters() before it can be used
 */
 /**
* \class StrategieFactory
* \brief se stocke les prototypes des Strategie pour produit des stratégie selon les besoins
* attributs : rsi, rsi_Iterator
* méthodes privées : StrategieFactory, ~StrategieFactory
* méthodes publiques : getStrategieFactory, libererFactory, getStrategie, listeStrategie
* amitiéss : class StrategieFactory
* Remarques : 	design pattern singleton, et design pattern factory et builder
                l'ajout d'une strategie provoque l'ajout de son nom au dictionnaire de stratégie
                la duplication est supprimée
*/
class StrategieFactory {
    static StrategieFactory* instance; /**< instance :StrategieFactory* pointe sur l'instance unique de StrategieFactory*/
    QHash<QString, Strategie*> strategieDictionary; /**< strategieDictionary :QHash<QString, Strategie*> contient le dictionnaire de stratégies*/
    //! Constructeur privé
    StrategieFactory();
    //! Destructeur privé
    ~StrategieFactory();
    StrategieFactory(StrategieFactory*) = delete;
    StrategieFactory& operator=(StrategieFactory*) = delete;
public:
    //! Retourner instance unique de StrategieFactory
    /**
    * \return StrategieFactory* : renvoie la valeur de l'attribut instance si elle existe et la créer, sinon
    */
    static StrategieFactory* getStrategieFactory(){
        if (instance == nullptr) {
            instance = new StrategieFactory();
        }
        return instance;
    }
    //! Libérer l'instance
    /**
    * \return void : libère instance
    */
    static void libererFactory() {
        delete instance;
        instance = nullptr;
    }
    //! Retourner la strategie demandé et s'applique cette stratégie sur une évolution cours fournit en entrée
    /**
    * \param nom :QString
    * \param evolutionCours :EvolutionCours*
    * \return Strategie* : renvoie la valeur du pointeur sur la stratégie demandée sur l'EvolutionCours souhaité
    */
    Strategie* getStrategie(QString nom, EvolutionCours* evolutionCours) const;
    //! Liste de Strategie disponible
    /**
    * \return const QStringList : renvoie la liste des stratégies disponibles
    */
    const QStringList listeStrategie() const;
};



/*
class Strategie_Trivial : public Strategie {
    double limiteBase;
    double limiteContrepartie;

    Strategie_Trivial(QString n, EvolutionCours& e, unsigned int nbdejours, double limiteB, double limiteC):	//calculer du montant de base
        nom(n), listecoursOHLCV(e), temps(nbdejours), hausse(0), limiteBase(limiteB), limiteContrepartie(limiteC) {}
    ~Strategie_Trivial()=default;
public:
    double operator ()(const Transaction& precedent);
}
*/

/*
class Strategie_Scalping :public Strategie {
    RSI* rsi;
public:
    double operator()(const Transaction& precedent);
}*/

#endif //STRATEGIE_H
