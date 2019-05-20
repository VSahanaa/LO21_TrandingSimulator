#include "indicateur.h"
/*----------------------------------------------- Methodes de classe Indicateur -------------------------------------------------*/


/*----------------------------------------------- Methodes de classe EMA -------------------------------------------------*/

EMA::EMA(CoursOHLCV* startingPoint, CoursOHLCV* endPoint, EvolutionCours* evolutionCours, QString nom) : Indicateur(evolutionCours,nom), startingPoint(startingPoint), endPoint(endPoint) {
    if(!startingPoint || !endPoint) throw TradingException("EMA: startingPoint ou endPoint est null");
    periode = startingPoint->getDate().daysTo(endPoint->getDate());
    if(periode <= 0) throw TradingException("EMA: periode est null");
    nbMaxIndicateur = evolutionCours->getNbCours();

    indices = new IndiceIndicateur[nbMaxIndicateur];
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
    indiceIterator->setIndice((periode - sum)/periode);       //SMA
    indiceIterator++;
    coursIterator = startingPoint+1;
    while(indiceIterator != end()) {
        indiceIterator->setDate(coursIterator->getDate());
        indiceIterator->setIndice((coursIterator->getClose()-(indiceIterator-1)->getIndice())*2/(periode+1) + (indiceIterator-1)->getIndice());
        indiceIterator++;
        coursIterator++;
    }
}

/*----------------------------------------------- Methodes de classe RSI -------------------------------------------------*/

RSI::RSI(const int p, EvolutionCours* e, char* n):Indicateur(e, n){
	int nb;
	nb = e->getNbCours();
	if (p >nb) throw TradingException("periode est plus superieur ");
	if (p < 0) throw TradingException("periode negative");
	if (e == nullptr ||nb== 0) throw TradingException("EvolutionCours null ");
	parametre = p;
	nbIndicateur =nb-p+1;
	indices = (IndiceIndicateur*)malloc(nbIndicateur * sizeof(IndiceIndicateur));
	double up,down,rs,upavg,downavg;
	up = down = 0;
	//premiere element
	for (int i = 1; i <=p; i++) {
		if (e->cours[i].getClose() >= e->cours[i - 1].getClose())
			up += e->cours[i].getClose() - e->cours[i - 1].getClose();
		else
			down+= e->cours[i-1].getClose() - e->cours[i].getClose();
	}
	upavg = up / p;
	downavg = down / p;
	rs = upavg/downavg;
	indices[0].setIndice(100 - 100 / (1 + rs));
	indices[0].setDate(e->cours[0].getDate()); 
	//element suivant
	for (int i = p; i <nb; i++) {
		up = down = 0;
		if (e->cours[i].getClose() >= e->cours[i - 1].getClose())
			up += e->cours[i].getClose() - e->cours[i - 1].getClose();
		else
			down += e->cours[i - 1].getClose() - e->cours[i].getClose();
		upavg = (upavg*(p - 1) + up) / p;
		downavg = (downavg*(p - 1) + down) / p;
		rs = upavg / downavg;
		indices[i-p+1].setIndice(100 - 100 / (1 + rs));
		indices[i-p+1].setDate(e->cours[i-p+1].getDate()); 
	}
}

RSI::~RSI() {
	free(indices);
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
