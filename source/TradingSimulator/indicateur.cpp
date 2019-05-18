#include "indicateur.h"
/*----------------------------------------------- Methodes de classe Indicateur -------------------------------------------------*/

Indicateur::Indicateur(EvolutionCours* e, char* n) {
	nom = new char[strlen(n) + 1];
	strcpy(nom, n);
	evolutionCours = e;
};
Indicateur::~Indicateur() { delete[] nom; };



/*----------------------------------------------- Methodes de classe EMA -------------------------------------------------*/
EMA::EMA(const int p,EvolutionCours* e, char* n):Indicateur(e,n) {
	if (p>e->nbCours) throw TradingException("periode est plus superieur ");
	if (p<0) throw TradingException("periode negative");
	if (e==nullptr||e->nbCours==0) throw TradingException("EvolutionCours null ");
	nbIndicateur = e->nbCours;
	periode = p;
	indices=(IndiceIndicateur*)malloc((e->nbCours)*sizeof(IndiceIndicateur));
	indices[0].setIndice(e->cours[0].getClose());
	indices[0].setDate(e->cours[0].getDate());
	for (int i = 1; i < e->nbCours; i++) {
		indices[i].setIndice((indices[i - 1].getIndice()* (periode - 1) + 2 * e->cours[i].getClose()) / (periode + 1));
		indices[i].setDate(e->cours[i].getDate());
	}
}

EMA::~EMA() {
	free(indices);	
}

/*----------------------------------------------- Methodes de classe RSI -------------------------------------------------*/
RSI::RSI(const int p, EvolutionCours* e, char* n):Indicateur(e, n){
	if (p > e->nbCours) throw TradingException("periode est plus superieur ");
	if (p < 0) throw TradingException("periode negative");
	if (e == nullptr || e->nbCours == 0) throw TradingException("EvolutionCours null ");
	parametre = p;
	nbIndicateur = e->nbCours-p+1;
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
	for (int i = p; i <e->nbCours; i++) {
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
MACD::MACD(const int shortp, const int longp, EvolutionCours* e, char* n) :Indicateur(e, n){
	if (longp <shortp|| shortp > e->nbCours) throw TradingException("periode erreur");
	if (longp< 0||shortp< 0) throw TradingException("periode negative");
	if (e == nullptr) throw TradingException("EvolutionCours null ");
	nbIndicateur = e->nbCours;
	double* el, * es;
	el = (double *)malloc((e->nbCours) * sizeof(double));
	es = (double *)malloc((e->nbCours) * sizeof(double));
	EMA emal(longp, e,n);
	EMA emas(shortp, e,n);
	for (int k = 1; k< e->nbCours; k++){
		el[k] = emal.indices[k].getIndice;
		es[k] = emas.indices[k].getIndice;
	}
	longPeriode = longp;
	shortPeriode = shortp;
	evolutionCours = e;
	for (int i = 0; i < e->nbCours; i++) {
		indices[i].setIndice(es[i] - el[i]);
		indices[i].setDate(e->cours[i].getDate()); 
	}
	free(el);
	free(es);

}

MACD::~MACD() {
	free(indices);
}
