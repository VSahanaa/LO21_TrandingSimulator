#include "indicateur.h"
#include "transaction.h"
class Strategie {
    QString nom;
	EvolutionCours& evolutioncours;
	unsigned int temps; //compteur de jour => faire un evolutioncours->iterator ?
	int hausse; //PERIODE 5utilisation pour les methodes pendu, marteau... : -1 baissiere, 0 neutre, 1 hausse
	
	//Constructeur et destructeur
    Strategie(QString n, EvolutionCours& e, unsigned int nbdejours):
        nom(n), listecoursOHLCV(e), temps(nbdejours),hausse(0){}
    ~Strategie()=default;
	
/*	//Empecher la recopie de stratégie.
	Strategie(const Strategie& s) = delete;
    Strategie& operator=(const Strategie& s) = delete;
*/	
	public:
        QString getNom(){return nom;};
		
		//hausse
		void updateHausse(){};
		
		//Indicateur graphique
        bool verte(const CoursOHLCV& c);
		
        int pendu(const CoursOHLCV& c);
        int marteau(const CoursOHLCV& c);
        int etoile(const CoursOHLCV& c);
        int marteauinverse(const CoursOHLCV& c);
        bool lignependante(const CoursOHLCV& c1,const CoursOHLCV& c2);
        bool cielcouvert(const CoursOHLCV& c1,const CoursOHLCV& c2);
        bool avalementhaussiere(const CoursOHLCV& c1,const CoursOHLCV& c2);
        bool avalementbaissiere(const CoursOHLCV& c1,const CoursOHLCV& c2);
		//a faire le doji
};

class Strategie_Trivial :public Strategie {
	double limiteBase;
	double limiteContrepartie;
	
    Strategie_Trivial(QString n, EvolutionCours& e, unsigned int nbdejours, double limiteB, double limiteC):	//calculer du montant de base
        nom(n), listecoursOHLCV(e), temps(nbdejours), hausse(0), limiteBase(limiteB), limiteContrepartie(limiteC) {}
    ~Strategie_Trivial()=default;
public:
    double operator ()(const Transaction& precedent);
}


/*
class Strategie_Scalping :public Strategie {
	RSI* rsi;
public:
	double operator()(const Transaction& precedent);	
}*/
