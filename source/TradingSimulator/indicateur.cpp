//pas fini

#include "indicateur.h"

/*----------------------------------------------- Methodes de classe EMA -------------------------------------------------*/
EMA::EMA(const int p,EvolutionCours* e) {
	if (p>e->nbCours) throw TradingException("periode est plus superieur ");
	if (p<0) throw TradingException("periode negative");
	if (e==nullptr||e->nbCours==0) throw TradingException("EvolutionCours null ");
	periode = p;
	evolutionCours = e;
	ema = (double *)malloc(e->nbCours);
	ema[0] = e.cours[0].close;
	for (int i = 1; i < e->nbCours; i++) 
		ema[i] = (ema[i - 1] * (periode - 1) + 2 * e.cours[i].close) / (periode + 1);
}

EMA::~EMA() {
	free(ema);
}

/*----------------------------------------------- Methodes de classe RSI -------------------------------------------------*/
RSI::RSI(const int p, EvolutionCours* e) {
	if (p > e->nbCours) throw TradingException("periode est plus superieur ");
	if (p < 0) throw TradingException("periode negative");
	if (e == nullptr || e->nbCours == 0) throw TradingException("EvolutionCours null ");
	parametre = p;
	evolutionCours = e;
	rsi = (double *)malloc(e->nbCours);
	double up,down,rs,upavg,downavg;
	up = down = 0;
	//premiere element
	for (int i = 1; i <=p; i++) {
		if (e.cours[i].close >= e.cours[i - 1].close)
			up += e.cours[i].close - e.cours[i - 1].close;
		else
			down+= e.cours[i-1].close - e.cours[i].close;
	}
	upavg = up / p;
	downavg = down / p;
	rs = upavg/downavg;
	rsi[p - 1] = 100 - 100 / (1 + rs);
	//element suivant
	for (int i = p; i <=e->nbCours; i++) {
		up = down = 0;
		if (e.cours[i].close >= e.cours[i - 1].close)
			up += e.cours[i].close - e.cours[i - 1].close;
		else
			down += e.cours[i - 1].close - e.cours[i].close;
		upavg = (upavg*(p - 1) + up) / p;
		downavg = (downavg*(p - 1) + down) / p;
		rs = upavg / downavg;
		rsi[p] = 100 - 100 / (1 + rs);
	}
}

RSI::~RSI() {
	free(rsi);
}

/*----------------------------------------------- Methodes de classe MACD -------------------------------------------------*/
MACD::MACD(const int shortp, const int longp, EvolutionCours* e) {
	if (longp <shortp|| shortp > e->nbCours) throw TradingException("periode erreur");
	if (longp< 0||shortp< 0) throw TradingException("periode negative");
	if (e == nullptr) throw TradingException("EvolutionCours null ");
	double* el, es;
	el = (double *)malloc(e->nbCours);
	es = (double *)malloc(e->nbCours);
	EMA emal, emas;
	emal(longp, e);
	emas(shortp, e);
	el = emal.ema;
	es = emas.ema;
	longperiode = longp;
	shortperiode = shortp;
	evolutionCours = e;
	for (int i = 1; i < e->nbCours; i++)
		macd[i] = es[i]-el[i];
	free(el);
	free(es);

}

MACD::~MACD() {
	free(macd);
}
