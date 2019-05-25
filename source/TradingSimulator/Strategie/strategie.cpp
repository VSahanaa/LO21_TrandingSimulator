#include "strategie.h"

/*--------------------------------------------------- Methodes de classe StrategieFactory ----------------------------------------------*/
StrategieFactory* StrategieFactory::instance = nullptr;
StrategieFactory::StrategieFactory(){
    strategieDictionary.empty();
    //IndicateurCollection = IndicateurCollection::getIndicateurCollection(evolutionCours);
    //add Strategie to dictionary

}


/*--------------------------------------------------- Methodes de classe MA_Strategie ---------------------------------------------------*/
MA_Strategie::MA_Strategie(EvolutionCours* evolutionCours, unsigned int period) : Strategie(evolutionCours, "MA Strategie") {
    ema = dynamic_cast<EMA*>(evolutionCours->getCollection()->getIndicateur("EMA"));
    ema ->setPeriod(period);
    ema_Iterator = ema->begin();
}

double MA_Strategie::operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours) {
    double montantBase = transactionManager->getMontantBase();
    double montantContrepartie = transactionManager->getMontantContrepartie();
    if(ema_Iterator->getDate() > currentCours->getDate()) {
        //hold until has enough indicateur data
        return 0;
    }
    // move ema_Iterator to current date
    while(ema_Iterator->getDate() < currentCours->getDate()) {
        ema_Iterator++;
    }

    if (currentCours->getOpen() > ema_Iterator->getIndice() && montantContrepartie > 0) {
        //buy signal
            return montantContrepartie;
    }
    else if (currentCours->getOpen() < ema_Iterator->getIndice() && montantBase > 0){
        //sell signal
        return - montantBase;
    }
    else {
        return 0;
    }
}

/*---------------------------------------------------------- Methodes de classe RSI_Strategie ------------------------------------------------*/
RSI_Strategie::RSI_Strategie(EvolutionCours* evolutionCours, unsigned int lookbackPeriod, double sellBound, double buyBound) : Strategie(evolutionCours, "RSI Strategie") {
    rsi = dynamic_cast<RSI*>(evolutionCours->getCollection()->getIndicateur("RSI"));
    rsi->setOversoldBound(buyBound);
    rsi->setOverboughtBound(sellBound);
    rsi->setLookbackPeriod(lookbackPeriod);
    rsi_Iterator = rsi->begin();
}

double RSI_Strategie::operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours) {
    double montantBase = transactionManager->getMontantBase();
    double montantContrepartie = transactionManager->getMontantContrepartie();
    if(rsi_Iterator->getDate() > currentCours->getDate()) {
        //hold until has enough indicateur data
        return 0;
    }
    // move rsi_Iterator to current date
    while(rsi_Iterator->getDate() < currentCours->getDate()) {
        rsi_Iterator++;
    }

    if (rsi_Iterator->getIndice() <= rsi->getOversoldBound() && montantContrepartie > 0) {
        //buy signal
        return montantContrepartie;
    }
    else if (rsi_Iterator->getIndice() >= rsi->getOverboughtBound() && montantBase > 0) {
        //sell signal
        return - montantBase;
    }
    else {
        return 0;
    }
}














