#include "transaction.h"

/* * Class Strategie: base class of all Strategies
 * each Strategie has a name and an evolutionCours
 * The Constructor is protected, which can only be created by Inherit classes or Strategiefactory
 * Trading algorithm is implemented in operator(), which returns the trading decision for each day
 *      - a negative value is for selling
 *      - a positive value is for buying
 *      - 0 is for holding
 * each Strategie overload a clone() method to make a replicate of it
 */
class Strategie {
    friend class StrategieFactory;
protected:
    QString nom = "unnamed strategie";
    EvolutionCours* evolutionCours = nullptr;
    Strategie(QString nom) : nom(nom){}
    Strategie(Strategie* strategie) = delete;
    void setEvolutionCours(EvolutionCours* evolutionCours) {this->evolutionCours = evolutionCours;}
public:
    virtual ~Strategie() = default;
    virtual Strategie* clone() {
        Strategie* clone = new Strategie(nom);
        clone->setEvolutionCours(evolutionCours);
        return clone;
    }
    const QString& getNom() const {return nom;}
    virtual void setParameters(QMap<QString, QVariant> parameters) {/*do nothing*/}
    virtual QMap<QString, QVariant> getParameters() const {return QMap<QString, QVariant>(); /*return empty object*/}
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

/* * Class MA_Strategie: Implement MA Trading Strategy
 * Parameters of this strategy is a period(int) for an EMA indicator
 * the parameters is pass to the object is encapsulated in a QMap<QString, QVariant> object
 */
class MA_Strategie : public Strategie {
    friend class StrategieFactory;
    EMA* ema=nullptr;
    EMA::iterator ema_Iterator=nullptr;
    MA_Strategie(): Strategie("MA Strategie") {}
public:
    Strategie* clone();
    void setParameters(QMap<QString, QVariant> parameters);
    QMap<QString, QVariant> getParameters() const {return ema->getParameters();}
    double operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours);
};

/* * Class RSI_Strategie: Implement RSI Trading Strategy
 * Parameters of this strategy is a lookbackPeriod(unsigned int), an overboughtBound(double), an oversoldBound(double) for a RSI indicator
 * the parameters is pass to the object is encapsulated in a QMap<QString, QVariant> object
 */
class RSI_Strategie : public Strategie {
    friend class StrategieFactory;
    RSI* rsi=nullptr;
    RSI::iterator rsi_Iterator=nullptr;
    RSI_Strategie() : Strategie("RSI Strategie") {}
public:
    Strategie* clone();
    void setParameters(QMap<QString, QVariant> parameters);
    QMap<QString, QVariant> getParameters() const {return rsi->getParameters();}
    double operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours);
};

/* * Class StrategieFactory: keeps track only the prototype of Strategie, applies Singleton partern and Factory pattern
 * When ever a new Strategie is added to the code base, it's only need to be added here to the strategieDictonary at the constructor in order to be used with other Strategies
 * When ever a strategie is needed, function getStrategie() will create a replicate of the strategie object stored in strategieDictonary and return it with an evolutionCours
 * Strategie objects in strategieDictonary are always prototype of each Strategie with evolutionCours is null
 * the Strategie returned by getStrategie() need to setParameters() before it can be used
 */
class StrategieFactory {
    static StrategieFactory* instance;              //singleton
    QHash<QString, Strategie*> strategieDictionary;
    StrategieFactory();
    ~StrategieFactory();
    StrategieFactory(StrategieFactory*) = delete;
    StrategieFactory& operator=(StrategieFactory*) = delete;
public:
    static StrategieFactory* getStrategieFactory(){
        if (instance == nullptr) {
            instance = new StrategieFactory();
        }
        return instance;
    }
    static void libererFactory() {
        delete instance;
        instance = nullptr;
    }
    Strategie* getStrategie(QString nom, EvolutionCours* evolutionCours) const;
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
