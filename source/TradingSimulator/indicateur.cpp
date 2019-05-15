#include "indicateur.h"

/*----------------------------------------------- Methodes de classe EMA -------------------------------------------------*/
EMA::EMA(const int p,EvolutionCours* e, char* n) {
	if (p>e->nbCours) throw TradingException("periode est plus superieur ");
	if (p<0) throw TradingException("periode negative");
	if (e==nullptr||e->nbCours==0) throw TradingException("EvolutionCours null ");
	nbIndicateur = e->nbCours;
	periode = p;
	nom = new char[strlen(n) + 1];
	strcpy(nom, n);
	evolutionCours = e;
	indices=(IndiceIndicateur*)malloc((e->nbCours)*sizeof(IndiceIndicateur));
	indices[0] = e->cours[0].getClose();
	for (int i = 1; i < e->nbCours; i++) 
		indices[i] = (indices[i - 1].getIndice()* (periode - 1) + 2 * e->cours[i].getClose()) / (periode + 1);
}

EMA::~EMA() {
	free(indices);
	delete[] nom;
}

/*----------------------------------------------- Methodes de classe RSI -------------------------------------------------*/
RSI::RSI(const int p, EvolutionCours* e, char* n) {
	if (p > e->nbCours) throw TradingException("periode est plus superieur ");
	if (p < 0) throw TradingException("periode negative");
	if (e == nullptr || e->nbCours == 0) throw TradingException("EvolutionCours null ");
	parametre = p;
	nbIndicateur = e->nbCours-p+1;
	nom = new char[strlen(n) + 1];
	strcpy(nom, n);
	evolutionCours = e;
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
	indices[0].donnee = 100 - 100 / (1 + rs);
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
		indices[i-p+1].donnee= 100 - 100 / (1 + rs);
	}
}

RSI::~RSI() {
	free(indices);
	delete[] nom;
}

/*----------------------------------------------- Methodes de classe MACD -------------------------------------------------*/
MACD::MACD(const int shortp, const int longp, EvolutionCours* e, char* n) {
	if (longp <shortp|| shortp > e->nbCours) throw TradingException("periode erreur");
	if (longp< 0||shortp< 0) throw TradingException("periode negative");
	if (e == nullptr) throw TradingException("EvolutionCours null ");
	nbIndicateur = e->nbCours;
	nom = new char[strlen(n) + 1];
	strcpy(nom, n);
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
	for (int i = 1; i < e->nbCours; i++)
		indices[i].donnee = es[i]-el[i];
	free(el);
	free(es);

}

MACD::~MACD() {
	free(indices);
	delete[] nom;
}