/*
//INDICATEUR GRAPHIQUE BOUGIE
bool Strategie::verte(const CoursOHLC& c){
	if (c.getClose()-c.getOpen()>0) return true;
	else return false;
};	

int Strategie::pendu(const CoursOHLC& c){
	if (hausse==-1) return -1; //si ce n'est pas dans une periode montante
	float corps=abs(c.getOpen()-c.getClose()); //#include <stdlib.h>
	else if ((c.getLow/corps)<=2) return 0;	//taille de la mèche
	else return corps;
};

int Strategie::marteau(const CoursOHLC& c){
	if (hausse==1) return -1; //si ce n'est pas dans une periode basse
	float corps=abs(c.getOpen()-c.getClose()); //#include <stdlib.h>
	else if ((c.getLow/corps)<=2) return 0;	//taille de la mèche
	else return corps;
};

int Strategie::etoile(const CoursOHLC& c){
	if (hausse==-1) return -1; //si ce n'est pas dans une periode montante
	float corps=abs(c.getOpen()-c.getClose()); //#include <stdlib.h>
	else if ((c.getHight/corps)<=2) return 0;	//taille de la mèche
	else return corps;
};

int Strategie::marteauinverse(const CoursOHLC& c){
	if (hausse==1) return -1; //si ce n'est pas dans une periode basse
	float corps=abs(c.getOpen()-c.getClose()); //#include <stdlib.h>
	else if ((c.getHight/corps)<=2) return 0;	//taille de la mèche
	else return corps;
};

bool Strategie::lignependante(const CoursOHLC& c1,const CoursOHLC& c2){
	if (verte(c1)||!verte(c2)) return false; //si c1 bougie verte, ou c2 bougie rouge
	else {
		float milieu1= (c1.getOpen-c1.getClose())/2;
		float milieu2= (c2.getClose()-c2.getOpen())/2;
		if (milieu1>=milieu2 && c1.getClose()>c2.getOpen()) return true;
		else return false;
	}
};

bool Strategie::cielcouvert(const CoursOHLC& c1,const CoursOHLC& c2){
	if (verte(c2)||!verte(c1)) return false; //si c1 bougie rouge, ou c2 bougie verte
	else {
		float milieu2= (c2.getOpen-c2.getClose())/2;
		float milieu1= (c1.getClose()-c1.getOpen())/2;
		if (milieu1<=milieu2 && c2.getClose()>c1.getOpen()) return true;
		else return false;
	}
};

bool Strategie::avalementhaussiere(const CoursOHLC& c1,const CoursOHLC& c2){
	if (verte(c1)||!verte(c2)) return false; //si c1 bougie verte, ou c2 bougie rouge
	else if (c1.getClose()>c2.getOpen()&&c1.getOpen<c2.getClose) return true;
	else return false;
};

bool Strategie::avalementbaissiere(const CoursOHLC& c1,const CoursOHLC& c2){
	if (verte(c2)||!verte(c1)) return false; //si c1 bougie rouge, ou c2 bougie verte
	else if (c1.getClose()<c2.getOpen()&&c1.getOpen>c2.getClose) return true;
	else return false;
};

//PERIODE
void Strategie::updateHausse(){
	if (temps<3) hausse=0;
	else {
	if (verte(evolutioncours.cours[jours-3])&&verte(evolutioncours.cours[jours-2])
		&&	(evolutioncours.cours[jours-3]->getOpen()<evolutioncours.cours[jours-3]->getOpen()
			|| evolutioncours.cours[jours-3]->getClose()<evolutioncours.cours[jours-3]->getClose()))
			hausse=1;
	else if (!verte(evolutioncours.cours[jours-3])&&!verte(evolutioncours.cours[jours-2])
			&&	(evolutioncours.cours[jours-3]->getOpen()>evolutioncours.cours[jours-3]->getOpen()
			|| evolutioncours.cours[jours-3]->getClose()>evolutioncours.cours[jours-3]->getClose()))
			hausse=-1;
	else hausse=0;
	}
}

//STRATEGIE Trivial
double Strategie_Trivial::operator()(const Transaction& precedent){
	updateHausse();
	if (temps>3) //&& (&precedent!=nullptr).?
	{
		if (hausse==1)
		{
			if(etoile(evolutioncours.cours[jours-3])||pendu(evolutioncours.cours[jours-3])
				||etoile(evolutioncours.cours[jours-2])||pendu(evolutioncours.cours[jours-2])
				||avalementbaissiere(evolutioncours.cours[jours-3],evolutioncours.cours[jours-2]))
				{temps++; return 0;}
			else{
				if (precedent.montantBase-0.02*precedent.montantBase<limiteBase) {
					temps++; return 0;}
				else {
					temps++;
					return -0.02*precedent.montantBase; //ACHAT et ATTENTION ENLEVER LE BROKER!!! + MISE A JOUR 
				}
			}
		}
		else if (hausse==-1)
		{
			if(marteau(evolutioncours.cours[jours-3])||marteauinverse(evolutioncours.cours[jours-3])
				||marteau(evolutioncours.cours[jours-2])||marteauinverse(evolutioncours.cours[jours-2])
				||avalementhaussiere(evolutioncours.cours[jours-3],evolutioncours.cours[jours-2]))
				{temps++; return 0;}
			else {
				if (precedent.montantContrepartie-0.02*precedent.montantContrepartie<limiteContrepartie) {
					temps++; return 0;}
				else {
					temps++;
					return 0.02*precedent.montantContrepartie;//VENTE et ATTENTION ENLEVER LE BROKER!!! + MISE A JOUR
				} 
			}
		}
		else {
			temps++;
			return 0;
		}
	}
	else
	{
		temps++;
		return 0;
	}
};
*/
