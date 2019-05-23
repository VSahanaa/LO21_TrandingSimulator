#include "indicateur.h"
#include "transaction.h"
class Strategie {
protected:
    QString nom;
    EvolutionCours* evolutioncours;
    QDate currentDate;      //assigner au date debut de simulation
    //unsigned int temps; //compteur de jour => faire un evolutioncours->iterator ?
    //int hausse; //PERIODE 5utilisation pour les methodes pendu, marteau... : -1 baissiere, 0 neutre, 1 hausse
	
	//Constructeur et destructeur

	
/*	//Empecher la recopie de stratégie.
	Strategie(const Strategie& s) = delete;
    Strategie& operator=(const Strategie& s) = delete;
*/	
    public:
        Strategie(QString nom, EvolutionCours* evolutionCours, QDate dateDebut): nom(nom), evolutioncours(evolutionCours), currentDate(dateDebut){}
        virtual double operator()() = 0;   //implementer algorithme de trading
        //virtual ~Strategie() = 0;
		//hausse
        //void updateHausse(){};
        //QString getNom() const {return nom;}
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

class MA_strategie : public Strategie {
private:
    EMA* ema;
    EMA::iterator ema_Iterator;
public:
    MA_strategie(EvolutionCours* evolutionCours, QDate dateDebut) : Strategie("MA_Strategie", evolutionCours, dateDebut) {
        //ema =
        //ema_Iterator =
    }
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
