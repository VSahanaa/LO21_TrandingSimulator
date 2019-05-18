#ifndef INDICATEUR_H
#define INDICATEUR_H
#include<iostream>
#include<string.h>
#include <QString>
#include "trading.h"

class IndiceIndicateur {
private:
		double donnee;
		Qdate  date;
public:
		double getIndice() { return donnee; };
	    Qdate  getDate() { return date; };
		void setIndice(double don) { donnee = don;};
		void setDate(Qdate da) { date = da; };
};
class Indicateur {
protected:
	EvolutionCours* evolutionCours;
	int nbIndicateur;
	char* nom;
	IndiceIndicateur* indices;
public:
	Indicateur(EvolutionCours* e, char* n) {};
	~Indicateur();
};
class EMA:public Indicateur{
private:
	int	periode ;
public:
	friend class MACD;
	EMA(const int p, EvolutionCours* e, char* n);
	~EMA();
};

class RSI:public Indicateur {
private:
	int	parametre;
public:
	RSI(const int p, EvolutionCours* e, char* n);
	~RSI();
};


class MACD:public Indicateur {
private:
	int	longPeriode;
	int	shortPeriode;
public:
	MACD(const int longPeriode,const int shortPeriode, EvolutionCours* e,char* n);
	~MACD() ;
};

class IndicateurManage {
private:
	Indicateur* listeIndicateur;
	int nbIndicateur;
};

#endif // INDICATEUR_H

