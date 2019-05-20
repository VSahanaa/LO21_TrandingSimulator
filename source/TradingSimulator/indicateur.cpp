#include "indicateur.h"
/*----------------------------------------------- Methodes de classe Indicateur -------------------------------------------------*/
Indicateur::Indicateur(CoursOHLCV* startingPoint, CoursOHLCV* endPoint, EvolutionCours* evolutionCours, QString nom = "un named indicator"): nom(nom) {
    if (!evolutionCours) throw TradingException("Idicateur: evolutionCours est null");
        this->evolutionCours = evolutionCours;
    if(!startingPoint || !endPoint) throw TradingException("EMA: startingPoint ou endPoint est null");
        this->startingPoint = startingPoint;
        this->endPoint = endPoint;
    nbMaxIndicateur = evolutionCours->getNbCours();
    indices = new IndiceIndicateur[nbMaxIndicateur];
}

/*----------------------------------------------- Methodes de classe EMA -------------------------------------------------*/

EMA::EMA(CoursOHLCV* startingPoint, CoursOHLCV* endPoint, EvolutionCours* evolutionCours, QString nom) : Indicateur(startingPoint, endPoint, evolutionCours, nom) {
    period = startingPoint->getDate().daysTo(endPoint->getDate());
    if(period <= 0) throw TradingException("EMA: periode est null");

    //EMA initial est SMA pour cette periode
    double sum = 0;
    nbIndicateur = 0;
    EvolutionCours::iterator coursIterator;
    for(coursIterator = startingPoint; coursIterator != endPoint+1; coursIterator++) {
        sum += coursIterator->getClose();
        nbIndicateur++;
    }

    iterator indiceIterator = this->begin();
    indiceIterator->setDate(startingPoint->getDate());
    indiceIterator->setIndice((period - sum)/period);       //SMA
    indiceIterator++;
    coursIterator = startingPoint+1;
    while(indiceIterator != end()) {
        indiceIterator->setDate(coursIterator->getDate());
        //information sur EMA (https://www.investopedia.com/ask/answers/122314/what-exponential-moving-average-ema-formula-and-how-ema-calculated.asp)
        indiceIterator->setIndice((coursIterator->getClose()-(indiceIterator-1)->getIndice())*2/(period+1) + (indiceIterator-1)->getIndice());
        indiceIterator++;
        coursIterator++;
    }
}


/*----------------------------------------------- Methodes de classe RSI -------------------------------------------------*/


RSI::RSI(CoursOHLCV* startingPoint, CoursOHLCV* endPoint, EvolutionCours* evolutionCours, QString nom, unsigned int lookbackPeriod = 14, double overboughtBound= 70, double oversoldBound= 30)
    : Indicateur(startingPoint, endPoint, evolutionCours, nom), lookBackPeriod(lookbackPeriod), overboughtBound(overboughtBound), oversoldBound(oversoldBound) {

    //information sur RSI (https://stockcharts.com/school/doku.php?id=chart_school:technical_indicators:relative_strength_index_rsi)
    nbIndicateur = nbMaxIndicateur-lookbackPeriod;
    double avgGain=0, avgLost=0, RS;
    EvolutionCours::iterator coursIterator;
    double e;
    for (coursIterator = evolutionCours->begin()+1; coursIterator != evolutionCours->begin()+lookbackPeriod+1; coursIterator++) {
        e = coursIterator->getClose() - (coursIterator-1)->getClose();
        if (e>0) {
            avgGain += e;
        }
        else {
            avgLost += -e;
        }
    }
    avgGain /= lookBackPeriod;
    avgLost /= lookBackPeriod;
    RS = avgGain/avgLost;

    //il n'y a pas d'indicateur RSI pendant le look back periode
    iterator indiceIterator = begin();
    indiceIterator->setDate((coursIterator-1)->getDate());
    indiceIterator->setIndice(100-100/(1+RS));
    indiceIterator++;

	//element suivant
    while(indiceIterator != end()) {
        e = coursIterator->getClose() - (coursIterator-1)->getClose();
        if (e > 0) {
            avgGain = (avgGain*(lookbackPeriod-1) + e)/lookbackPeriod;
        }
        else {
            avgLost = (avgLost*(lookbackPeriod-1) - e)/lookbackPeriod;
        }
        RS = avgGain/avgLost;
        indiceIterator->setDate(coursIterator->getDate());
        indiceIterator->setIndice(100 - 100/(1+RS));
        indiceIterator++;
        coursIterator++;
	}
}



/*----------------------------------------------- Methodes de classe MACD -------------------------------------------------*/

/*
MACD::MACD(const int shortp, const int longp, EvolutionCours* e, char* n) :Indicateur(e, n){
	int nb;
	nb = e->getNbCours();
	if (longp <shortp|| shortp > nb) throw TradingException("periode erreur");
	if (longp< 0||shortp< 0) throw TradingException("periode negative");
	if (e == nullptr) throw TradingException("EvolutionCours null ");
	nbIndicateur =nb;
	double* el, * es;
	el = (double *)malloc(nb* sizeof(double));
	es = (double *)malloc(nb* sizeof(double));
	EMA emal(longp, e,n);
	EMA emas(shortp, e,n);
	for (int k = 1; k<nb; k++){
		el[k] = emal.indices[k].getIndice;
		es[k] = emas.indices[k].getIndice;
	}
	longPeriode = longp;
	shortPeriode = shortp;
	evolutionCours = e;
	for (int i = 0; i <nb; i++) {
		indices[i].setIndice(es[i] - el[i]);
		indices[i].setDate(e->cours[i].getDate()); 
	}
	free(el);
	free(es);

}

MACD::~MACD() {
	free(indices);
}
*/
