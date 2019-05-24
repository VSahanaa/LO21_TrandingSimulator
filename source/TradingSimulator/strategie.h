#include "indicateur.h"
#include "transaction.h"

class Strategie {
    friend class StrategieFactory;
protected:
    QString nom;
    EvolutionCours* evolutionCours;
    Strategie(QString nom, EvolutionCours* evolutionCours) : nom(nom), evolutionCours(evolutionCours) {}
    virtual ~Strategie() {}

public:
    //pure virtual function of abstract class
    virtual double operator()() = 0;   //implementer algorithme de trading, retourne le montant à effectuer la transaction



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

class StrategieFactory {
    static StrategieFactory* instance; //singleton
    QHash<QString, Strategie*> strategieDictionary;
    EvolutionCours* evolutionCours;
    IndicateurFactory* indicateurFactory;


    StrategieFactory(EvolutionCours* evolutionCours);
    ~StrategieFactory() { strategieDictionary.clear();}
    StrategieFactory(IndicateurFactory*) = delete;
    StrategieFactory& operator=(IndicateurFactory*) = delete;
public:
    static StrategieFactory* getIndicateurFactory(EvolutionCours* evolutionCours){
        if (instance == nullptr) {
            instance = new StrategieFactory(evolutionCours);
        }
        else if (instance->evolutionCours != evolutionCours) {
            //create new factory
            StrategieFactory::libererFactory();
            instance = new StrategieFactory(evolutionCours);
        }
        return instance;
    }

    static void libererFactory() {
        delete instance;
        instance = nullptr;
    }

    Indicateur* getStrategie(QString nom); //????????
};


class MA_Strategie : public Strategie {
    friend class StrategieFactory;
    EMA* ema;
    EMA::iterator ema_Iterator;
    MA_Strategie(EvolutionCours* evolutionCours, EMA* ema) : Strategie("MA_Strategie", evolutionCours) {
        if (!ema) throw TradingException("MA_Stategie: EMA is null");
        this->ema = ema;
        ema_Iterator = ema->begin();
    }
public:

    double operator()(Transaction* latestTransaction, EvolutionCours::iterator currentCours);
};


class RSI_Strategie : public Strategie {
    friend class StrategieFactory;
    RSI* rsi;
    RSI::iterator rsi_Iterator;
    double buyBound, sellBound;
    RSI_Strategie(EvolutionCours* evolutionCours, RSI* rsi, double buyBound=20, double sellBound=80);
public:
    double operator()(Transaction* latestTransaction, EvolutionCours::iterator currentCours);
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
