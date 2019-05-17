
class Strategie {
	Qstring nom;
	EvolutionCours& evolutioncours;
	unsigned int temps; //compteur de jour => faire un evolutioncours->iterator ?
	int hausse; //PERIODE 5utilisation pour les methodes pendu, marteau... : -1 baissiere, 0 neutre, 1 hausse
	
	//Constructeur et destructeur
	Strategie(Qtring n, EvolutionCours& e, unsigned int nbdejours): 
		nom(n), listecoursOHLCV(e), temps(nbdejours),hausse(0){};
	~strategie()=default;
	
/*	//Empecher la recopie de stratégie.
	Strategie(const Strategie& s) = delete;
    Strategie& operator=(const Strategie& s) = delete;
*/	
	public:
		Qtring getNom(){return nom;};
		
		//hausse
		void updateHausse(){};
		
		//Indicateur graphique
		bool verte(const CoursOHLC& c);	
		
		int pendu(const CoursOHLC& c);
		int marteau(const CoursOHLC& c);
		int etoile(const CoursOHLC& c);
		int marteauinverse(const CoursOHLC& c);
		bool lignependante(const CoursOHLC& c1,const CoursOHLC& c2);
		bool cielcouvert(const CoursOHLC& c1,const CoursOHLC& c2);
		bool avalementhaussiere(const CoursOHLC& c1,const CoursOHLC& c2);
		bool avalementbaissiere(const CoursOHLC& c1,const CoursOHLC& c2);
		//a faire le doji
};

class Strategie_Trivial :public Strategie {
	double limiteBase;
	double limiteContrepartie;
	
	Strategie_Trivial(Qtring n, EvolutionCours& e, unsigned int nbdejours, double limiteB, double limiteC):	//calculer du montant de base 
		nom(n), listecoursOHLCV(e), temps(nbdejours), hausse(0), limiteBase(limiteB), limiteContrepartie{limiteC};
	~strategie_Trivial()=default;
public:
	double operator()(const Transaction& precedent);	
}
/*
class Strategie_Scalping :public Strategie {
	RSI* rsi;
public:
	double operator()(const Transaction& precedent);	
}*/