//pas fini
#ifndef INDICATEUR_H
#define INDICATEUR_H
#include <QString>
#include "trading.h"

class EMA {
private:
	EvolutionCours* evolutionCours;
	int	periode ;
public:
	double* ema;
	EMA(const int p,EvolutionCours* e) {};
	~EMA();
};

class RSI {
private:
	EvolutionCours*	evolutionCours;
	int	parametre;
	double* rsi;

public:
	RSI(const int p, EvolutionCours* e) {};
	~RSI();
};


class MACD{
private:
	EvolutionCours*	evolutionCours;
	int	longPeriode;
	int	shortPeriode;
	double* macd;
public:
	MACD(const int longPeriode,const int shortPeriode, EvolutionCours* e) {};
	~MACD() ;
};



#endif // INDICATEUR_H
