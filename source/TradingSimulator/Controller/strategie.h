#include "transaction.h"

/* * Strategie class: base class of all Strategies
 * each Strategie has a name and an evolutionCours
 * The Constructor and Destructor is protected, which can only be accessed by Inherit classes or Strategiefactory
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
    virtual ~Strategie() = default;
    void setEvolutionCours(EvolutionCours* evolutionCours) {this->evolutionCours = evolutionCours;}
public:
    virtual Strategie* clone() {
        Strategie* clone = new Strategie(nom);
        clone->setEvolutionCours(evolutionCours);
        return clone;
    }
    virtual double operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours){return 0;  /*do nothing*/}  //implementer algorithme de trading
    //unsigned int temps; //compteur de jour => faire un evolutioncours->iterator ?
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

class MA_Strategie : public Strategie {
    friend class StrategieFactory;
    EMA* ema=nullptr;
    EMA::iterator ema_Iterator=nullptr;
    MA_Strategie(): Strategie("MA Strategie") {}
public:
    Strategie* clone();
    void setParameters(unsigned int period=10);
    double operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours);
};


class RSI_Strategie : public Strategie {
    friend class StrategieFactory;
    RSI* rsi=nullptr;
    RSI::iterator rsi_Iterator=nullptr;
    RSI_Strategie() : Strategie("RSI Strategie") {}
public:
    Strategie* clone();
    void setParameters(unsigned int lookbackPeriod = 14, double sellBound=80, double buyBound=20);
    double operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours);
};

/* * StrategieFactory keeps track only the prototype of Strategie
 * When ever a new Strategie is added to the code base, it's only need to be added here to the strategieDictonary at the constructor in order to be used with other Strategies
 * When ever a strategie is needed, function getStrategie() will create a replicate of the strategie object stored in strategieDictonary and return it with an evolutionCours
 * Strategie objects in strategieDictonary are always prototype of each Strategie with evolutionCours is null
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
    Strategie* getStrategie(QString nom, EvolutionCours* evolutionCours);
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
