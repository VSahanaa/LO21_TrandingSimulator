#ifndef INDICATEUR_H
#define INDICATEUR_H
#include<iostream>
#include<string.h>
#include <QString>
#include "trading.h"
/*Information de Indicateurs (https://stockcharts.com/school/doku.php?id=chart_school:technical_indicators:introduction_to_technical_indicators_and_oscillators#momentum_oscillators)
 */
class IndiceIndicateur {
private:
		double donnee;
        QDate  date;
public:
        IndiceIndicateur(){}
        double getIndice() { return donnee;}
        QDate  getDate() { return date;}
        void setIndice(double donnee) { this->donnee = donnee;}
        void setDate(QDate date) { this->date = date;}
};

//classe abstrait des indicateur

class Indicateur {
protected:
	EvolutionCours* evolutionCours;
    QString nom;
    CoursOHLCV* startingPoint;
    CoursOHLCV* endPoint;
    IndiceIndicateur* indices;  //array de IndiceIndicateur
    unsigned int nbIndicateur;
    unsigned int nbMaxIndicateur;
public:
    Indicateur(CoursOHLCV* startingPoint, CoursOHLCV* endPoint, EvolutionCours* evolutionCours, QString nom);
    ~Indicateur(){delete[] indices;}
    using iterator = IndiceIndicateur*;
    iterator begin(){return indices;}
    iterator end(){return indices + nbIndicateur;}
};


class EMA : public Indicateur{
    friend class MACD;
private:
    unsigned int period;
public:
    EMA(CoursOHLCV* startingPoint, CoursOHLCV* endPoint, EvolutionCours* evolutionCours, QString nom);
};


class RSI: public Indicateur {
private:
    unsigned int lookBackPeriod;
    double overboughtBound, oversoldBound;
public:
    RSI(CoursOHLCV* startingPoint, CoursOHLCV* endPoint, EvolutionCours* evolutionCours, QString nom, unsigned int lookbackPeriod, double overboughtBound, double oversoldBound);
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

